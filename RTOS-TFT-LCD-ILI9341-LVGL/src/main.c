/************************************************************************/
/* includes                                                             */
/************************************************************************/

#include <asf.h>
#include <string.h>
#include "ili9341.h"
#include "lvgl.h"
#include "arm_math.h"
#include "others/bme280.h"
#include "touch/touch.h"
#include "components/header.h"
#include "screens/setup.h"
#include "screens/main_menu.h"
#include "screens/summary.h"
#include "screens/race.h"

/************************************************************************/
/* SCREENS VARIABLES                                                    */
/************************************************************************/
static lv_obj_t *screen_setup;
static lv_obj_t *screen_main_menu;
static lv_obj_t *screen_summary;
static lv_obj_t *screen_race;

/************************************************************************/
/* LCD / LVGL                                                           */
/************************************************************************/

#define LV_HOR_RES_MAX (240)
#define LV_VER_RES_MAX (320)

/*A static or global variable to store the buffers*/
static lv_disp_draw_buf_t disp_buf;

/*Static or global buffer(s). The second buffer is optional*/
static lv_color_t buf_1[LV_HOR_RES_MAX * LV_VER_RES_MAX];
static lv_disp_drv_t disp_drv; /*A variable to hold the drivers. Must be static or global.*/
static lv_indev_drv_t indev_drv;

/************************************************************************/
/* INPUTS/OUTPUTS                                                       */
/************************************************************************/
#define SPEED_SENSOR_PIO PIOB
#define SPEED_SENSOR_PIO_ID ID_PIOB
#define SPEED_SENSOR_PIO_IDX 3
#define SPEED_SENSOR_PIO_IDX_MASK (1 << SPEED_SENSOR_PIO_IDX)

#define RTT_FREQUENCY 50
#define RTT_N_PULSES 5 * RTT_FREQUENCY

/************************************************************************/
/* RTOS                                                                 */
/************************************************************************/

#define TASK_LCD_STACK_SIZE (1024 * 12 / sizeof(portSTACK_TYPE))
#define TASK_LCD_STACK_PRIORITY (tskIDLE_PRIORITY)
#define TASK_LCD_LABEL_STACK_SIZE (1024 * 4 / sizeof(portSTACK_TYPE))
#define TASK_LCD_LABEL_STACK_PRIORITY (tskIDLE_PRIORITY)
#define TASK_MAIN_STACK_SIZE (1024 * 4 / sizeof(portSTACK_TYPE))
#define TASK_MAIN_STACK_PRIORITY (tskIDLE_PRIORITY)
#define TASK_RACE_STACK_SIZE (1024 * 8 / sizeof(portSTACK_TYPE))
#define TASK_RACE_STACK_PRIORITY (tskIDLE_PRIORITY)
#define TASK_BME280_STACK_SIZE (1024 * 8 / sizeof(portSTACK_TYPE))
#define TASK_BME280_STACK_PRIORITY (tskIDLE_PRIORITY)

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName);
extern void vApplicationIdleHook(void);
extern void vApplicationTickHook(void);
extern void vApplicationMallocFailedHook(void);
extern void xPortSysTickHandler(void);

extern void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
	printf("stack overflow %x %s\r\n", pxTask, (portCHAR *)pcTaskName);
	for (;;)
	{
	}
}

extern void vApplicationIdleHook(void) {}

extern void vApplicationTickHook(void) {}

extern void vApplicationMallocFailedHook(void)
{
	configASSERT((volatile void *)NULL);
}

static void RTT_init(float freqPrescale, uint32_t IrqNPulses, uint32_t rttIRQSource);

/************************************************************************/
/* STRUCTS                                                              */
/************************************************************************/
typedef struct
{
	uint32_t year;
	uint32_t month;
	uint32_t day;
	uint32_t week;
	uint32_t hour;
	uint32_t minute;
	uint32_t seccond;
} calendar;

typedef struct _lcd_label_t
{
	lv_obj_t *label;
	char content[10];
} lcd_label_t;

typedef struct lcd_label_icon_t
{
	int label_id;
	int icon_id;
} lcd_label_icon_t;

/************************************************************************/
/* TASKS HANDLERS                                                       */
/************************************************************************/
TaskHandle_t task_update_lcd_handler;
TaskHandle_t task_race_handler;
TaskHandle_t task_calories_handler;
TaskHandle_t task_bme280_handler;

void task_race(void *pvParameters);
static void configure_input(void);

/************************************************************************/
/* SEMAPHORES                                                           */
/************************************************************************/
SemaphoreHandle_t xMutexLcd;		 // Mutex to protect the LCD
SemaphoreHandle_t xSemaphoreRtc; // Semaphore to update clock
SemaphoreHandle_t xSemaphoreSubmitSetup;
SemaphoreHandle_t xSemaphoreCloseSummary; // Semaphore to close summary screen
SemaphoreHandle_t xSemaphoreResetBmeData; // Semaphore to reset bme data

/* Semaphores to race control */
SemaphoreHandle_t xSemaphoreStartRace;	 // Semaphore to start tasks of the race
SemaphoreHandle_t xSemaphoreStopRace;		 // Semaphore to stop tasks of the race
SemaphoreHandle_t xSemaphorePauseRace;	 // Semaphore to pause tasks of the race
SemaphoreHandle_t xSemaphoreResumeRace;	 // Semaphore to resume tasks of the race
SemaphoreHandle_t xSemaphoreFillSummary; // Semaphore to fill the summary labels
SemaphoreHandle_t xSemaphoreBmeData;

/* Semaphores to screen update */
SemaphoreHandle_t xSemaphoreScreenSetup;		// Change screen to setup
SemaphoreHandle_t xSemaphoreScreenMainMenu; // Change screen to main menu
SemaphoreHandle_t xSemaphoreScreenRace;			// Change screen to race
SemaphoreHandle_t xSemaphoreScreenSummary;	// Change screen to summary of the race

SemaphoreHandle_t xSemaphoreSpeedSensor; // Sensor signal
SemaphoreHandle_t xSemaphoreRttCount;		 // dt to calculate speed
SemaphoreHandle_t xSemaphoreTcCount;		 // counts total time from race

/************************************************************************/
/* QUEUES                                                               */
/************************************************************************/
QueueHandle_t xQueueLcdLabel;
QueueHandle_t xQueueLcdLabelIcon;
QueueHandle_t xQueueRadiusUpdate;

/************************************************************************/
/* CALLBACKS                                                            */
/************************************************************************/
void speed_sensor_callback(void)
{
	BaseType_t xHigherPriorityTaskWoken = pdTRUE;
	xSemaphoreGiveFromISR(xSemaphoreSpeedSensor, &xHigherPriorityTaskWoken);
}

/************************************************************************/
/* TIMERS INITS                                                         */
/************************************************************************/
void RTC_init(Rtc *rtc, uint32_t id_rtc, calendar t, uint32_t irq_type)
{
	/* Configura o PMC */
	pmc_enable_periph_clk(ID_RTC);

	/* Default RTC configuration, 24-hour mode */
	rtc_set_hour_mode(rtc, 0);

	/* Configura data e hora manualmente */
	rtc_set_date(rtc, t.year, t.month, t.day, t.week);
	rtc_set_time(rtc, t.hour, t.minute, t.seccond);

	/* Configure RTC interrupts */
	NVIC_DisableIRQ(id_rtc);
	NVIC_ClearPendingIRQ(id_rtc);
	NVIC_SetPriority(id_rtc, 4);
	NVIC_EnableIRQ(id_rtc);

	/* Ativa interrupcao via alarme */
	rtc_enable_interrupt(rtc, irq_type);
}

static void RTT_init(float freqPrescale, uint32_t IrqNPulses, uint32_t rttIRQSource)
{

	uint16_t pllPreScale = (int)(((float)32768) / freqPrescale);

	rtt_sel_source(RTT, false);
	rtt_init(RTT, pllPreScale);

	if (rttIRQSource & RTT_MR_ALMIEN)
	{
		uint32_t ul_previous_time;
		ul_previous_time = rtt_read_timer_value(RTT);
		while (ul_previous_time == rtt_read_timer_value(RTT))
			;
		rtt_write_alarm_time(RTT, IrqNPulses + ul_previous_time);
	}

	/* config NVIC */
	NVIC_DisableIRQ(RTT_IRQn);
	NVIC_ClearPendingIRQ(RTT_IRQn);
	NVIC_SetPriority(RTT_IRQn, 4);
	NVIC_EnableIRQ(RTT_IRQn);

	/* Enable RTT interrupt */
	if (rttIRQSource & (RTT_MR_RTTINCIEN | RTT_MR_ALMIEN))
		rtt_enable_interrupt(RTT, rttIRQSource);
	else
		rtt_disable_interrupt(RTT, RTT_MR_RTTINCIEN | RTT_MR_ALMIEN);
}

void TC_init(Tc *TC, int ID_TC, int TC_CHANNEL, int freq)
{
	uint32_t ul_div;
	uint32_t ul_tcclks;
	uint32_t ul_sysclk = sysclk_get_cpu_hz();

	/* Configura o PMC */
	pmc_enable_periph_clk(ID_TC);

	/** Configura o TC para operar em  freq hz e interrupçcão no RC compare */
	tc_find_mck_divisor(freq, ul_sysclk, &ul_div, &ul_tcclks, ul_sysclk);
	tc_init(TC, TC_CHANNEL, ul_tcclks | TC_CMR_CPCTRG);
	tc_write_rc(TC, TC_CHANNEL, (ul_sysclk / ul_div) / freq);

	/* Configura NVIC*/
	NVIC_SetPriority(ID_TC, 4);
	NVIC_EnableIRQ((IRQn_Type)ID_TC);
	tc_enable_interrupt(TC, TC_CHANNEL, TC_IER_CPCS);
}

/************************************************************************/
/* TIMERS HANDLERS                                                      */
/************************************************************************/
void RTC_Handler(void)
{
	uint32_t ul_status = rtc_get_status(RTC);
	char time_str[10];

	/* seccond tick */
	if ((ul_status & RTC_SR_SEC) == RTC_SR_SEC)
	{
		BaseType_t xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(xSemaphoreRtc, &xHigherPriorityTaskWoken);
	}

	/* Time or date alarm */
	if ((ul_status & RTC_SR_ALARM) == RTC_SR_ALARM)
	{
		// o código para irq de alame vem aqui
	}

	rtc_clear_status(RTC, RTC_SCCR_SECCLR);
	rtc_clear_status(RTC, RTC_SCCR_ALRCLR);
	rtc_clear_status(RTC, RTC_SCCR_ACKCLR);
	rtc_clear_status(RTC, RTC_SCCR_TIMCLR);
	rtc_clear_status(RTC, RTC_SCCR_CALCLR);
	rtc_clear_status(RTC, RTC_SCCR_TDERRCLR);
}

void RTT_Handler(void)
{
	uint32_t ul_status;

	/* Get RTT status - ACK */
	ul_status = rtt_get_status(RTT);

	/* IRQ due to Alarm */
	if ((ul_status & RTT_SR_ALMS) == RTT_SR_ALMS)
	{
		BaseType_t xHigherPriorityTaskWoken = pdTRUE;
		xSemaphoreGiveFromISR(xSemaphoreRttCount, &xHigherPriorityTaskWoken);
	}

	/* IRQ due to Time has changed */
	if ((ul_status & RTT_SR_RTTINC) == RTT_SR_RTTINC)
	{
		// BaseType_t xHigherPriorityTaskWoken = pdTRUE;
		// xSemaphoreGiveFromISR(xSemaphoreRttCount, &xHigherPriorityTaskWoken);
	}
}

void TC3_Handler(void)
{
	volatile uint32_t status = tc_get_status(TC1, 0);

	BaseType_t xHigherPriorityTaskWoken = pdTRUE;
	xSemaphoreGiveFromISR(xSemaphoreTcCount, &xHigherPriorityTaskWoken);
}

/************************************************************************/
/* BUTTONS HANDLERS                                                     */
/************************************************************************/
void submit_setup_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	uint32_t year, month, day, week, hour, minute, second;
	lv_calendar_date_t *today;
	lcd_label_t data_label;

	float radius;

	if (code == LV_EVENT_CLICKED)
	{
		radius = get_radius(lv_dropdown_get_selected(dropdown));
		xQueueSend(xQueueRadiusUpdate, &radius, (TickType_t)0);

		today = lv_calendar_get_today_date(lv_calendar);
		hour = atoi(lv_label_get_text(label_hour_setup));
		minute = atoi(lv_label_get_text(label_minute_setup));
		second = 0;
		week = (((today->month - 1) * 30) + today->day) / 7;

		rtc_set_date(RTC, today->year, today->month, today->day, week);
		rtc_set_time(RTC, hour, minute, second);

		xSemaphoreGive(xSemaphoreSubmitSetup);
	}
}

void open_setup_screen_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		xSemaphoreGive(xSemaphoreScreenSetup);
	}
}

void start_race_button_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		xSemaphoreGive(xSemaphoreScreenRace);
		xSemaphoreGive(xSemaphoreStartRace);
	}
}

void play_pause_button_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		xSemaphoreGive(xSemaphorePauseRace);
	}
}

void finish_race_button_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		xSemaphoreGive(xSemaphoreScreenSummary);
		xSemaphoreGive(xSemaphoreBmeData);
		xSemaphoreGive(xSemaphoreFillSummary);
	}
}

void close_summary_button_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code == LV_EVENT_CLICKED)
	{
		xSemaphoreGive(xSemaphoreCloseSummary);
		xSemaphoreGive(xSemaphoreResetBmeData);
	}
}

/************************************************************************/
/* GENERAL FUNCTIONS                                                    */
/************************************************************************/

void update_label_lcd(lv_obj_t *label, char *content)
{
	xSemaphoreTake(xMutexLcd, portMAX_DELAY);
	lv_label_set_text(label, content);
	fflush(stdout);
	xSemaphoreGive(xMutexLcd);
}

double get_cal_factor(double speed)
{
	double factor;
	if (speed < 15)
	{
		factor = 0.066;
	}
	else if ((speed >= 15) && (speed < 19))
	{
		factor = 0.1;
	}
	else if ((speed >= 19) && (speed < 22))
	{
		factor = 0.133;
	}
	else if ((speed >= 22) && (speed < 25))
	{
		factor = 0.166;
	}
	else if ((speed >= 25) && (speed < 30))
	{
		factor = 0.2;
	}
	else
	{
		factor = 0.266;
	}

	return factor;
}

void resume_race_tasks(void)
{
	vTaskResume(task_race_handler);
	// vTaskResume(task_calories_handler);
	vTaskResume(task_bme280_handler);
}

void pause_race_tasks(void)
{
	vTaskSuspend(task_bme280_handler);
	// vTaskSuspend(task_calories_handler);
	vTaskSuspend(task_race_handler);
}

void reset_screen_race_labels(void)
{
	lcd_label_t data_label;

	data_label.label = label_calories;
	lv_snprintf(data_label.content, 3, "%d", 0);
	xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

	data_label.label = label_speed_max;
	lv_snprintf(data_label.content, 3, "%d", 0);
	xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

	data_label.label = label_speed_avg;
	lv_snprintf(data_label.content, 3, "%d", 0);
	xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

	data_label.label = label_altitude;
	lv_snprintf(data_label.content, 3, "%d", 0);
	xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);
}

/************************************************************************/
/* TASKS                                                                */
/************************************************************************/
void task_main(void *pvParameters)
{
	TickType_t xBlockTime = 1 / portTICK_PERIOD_MS;

	lcd_label_icon_t icon_label;

	char race_status = 0;
	for (;;)
	{
		if (xSemaphoreTake(xSemaphoreStartRace, xBlockTime) == pdTRUE)
		{
			/* Create task to the race */
			RTT_init(RTT_FREQUENCY, RTT_N_PULSES, RTT_MR_ALMIEN);
			tc_start(TC1, 0);
			resume_race_tasks();
			race_status = 1;
		}

		/* Semaphore to play/pause the race task */
		if (xSemaphoreTake(xSemaphorePauseRace, xBlockTime) == pdTRUE)
		{
			if (race_status)
			{
				icon_label.label_id = 0;
				icon_label.icon_id = 0;
				xQueueSend(xQueueLcdLabelIcon, &icon_label, (TickType_t)0);

				printf("Corrida pausada\n");
				tc_stop(TC3, 0);
				pause_race_tasks();
			}
			else
			{
				icon_label.label_id = 0;
				icon_label.icon_id = 1;
				xQueueSend(xQueueLcdLabelIcon, &icon_label, (TickType_t)0);

				printf("Corrida retomada\n");
				tc_start(TC3, 0);
				resume_race_tasks();
			}
			race_status = !race_status;
		}

		vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}

void task_screen_lcd(void *pvParameters)
{
	/** Configure RTC */
	calendar rtc_initial = {2022, 5, 31, 21, 18, 0, 0};
	RTC_init(RTC, ID_RTC, rtc_initial, RTC_IER_SECEN);

	/* Create screens */
	screen_setup = lv_obj_create(NULL);
	screen_main_menu = lv_obj_create(NULL);
	screen_summary = lv_obj_create(NULL);
	screen_race = lv_obj_create(NULL);

	lv_obj_t *screen_act;
	lcd_label_t data_label;
	lv_calendar_date_t *today;

	setup_screen_create(screen_setup);
	main_menu_screen_create(screen_main_menu);
	summary_screen_create(screen_summary);
	race_screen_create(screen_race);

	screen_act = screen_setup;

	BaseType_t xTaskWokenByReceiveSemaphore = pdFALSE;
	TickType_t xBlockTime = 1 / portTICK_PERIOD_MS;

	char change_screen = 0; // if screen is changed, update the date in header

	for (;;)
	{
		lv_scr_load(screen_act);

		/* Gets setup choices and load main menu screen */
		if (xSemaphoreTake(xSemaphoreSubmitSetup, xBlockTime) == pdTRUE)
		{
			screen_act = screen_main_menu;
			header_create(screen_act);
			change_screen = 1;
		}

		/* Close summary screen and load main menu screen */
		if (xSemaphoreTake(xSemaphoreCloseSummary, xBlockTime) == pdTRUE)
		{
			screen_act = screen_main_menu;
			header_create(screen_act);
			change_screen = 1;
		}

		/* Return to setup screen */
		if (xSemaphoreTake(xSemaphoreScreenSetup, xBlockTime) == pdTRUE)
		{
			screen_act = screen_setup;
			change_screen = 1;
		}

		/* Open race screen */
		if (xSemaphoreTake(xSemaphoreScreenRace, xBlockTime) == pdTRUE)
		{
			screen_act = screen_race;
			header_create(screen_act);
			change_screen = 1;
		}

		/* Open summary screen */
		if (xSemaphoreTake(xSemaphoreScreenSummary, xBlockTime) == pdTRUE)
		{
			screen_act = screen_summary;
			header_create(screen_act);
			change_screen = 1;
		}

		if (change_screen)
		{
			today = lv_calendar_get_today_date(lv_calendar);
			lv_snprintf(data_label.content, 11, "%02d/%02d/%04d", today->day, today->month, today->year);
			data_label.label = label_date_header;
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);
			change_screen = 0;
		}

		lv_tick_inc(10);
		lv_task_handler();
		vTaskDelay(10);
	}
}

void task_update_lcd(void *pvParameters)
{
	lcd_label_t data_label;
	lcd_label_icon_t icon_label;

	uint32_t hour, min, sec;
	char time_str[10];

	BaseType_t xTaskWokenByRtc = pdFALSE;

	for (;;)
	{
		if (xQueueReceive(xQueueLcdLabel, &data_label, (TickType_t)0))
		{
			xSemaphoreTake(xMutexLcd, portMAX_DELAY);
			lv_label_set_text(data_label.label, data_label.content);
			fflush(stdout);
			xSemaphoreGive(xMutexLcd);
		}

		if (xQueueReceive(xQueueLcdLabelIcon, &icon_label, (TickType_t)0))
		{
			xSemaphoreTake(xMutexLcd, portMAX_DELAY);
			/* Update play/pause button icon */
			if (icon_label.label_id == 0)
			{
				if (icon_label.icon_id == 0)
				{
					lv_label_set_text(label_btn_play_pause, LV_SYMBOL_PLAY);
				}
				else
				{
					lv_label_set_text(label_btn_play_pause, LV_SYMBOL_PAUSE);
				}
			}

			/* Update acceleration icon */
			else if (icon_label.label_id == 1)
			{
				if (icon_label.icon_id == 0)
				{
					lv_label_set_text(label_acceleration, LV_SYMBOL_MINUS);
					lv_obj_set_style_text_color(label_acceleration, lv_color_hex(BLUE_LIGHT), LV_STATE_DEFAULT);
				}
				else if (icon_label.icon_id == 1)
				{
					lv_label_set_text(label_acceleration, LV_SYMBOL_UP);
					lv_obj_set_style_text_color(label_acceleration, lv_color_hex(GREEN_BACKGROUND), LV_STATE_DEFAULT);
				}
				else if (icon_label.icon_id == 2)
				{
					lv_label_set_text(label_acceleration, LV_SYMBOL_DOWN);
					lv_obj_set_style_text_color(label_acceleration, lv_color_hex(RED_LIGHT), LV_STATE_DEFAULT);
				}
			}
			fflush(stdout);
			xSemaphoreGive(xMutexLcd);
		}

		if (xSemaphoreTakeFromISR(xSemaphoreRtc, &xTaskWokenByRtc) == pdTRUE)
		{
			xSemaphoreTake(xMutexLcd, portMAX_DELAY);
			rtc_get_time(RTC, &hour, &min, &sec);
			lv_label_set_text_fmt(label_time_header, "%02d:%02d:%02d", hour, min, sec);
			fflush(stdout);
			xSemaphoreGive(xMutexLcd);
		}

		lv_tick_inc(10);
		lv_task_handler();
		vTaskDelay(10);
	}
}

void task_race(void *pvParameters)
{
	configure_input();

	uint32_t pulses = 0; // pulses from speed sensor (counts the number of turns that wheel has made)
	double prev_time_s = 0.0;
	double prev_vel_ms = 0.0;
	double dt = 1.0 / RTT_FREQUENCY; // time difference between two consecutive pulses
	double distance = 0.0;					 // distance in kilometers
	double acceleration;						 // acceleration in m/s^2
	float radius = 0.29f;						 // radius of the wheel in meters (default value)

	double avg_vel = 0.0; // average velocity in m/s
	double sum_vel = 0.0; // sum of velocities in m/s

	double w_ = 0.0;		 // wheel rotation in rad/s
	double vel_ms = 0.0; // velocity in m/s
	double vel_km = 0.0; // velocity in km/h
	int max_vel = 0;		 // maximum velocity in km/h
	double time_s = 0.0; // time in seconds since the start of the rtt counter
	double time_h = 0.0; // time in hours since the start of the rtt counter

	int pulses_rtt = 0; // pulses from rtt peripheral
	int prev_acc = 0;		// previous acceleration status

	int kcal;				 // calories burned
	int weight;			 // weight in kilograms
	double factor;	 // conversion factor to calories burned
	double time_min; // time in minutes

	TC_init(TC1, ID_TC3, 0, 1);

	BaseType_t xTaskIsWoken = pdTRUE;
	BaseType_t xTaskIsNotWoken = pdFALSE;
	TickType_t xBlockTime = 5 / portTICK_PERIOD_MS;

	lcd_label_t data_label;
	lcd_label_icon_t icon_label;

	uint32_t total_time = 0;

	vTaskSuspend(task_race_handler);

	for (;;)
	{
		if (xQueueReceive(xQueueRadiusUpdate, &radius, (TickType_t)0))
		{
			printf("Updated radius: r = %f\n", radius);
		}

		if (xSemaphoreTakeFromISR(xSemaphoreSpeedSensor, &xTaskIsWoken) == pdTRUE)
		{
			pulses_rtt = rtt_read_timer_value(RTT);
			dt = pulses_rtt / (double)RTT_FREQUENCY;
			RTT_init(RTT_FREQUENCY, RTT_N_PULSES, RTT_MR_ALMIEN);

			w_ = (2 * PI) * (double)(1 / dt);
			vel_ms = w_ * radius;
			vel_km = vel_ms * 3.6;

			distance += (2 * PI * radius) / 1000.0;
			acceleration = (vel_ms - prev_vel_ms) / (double)dt;
			time_h = total_time / 3600.0;

			prev_vel_ms = vel_ms;

			if (max_vel < vel_km)
			{
				max_vel = vel_km;
				/* Update max speed on lcd only when it changes */
				data_label.label = label_speed_max;
				lv_snprintf(data_label.content, 3, "%02d", (uint)max_vel);
				xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);
			}

			if (time_h > 0)
			{
				avg_vel = distance / time_h;
			}
			else
			{
				avg_vel = 0.0;
			}

			icon_label.label_id = 1;
			if (acceleration > 0.05)
			{
				icon_label.icon_id = 1;
			}
			else if (acceleration < -0.05)
			{
				icon_label.icon_id = 2;
			}
			else
			{
				icon_label.icon_id = 0;
			}
			xQueueSend(xQueueLcdLabelIcon, &icon_label, (TickType_t)0);

			data_label.label = label_speed_inst;
			lv_snprintf(data_label.content, 3, "%02d", (int)vel_km);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			/* Updates distance and average speed every 3 seconds */
			if (total_time % 3 == 0)
			{
				int distance_dec = (int)(distance * 10) % 10;
				int avg_vel_dec = (int)(avg_vel * 10) % 10;

				data_label.label = label_distance;
				lv_snprintf(data_label.content, 5, "%02d,%01d", (int)distance, distance_dec);
				xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

				data_label.label = label_speed_avg;
				lv_snprintf(data_label.content, 5, "%02d,%01d", (int)avg_vel, avg_vel_dec);
				xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);
			}
		}

		if (xSemaphoreTakeFromISR(xSemaphoreTcCount, &xTaskIsWoken) == pdTRUE)
		{
			total_time++;
			uint t_mins = (total_time / 60) % 60;
			uint t_hours = (t_mins / 60) % 24;
			if (total_time % 2 == 0)
			{
				lv_snprintf(data_label.content, 6, "%02d:%02d", t_hours, t_mins);
			}
			else
			{
				lv_snprintf(data_label.content, 6, "%02d %02d", t_hours, t_mins);
			}
			data_label.label = label_total_time;
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);
		}

		if (xSemaphoreTakeFromISR(xSemaphoreRttCount, &xTaskIsWoken) == pdTRUE)
		{
			vel_km = 0.0;
			vel_ms = 0.0;
			dt = (double)RTT_N_PULSES / RTT_FREQUENCY;
			acceleration = (vel_ms - prev_vel_ms) / dt;

			time_h = total_time / 3600.0;
			avg_vel = distance / time_h;

			icon_label.label_id = 1;
			if (acceleration > 0.1)
			{
				icon_label.icon_id = 1;
			}
			else if (acceleration < -0.1)
			{
				icon_label.icon_id = 2;
			}
			else
			{
				icon_label.icon_id = 0;
			}
			xQueueSend(xQueueLcdLabelIcon, &icon_label, (TickType_t)0);

			int distance_dec = (int)(distance * 10) % 10;
			int avg_vel_dec = (int)(avg_vel * 10) % 10;

			data_label.label = label_speed_inst;
			lv_snprintf(data_label.content, 3, "%02d", (uint)vel_km);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			data_label.label = label_distance;
			lv_snprintf(data_label.content, 5, "%02d,%01d", (uint)distance, distance_dec);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			data_label.label = label_speed_max;
			lv_snprintf(data_label.content, 3, "%02d", (uint)max_vel);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			data_label.label = label_speed_avg;
			lv_snprintf(data_label.content, 5, "%02d,%01d", (uint)avg_vel, avg_vel_dec);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			RTT_init(RTT_FREQUENCY, RTT_N_PULSES, RTT_MR_ALMIEN);
		}

		if (xSemaphoreTake(xSemaphoreFillSummary, xBlockTime) == pdTRUE)
		{
			vTaskDelay(500 / portTICK_PERIOD_MS);

			data_label.label = label_summary_distance;
			lv_snprintf(data_label.content, 5, "%02d,%01d", (uint)distance, (int)(distance * 10) % 10);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			data_label.label = label_summary_avg_speed;
			lv_snprintf(data_label.content, 5, "%02d,%01d", (uint)avg_vel, (int)(avg_vel * 10) % 10);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			data_label.label = label_summary_max_speed;
			lv_snprintf(data_label.content, 3, "%02d", (uint)max_vel);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			data_label.label = label_summary_total_time;
			uint t_secs = (total_time % 60);
			uint t_mins = (total_time / 60) % 60;
			uint t_hours = (t_mins / 60) % 24;
			lv_snprintf(data_label.content, 9, "%02d:%02d:%02d", t_hours, t_mins, t_secs);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			data_label.label = label_summary_calories;
			lv_snprintf(data_label.content, 5, "%s", lv_label_get_text(label_calories));
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			/* Reset all values */
			reset_screen_race_labels();

			tc_stop(TC3, 0);
			rtt_disable_interrupt(RTT, RTT_MR_ALMIEN);

			pulses = 0;
			prev_time_s = 0.0;
			prev_vel_ms = 0.0;
			distance = 0.0;
			acceleration = 0.0;
			avg_vel = 0.0;
			sum_vel = 0.0;
			w_ = 0.0;
			vel_ms = 0.0;
			vel_km = 0.0;
			max_vel = 0;
			time_s = 0.0;
			time_h = 0.0;
			total_time = 0;
			kcal = 0;
			time_min = 0;

			// vTaskSuspend(task_calories_handler);
			vTaskSuspend(task_race_handler);
		}

		/* Update calories value */
		if (total_time % 4 == 0)
		{
			time_min = (double)total_time / 60;
			weight = atoi(lv_label_get_text(label_w_bike));
			factor = get_cal_factor(avg_vel);

			kcal = (factor * weight * time_min);

			lv_snprintf(data_label.content, 5, "%d", kcal);
			data_label.label = label_calories;
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);
		}
	}
}

void task_bme280(void *pvParameters)
{
	bme280_i2c_bus_init();

	char validated = 0;

	uint temp, pressao, altitude;
	int32_t dig_T1, dig_T2, dig_T3;
	int32_t dig_P1, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;

	uint min_altitude = 10000;
	uint max_altitude = 0;

	uint min_temp = 100;
	uint max_temp = 0;
	double avg_temp;

	lcd_label_t data_label;
	TickType_t xBlockTime = 1 / portTICK_PERIOD_MS;
	TickType_t xTaskDelay = 3000 / portTICK_PERIOD_MS;

	vTaskSuspend(task_bme280_handler);

	for (;;)
	{
		if (bme280_validate_id())
		{
			printf("Chip nao encontrado\n");
			validated = 0;
		}
		else if (!validated)
		{
			printf("Chip encontrado\n");
			validated = 1;
			bme280_i2c_config_temp();

			bme280_i2c_read_compensation_T(&dig_T1, BME280_DIG_T1_LSB_REG, BME280_DIG_T1_MSB_REG);
			bme280_i2c_read_compensation_T(&dig_T2, BME280_DIG_T2_LSB_REG, BME280_DIG_T2_MSB_REG);
			bme280_i2c_read_compensation_T(&dig_T3, BME280_DIG_T3_LSB_REG, BME280_DIG_T3_MSB_REG);

			bme280_i2c_read_compensation_P(&dig_P1, BME280_DIG_P1_LSB_REG, BME280_DIG_P1_MSB_REG);
			bme280_i2c_read_compensation_P(&dig_P2, BME280_DIG_P2_LSB_REG, BME280_DIG_P2_MSB_REG);
			bme280_i2c_read_compensation_P(&dig_P3, BME280_DIG_P3_LSB_REG, BME280_DIG_P3_MSB_REG);
			bme280_i2c_read_compensation_P(&dig_P4, BME280_DIG_P4_LSB_REG, BME280_DIG_P4_MSB_REG);
			bme280_i2c_read_compensation_P(&dig_P5, BME280_DIG_P5_LSB_REG, BME280_DIG_P5_MSB_REG);
			bme280_i2c_read_compensation_P(&dig_P6, BME280_DIG_P6_LSB_REG, BME280_DIG_P6_MSB_REG);
			bme280_i2c_read_compensation_P(&dig_P7, BME280_DIG_P7_LSB_REG, BME280_DIG_P7_MSB_REG);
			bme280_i2c_read_compensation_P(&dig_P8, BME280_DIG_P8_LSB_REG, BME280_DIG_P8_MSB_REG);
			bme280_i2c_read_compensation_P(&dig_P9, BME280_DIG_P9_LSB_REG, BME280_DIG_P9_MSB_REG);
		}

		if (validated)
		{
			if (bme280_i2c_read_temp(&temp))
			{
				printf("erro reading temperature \n");
			}
			else
			{
				// bme280_i2c_read_compensation_T(&dig_T1, BME280_DIG_T1_LSB_REG, BME280_DIG_T1_MSB_REG);
				// bme280_i2c_read_compensation_T(&dig_T2, BME280_DIG_T2_LSB_REG, BME280_DIG_T2_MSB_REG);
				// bme280_i2c_read_compensation_T(&dig_T3, BME280_DIG_T3_LSB_REG, BME280_DIG_T3_MSB_REG);

				temp = BME280_compensate_T_int32((int32_t)temp << 4, dig_T1, dig_T2, dig_T3) / 100;

				if (temp < min_temp)
				{
					min_temp = temp;
				}

				if (temp > max_temp)
				{
					max_temp = temp;
				}
			}

			if (bme280_i2c_read_press(&pressao))
			{
				printf("Erro ao ler a pressao \n");
			}
			else
			{
				// bme280_i2c_read_compensation_P(&dig_P1, BME280_DIG_P1_LSB_REG, BME280_DIG_P1_MSB_REG);
				// bme280_i2c_read_compensation_P(&dig_P2, BME280_DIG_P2_LSB_REG, BME280_DIG_P2_MSB_REG);
				// bme280_i2c_read_compensation_P(&dig_P3, BME280_DIG_P3_LSB_REG, BME280_DIG_P3_MSB_REG);
				// bme280_i2c_read_compensation_P(&dig_P4, BME280_DIG_P4_LSB_REG, BME280_DIG_P4_MSB_REG);
				// bme280_i2c_read_compensation_P(&dig_P5, BME280_DIG_P5_LSB_REG, BME280_DIG_P5_MSB_REG);
				// bme280_i2c_read_compensation_P(&dig_P6, BME280_DIG_P6_LSB_REG, BME280_DIG_P6_MSB_REG);
				// bme280_i2c_read_compensation_P(&dig_P7, BME280_DIG_P7_LSB_REG, BME280_DIG_P7_MSB_REG);
				// bme280_i2c_read_compensation_P(&dig_P8, BME280_DIG_P8_LSB_REG, BME280_DIG_P8_MSB_REG);
				// bme280_i2c_read_compensation_P(&dig_P9, BME280_DIG_P9_LSB_REG, BME280_DIG_P9_MSB_REG);

				pressao = BME280_compensate_P_int64((int32_t)pressao << 4, dig_P1, dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9);
				pressao /= 256;
				altitude = (11.526 - log(pressao)) * 8696;

				if (altitude < min_altitude)
				{
					min_altitude = altitude;
				}

				if (altitude > max_altitude)
				{
					max_altitude = altitude;
				}

				data_label.label = label_altitude;
				lv_snprintf(data_label.content, 5, "%d", altitude);
				xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);
			}
		}

		/* Send summary data about press and temperature to the LCD */
		if (xSemaphoreTake(xSemaphoreBmeData, xBlockTime))
		{
			vTaskDelay(500 / portTICK_PERIOD_MS);

			data_label.label = label_summary_min_altitude;
			lv_snprintf(data_label.content, 5, "%d", min_altitude);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			data_label.label = label_summary_max_altitude;
			lv_snprintf(data_label.content, 5, "%d", max_altitude);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			data_label.label = label_summary_altitude_gain;
			lv_snprintf(data_label.content, 5, "%d", max_altitude - min_altitude);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			avg_temp = (double)(max_temp + min_temp) / 2;
			int avg_temp_dec = (int)(10 * avg_temp) % 10;
			data_label.label = label_summary_avg_temp;
			lv_snprintf(data_label.content, 5, "%02d,%01d", (int)avg_temp, avg_temp_dec);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			vTaskSuspend(task_bme280_handler);
		}

		if (xSemaphoreTake(xSemaphoreResetBmeData, xBlockTime))
		{
			min_altitude = 10000;
			min_temp = 100;

			data_label.label = label_summary_min_altitude;
			lv_snprintf(data_label.content, 5, "%d", 0);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			data_label.label = label_summary_max_altitude;
			lv_snprintf(data_label.content, 5, "%d", 0);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);

			data_label.label = label_summary_altitude_gain;
			lv_snprintf(data_label.content, 5, "%d", 0);
			xQueueSend(xQueueLcdLabel, &data_label, (TickType_t)0);
		}

		vTaskDelay(xTaskDelay);
	}
}

/************************************************************************/
/* configs                                                              */
/************************************************************************/

static void configure_lcd(void)
{
	/**LCD pin configure on SPI*/
	pio_configure_pin(LCD_SPI_MISO_PIO, LCD_SPI_MISO_FLAGS); //
	pio_configure_pin(LCD_SPI_MOSI_PIO, LCD_SPI_MOSI_FLAGS);
	pio_configure_pin(LCD_SPI_SPCK_PIO, LCD_SPI_SPCK_FLAGS);
	pio_configure_pin(LCD_SPI_NPCS_PIO, LCD_SPI_NPCS_FLAGS);
	pio_configure_pin(LCD_SPI_RESET_PIO, LCD_SPI_RESET_FLAGS);
	pio_configure_pin(LCD_SPI_CDS_PIO, LCD_SPI_CDS_FLAGS);

	ili9341_init();
	ili9341_backlight_on();
}

static void configure_console(void)
{
	/* Configura USART1 Pinos */
	sysclk_enable_peripheral_clock(ID_PIOB);
	sysclk_enable_peripheral_clock(ID_PIOA);
	pio_set_peripheral(PIOB, PIO_PERIPH_D, PIO_PB4);	// RX
	pio_set_peripheral(PIOA, PIO_PERIPH_A, PIO_PA21); // TX
	MATRIX->CCFG_SYSIO |= CCFG_SYSIO_SYSIO4;

	const usart_serial_options_t uart_serial_options = {
			.baudrate = USART_SERIAL_EXAMPLE_BAUDRATE,
			.charlength = USART_SERIAL_CHAR_LENGTH,
			.paritytype = USART_SERIAL_PARITY,
			.stopbits = USART_SERIAL_STOP_BIT,
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(CONSOLE_UART_ID);
	stdio_serial_init(CONSOLE_UART, &uart_serial_options);

	/* Specify that stdout should not be buffered. */
	setbuf(stdout, NULL);
}

static void configure_input(void)
{
	/* Configure speed sensor input */
	pio_configure(SPEED_SENSOR_PIO, PIO_INPUT, SPEED_SENSOR_PIO_IDX_MASK, PIO_DEFAULT);
	pio_set_debounce_filter(SPEED_SENSOR_PIO, SPEED_SENSOR_PIO_IDX_MASK, 60);
	pio_handler_set(SPEED_SENSOR_PIO, SPEED_SENSOR_PIO_ID, SPEED_SENSOR_PIO_IDX_MASK, PIO_IT_FALL_EDGE, &speed_sensor_callback);
	pio_enable_interrupt(SPEED_SENSOR_PIO, SPEED_SENSOR_PIO_IDX_MASK);
	pio_get_interrupt_status(SPEED_SENSOR_PIO);
	NVIC_EnableIRQ(SPEED_SENSOR_PIO_ID);
	NVIC_SetPriority(SPEED_SENSOR_PIO_ID, 4);
}

/************************************************************************/
/* port lvgl                                                            */
/************************************************************************/

void my_flush_cb(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
	ili9341_set_top_left_limit(area->x1, area->y1);
	ili9341_set_bottom_right_limit(area->x2, area->y2);
	ili9341_copy_pixels_to_screen(color_p, (area->x2 + 1 - area->x1) * (area->y2 + 1 - area->y1));

	/* IMPORTANT!!!
	 * Inform the graphics library that you are ready with the flushing*/
	lv_disp_flush_ready(disp_drv);
}

void my_input_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
	int px, py, pressed;

	if (readPoint(&px, &py))
		data->state = LV_INDEV_STATE_PRESSED;
	else
		data->state = LV_INDEV_STATE_RELEASED;

	data->point.x = py;
	data->point.y = 320 - px;
}

void configure_lvgl(void)
{
	lv_init();
	lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, LV_HOR_RES_MAX * LV_VER_RES_MAX);

	lv_disp_drv_init(&disp_drv);			 /*Basic initialization*/
	disp_drv.draw_buf = &disp_buf;		 /*Set an initialized buffer*/
	disp_drv.flush_cb = my_flush_cb;	 /*Set a flush callback to draw to the display*/
	disp_drv.hor_res = LV_HOR_RES_MAX; /*Set the horizontal resolution in pixels*/
	disp_drv.ver_res = LV_VER_RES_MAX; /*Set the vertical resolution in pixels*/

	lv_disp_t *disp;
	disp = lv_disp_drv_register(&disp_drv); /*Register the driver and save the created display objects*/

	/* Init input on LVGL */
	lv_indev_drv_init(&indev_drv);
	indev_drv.type = LV_INDEV_TYPE_POINTER;
	indev_drv.read_cb = my_input_read;
	lv_indev_t *my_indev = lv_indev_drv_register(&indev_drv);
}

void create_initial_tasks(void)
{
	/* Create task to general control of the application */
	xTaskCreate(task_main, "main", TASK_MAIN_STACK_SIZE, NULL, TASK_MAIN_STACK_PRIORITY, NULL);

	/* Create task to control oled */
	xTaskCreate(task_screen_lcd, "LCD", TASK_LCD_STACK_SIZE, NULL, TASK_LCD_STACK_PRIORITY, NULL);

	/* Create task to control oled */
	xTaskCreate(
			task_update_lcd,
			"lcd_label",
			TASK_LCD_LABEL_STACK_SIZE,
			NULL,
			TASK_LCD_LABEL_STACK_PRIORITY,
			&task_update_lcd_handler);

	xTaskCreate(
			task_race,
			"race",
			TASK_RACE_STACK_SIZE,
			NULL,
			TASK_RACE_STACK_PRIORITY,
			&task_race_handler);

	// xTaskCreate(
	// 		task_calories,
	// 		"calories",
	// 		TASK_CALORIES_STACK_SIZE,
	// 		NULL,
	// 		TASK_CALORIES_STACK_PRIORITY,
	// 		&task_calories_handler);

	xTaskCreate(
			task_bme280,
			"bme280",
			TASK_BME280_STACK_SIZE,
			NULL,
			TASK_BME280_STACK_PRIORITY,
			&task_bme280_handler);
}

void create_semaphores(void)
{
	xMutexLcd = xSemaphoreCreateMutex();

	xSemaphoreRtc = xSemaphoreCreateBinary();
	xSemaphoreSubmitSetup = xSemaphoreCreateBinary();
	xSemaphoreScreenSetup = xSemaphoreCreateBinary();
	xSemaphoreScreenRace = xSemaphoreCreateBinary();
	xSemaphoreScreenSummary = xSemaphoreCreateBinary();
	xSemaphoreSpeedSensor = xSemaphoreCreateBinary();
	xSemaphoreStartRace = xSemaphoreCreateBinary();
	xSemaphoreRttCount = xSemaphoreCreateBinary();
	xSemaphorePauseRace = xSemaphoreCreateBinary();
	xSemaphoreStopRace = xSemaphoreCreateBinary();
	xSemaphoreTcCount = xSemaphoreCreateBinary();
	xSemaphoreFillSummary = xSemaphoreCreateBinary();
	xSemaphoreCloseSummary = xSemaphoreCreateBinary();
	xSemaphoreBmeData = xSemaphoreCreateBinary();
	xSemaphoreResetBmeData = xSemaphoreCreateBinary();
}

void create_queues(void)
{
	xQueueLcdLabel = xQueueCreate(128, sizeof(lcd_label_t));
	xQueueRadiusUpdate = xQueueCreate(2, sizeof(float));
	xQueueLcdLabelIcon = xQueueCreate(16, sizeof(lcd_label_icon_t));
}

/************************************************************************/
/* main                                                                 */
/************************************************************************/
int main(void)
{
	/* board and sys init */
	board_init();
	sysclk_init();
	configure_console();

	/* LCd, touch and lvgl init*/
	configure_lcd();
	ili9341_set_orientation(ILI9341_FLIP_Y | ILI9341_SWITCH_XY);
	configure_touch();
	configure_lvgl();
	// configure_input();

	create_initial_tasks();
	create_semaphores();
	create_queues();

	/* Start the scheduler. */
	vTaskStartScheduler();

	while (1)
	{
	}
}
