/*
 * setup.c
 *
 * Created: 19/05/2022 12:04:10
 *  Author: James
 *
 * Fun��es que implementam a tela de configura��o do app
 */

#include "setup.h"

// bikes[9] = {9, 0.540f};
// bikes[10] = {10, 0.520f};
// bikes[11] = {11, 0.507f};
// bikes[12] = {12, 0.451f};
// bikes[13] = {13, 0.419f};
// bikes[14] = {14, 0.406f};

float get_radius(int id)
{
	switch (id)
	{
	case 0:
		return 0.635f / 2;
		break;
	case 1:
		return 0.622f / 2;
		break;
	case 2:
		return 0.599f / 2;
		break;
	case 3:
		return 0.597f / 2;
		break;
	case 4:
		return 0.590f / 2;
		break;
	case 5:
		return 0.584f / 2;
		break;
	case 6:
		return 0.571f / 2;
		break;
	case 7:
		return 0.559f / 2;
		break;
	case 8:
		return 0.547f / 2;
		break;
	}
}

void rim_dropdown_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);
	if (code == LV_EVENT_VALUE_CHANGED)
	{
		char buf[32];
		lv_dropdown_get_selected_str(obj, buf, sizeof(buf));
		printf("Option: %s\n", buf);
		printf("Option: %d\n", lv_dropdown_get_selected(obj));
		printf("Radius: %1.3f\n", get_radius(lv_dropdown_get_selected(obj)));
	}
}

static void up_w_bike_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	char *c;
	int temp;
	if (code == LV_EVENT_CLICKED)
	{
		c = lv_label_get_text(label_w_bike);
		temp = atoi(c);
		lv_label_set_text_fmt(label_w_bike, "%02d", temp + 1);
	}
}

static void down_w_bike_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	char *c;
	int temp;
	if (code == LV_EVENT_CLICKED)
	{
		c = lv_label_get_text(label_w_bike);
		temp = atoi(c);
		temp--;
		if (temp < 0)
		{
			temp = 0;
		}
		lv_label_set_text_fmt(label_w_bike, "%02d", temp);
	}
}

static void up_hours_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	char *c;
	int temp;
	if (code == LV_EVENT_CLICKED)
	{
		c = lv_label_get_text(label_hour_setup);
		temp = atoi(c);
		temp++;
		if (temp > 23)
		{
			temp = 0;
		}
		lv_label_set_text_fmt(label_hour_setup, "%02d", temp);
	}
}

static void down_hours_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	char *c;
	int temp;
	if (code == LV_EVENT_CLICKED)
	{
		c = lv_label_get_text(label_hour_setup);
		temp = atoi(c);
		temp--;
		if (temp < 0)
		{
			temp = 23;
		}
		lv_label_set_text_fmt(label_hour_setup, "%02d", temp);
	}
}

static void up_minutes_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	char *c;
	int temp;
	if (code == LV_EVENT_CLICKED)
	{
		c = lv_label_get_text(label_minute_setup);
		temp = atoi(c);
		temp++;
		if (temp > 59)
		{
			temp = 0;
		}
		lv_label_set_text_fmt(label_minute_setup, "%02d", temp);
	}
}

static void down_minutes_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	char *c;
	int temp;
	if (code == LV_EVENT_CLICKED)
	{
		c = lv_label_get_text(label_minute_setup);
		temp = atoi(c);
		temp--;
		if (temp < 0)
		{
			temp = 59;
		}
		lv_label_set_text_fmt(label_minute_setup, "%02d", temp);
	}
}

void calendar_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_current_target(e);

	if (code == LV_EVENT_VALUE_CHANGED)
	{
		lv_calendar_date_t date;
		if (lv_calendar_get_pressed_date(obj, &date))
		{
			lv_label_set_text_fmt(label_calendar, "DATA ATUAL: %02d/%02d/%04d", date.day, date.month, date.year);
			lv_calendar_set_today_date(lv_calendar, date.year, date.month, date.day);
		}
	}
}

void setup_screen_create(lv_obj_t *screen)
{
	lv_obj_t *label;

	/* containers to put its children in a flex row display */
	lv_obj_t *cont_w_bike;
	lv_obj_t *cont_hour_setup;
	lv_obj_t *cont_minutes_setup;

	lv_obj_t *btn_up_w_bike;
	lv_obj_t *btn_down_w_bike;
	lv_obj_t *btn_up_hour;
	lv_obj_t *btn_down_hour;
	lv_obj_t *btn_up_minutes;
	lv_obj_t *btn_down_minutes;

	/* Create a Tab view object */
	lv_obj_t *tabview;
	tabview = lv_tabview_create(screen, LV_DIR_TOP, 50);

	/* Set background color */
	lv_obj_set_style_bg_color(tabview, lv_color_white(), 0);

	/* Add style to bottom button */
	lv_obj_t *btn_submit_setup;
	btn_submit_setup = lv_btn_create(tabview);
	set_button_bottom_style(btn_submit_setup);
	lv_obj_set_style_height(btn_submit_setup, 40, LV_STATE_DEFAULT);
	lv_obj_set_style_width(btn_submit_setup, LV_HOR_RES, NULL);
	lv_obj_add_event_cb(btn_submit_setup, submit_setup_handler, LV_EVENT_ALL, NULL);

	/* Add a label on the button*/
	lv_obj_t *label_btn_submit = lv_label_create(btn_submit_setup);
	lv_label_set_text(label_btn_submit, "SALVAR ESCOLHAS");
	lv_obj_center(label_btn_submit);
	lv_obj_align_to(btn_submit_setup, tabview, LV_ALIGN_BOTTOM_MID, 0, 0);

	/*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
	lv_obj_t *tab1 = lv_tabview_add_tab(tabview, "BIKE");
	lv_obj_t *tab2 = lv_tabview_add_tab(tabview, "HORA");
	lv_obj_t *tab3 = lv_tabview_add_tab(tabview, "DATA");

	lv_obj_t *tab_btns = lv_tabview_get_tab_btns(tabview);
	lv_obj_set_style_bg_color(tab_btns, lv_color_hex(GREEN_BACKGROUND), LV_PART_ITEMS | LV_STATE_CHECKED);
	lv_obj_set_style_border_side(tab_btns, LV_BORDER_SIDE_BOTTOM, LV_PART_ITEMS | LV_STATE_CHECKED);
	lv_obj_set_style_border_color(tab_btns, lv_color_hex(GREEN_BACKGROUND), LV_PART_ITEMS | LV_STATE_CHECKED);
	lv_obj_set_style_text_color(tab_btns, lv_color_white(), LV_PART_ITEMS | LV_STATE_CHECKED);

	/************************************************************************/
	/* Configure tab 1 view => BIKE setup                                   */
	/************************************************************************/

	/* Configure display flex */
	lv_obj_set_flex_flow(tab1, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(tab1, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	/* Configure dropdown for rim bike */
	label = lv_label_create(tab1);
	lv_label_set_text(label, "ARO DA BICILETA");
	// set_label_title_style(label);
	dropdown = lv_dropdown_create(tab1);
	lv_dropdown_set_options(dropdown, "28x1 1/2 3 700B\n"
																		"700C e 29\"\n"
																		"26x1.125 e 26x1.375\n"
																		"26x1 1/4 e 26x1 3/8\n"
																		"26x1 3/8 (EA3)\n"
																		"26x1 1/2 e 650B\n"
																		"26x1, 26x1 3/4 e 650C\n"
																		"26x1.0 a 26x2.5\n"
																		"24x1 1/8 e 24x1 3/8");
	lv_obj_set_style_min_width(dropdown, 200, NULL);
	lv_obj_add_event_cb(dropdown, rim_dropdown_handler, LV_EVENT_ALL, NULL);

	/* Configure spin box for the weight bike */
	label = lv_label_create(tab1);
	lv_label_set_text(label, "SEU PESO (KG)");

	/* Create a container to use flex row */
	cont_w_bike = lv_obj_create(tab1);
	lv_obj_set_flex_flow(cont_w_bike, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(cont_w_bike, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
	lv_obj_set_size(cont_w_bike, 210, 40);
	lv_obj_set_style_pad_all(cont_w_bike, 0, NULL);
	lv_obj_set_style_border_width(cont_w_bike, 0, NULL);

	/* Creates the first button to be positioned at the beginning */
	btn_up_w_bike = lv_btn_create(cont_w_bike);

	/* Label contains the weight bike value */
	label_w_bike = lv_label_create(cont_w_bike);
	lv_label_set_text(label_w_bike, "70");

	lv_coord_t h = 38;

	lv_obj_set_size(btn_up_w_bike, h, h);
	lv_obj_set_style_bg_img_src(btn_up_w_bike, LV_SYMBOL_PLUS, 0);
	lv_obj_set_style_bg_color(btn_up_w_bike, lv_color_hex(GREEN_BACKGROUND), 0);
	lv_obj_add_event_cb(btn_up_w_bike, up_w_bike_handler, LV_EVENT_ALL, NULL);

	/* Creates the second button to control the weight bike value */
	btn_down_w_bike = lv_btn_create(cont_w_bike);
	lv_obj_set_size(btn_down_w_bike, h, h);
	lv_obj_set_flex_align(btn_down_w_bike, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_style_bg_img_src(btn_down_w_bike, LV_SYMBOL_MINUS, 0);
	lv_obj_set_style_bg_color(btn_down_w_bike, lv_color_hex(GREEN_BACKGROUND), 0);
	lv_obj_add_event_cb(btn_down_w_bike, down_w_bike_handler, LV_EVENT_ALL, NULL);

	/************************************************************************/
	/* Configure tab 2 view => CLOCK setup                                  */
	/************************************************************************/

	/* Configure display flex */
	lv_obj_set_flex_flow(tab2, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(tab2, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	/* Configure title for the hour setup */
	label = lv_label_create(tab2);
	lv_label_set_text(label, "HORA");

	/* Create a container to use flex row */
	cont_hour_setup = lv_obj_create(tab2);
	lv_obj_set_flex_flow(cont_hour_setup, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(cont_hour_setup, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
	lv_obj_set_size(cont_hour_setup, 210, 40);
	lv_obj_set_style_pad_all(cont_hour_setup, 0, NULL);
	lv_obj_set_style_border_width(cont_hour_setup, 0, NULL);

	/* Creates the first button to be positioned at the beginning */
	btn_down_hour = lv_btn_create(cont_hour_setup);

	/* Label contains the hour value */
	label_hour_setup = lv_label_create(cont_hour_setup);
	lv_label_set_text(label_hour_setup, "12");

	lv_obj_set_size(btn_down_hour, h, h);
	lv_obj_set_style_bg_img_src(btn_down_hour, LV_SYMBOL_MINUS, 0);
	lv_obj_add_event_cb(btn_down_hour, down_hours_handler, LV_EVENT_ALL, NULL);
	lv_obj_set_style_bg_color(btn_down_hour, lv_color_hex(GREEN_BACKGROUND), 0);

	/* Creates the second button to control the hour value */
	btn_up_hour = lv_btn_create(cont_hour_setup);
	lv_obj_set_size(btn_up_hour, h, h);
	lv_obj_set_flex_align(btn_up_hour, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_style_bg_img_src(btn_up_hour, LV_SYMBOL_PLUS, 0);
	lv_obj_set_style_bg_color(btn_up_hour, lv_color_hex(GREEN_BACKGROUND), LV_STATE_DEFAULT);
	lv_obj_add_event_cb(btn_up_hour, up_hours_handler, LV_EVENT_ALL, NULL);

	/* Configure title for the minutes setup */
	label = lv_label_create(tab2);
	lv_label_set_text(label, "MINUTOS");

	/* Create a container to use flex row */
	cont_minutes_setup = lv_obj_create(tab2);
	lv_obj_set_flex_flow(cont_minutes_setup, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(cont_minutes_setup, LV_FLEX_ALIGN_SPACE_AROUND, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
	lv_obj_set_size(cont_minutes_setup, 210, 40);
	lv_obj_set_style_pad_all(cont_minutes_setup, 0, NULL);
	lv_obj_set_style_border_width(cont_minutes_setup, 0, NULL);

	/* Creates the first button to be positioned at the beginning */
	btn_down_minutes = lv_btn_create(cont_minutes_setup);

	/* Label contains the minute value */
	label_minute_setup = lv_label_create(cont_minutes_setup);
	lv_label_set_text(label_minute_setup, "30");

	lv_obj_set_size(btn_down_minutes, h, h);
	lv_obj_set_style_bg_img_src(btn_down_minutes, LV_SYMBOL_MINUS, 0);
	lv_obj_add_event_cb(btn_down_minutes, down_minutes_handler, LV_EVENT_ALL, NULL);
	lv_obj_set_style_bg_color(btn_down_minutes, lv_color_hex(GREEN_BACKGROUND), LV_STATE_DEFAULT);

	/* Creates the second button to control the minute value */
	btn_up_minutes = lv_btn_create(cont_minutes_setup);
	lv_obj_set_size(btn_up_minutes, h, h);
	lv_obj_set_flex_align(btn_up_minutes, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_style_bg_img_src(btn_up_minutes, LV_SYMBOL_PLUS, 0);
	lv_obj_set_style_bg_color(btn_up_minutes, lv_color_hex(GREEN_BACKGROUND), LV_STATE_DEFAULT);
	lv_obj_add_event_cb(btn_up_minutes, up_minutes_handler, LV_EVENT_ALL, NULL);

	/************************************************************************/
	/* Configure tab 3 view => DATE setup                                   */
	/************************************************************************/

	/* Configure display flex */
	lv_obj_set_flex_flow(tab3, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(tab3, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	label_calendar = lv_label_create(tab3);
	lv_label_set_text(label_calendar, "SELECIONE A DATA ATUAL");
	lv_obj_set_style_pad_all(label, 0, NULL); // experimental

	lv_calendar = lv_calendar_create(tab3);
	lv_obj_set_size(lv_calendar, 190, 190);
	lv_obj_add_event_cb(lv_calendar, calendar_handler, LV_EVENT_ALL, NULL);

	lv_calendar_set_today_date(lv_calendar, 2022, 05, 23);
	lv_calendar_set_showed_date(lv_calendar, 2022, 05);

#if LV_USE_CALENDAR_HEADER_DROPDOWN
	lv_calendar_header_dropdown_create(lv_calendar);
#elif LV_USE_CALENDAR_HEADER_ARROW
	lv_calendar_header_arrow_create(lv_calendar);
#endif
	lv_calendar_set_showed_date(lv_calendar, 2022, 05);
}