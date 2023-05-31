/*
 * setup.h
 *
 * Created: 19/05/2022 11:54:12
 *  Author: James
 */

#include "ili9341.h"
#include "lvgl.h"
#include "styles/styles.h"

#ifndef SETUP_H_
#define SETUP_H_

#define RIM_BIKE_TYPE_0 0 // defines the type 0 of rim measurement (separate inches from cm, for example)

#define MENU_BOX_WIDTH 200 // width of menu boxes

LV_FONT_DECLARE(roboto14bold);

lv_obj_t *dropdown;
lv_obj_t *lv_calendar;
lv_obj_t *label_w_bike;
lv_obj_t *label_minute_setup;
lv_obj_t *label_hour_setup;
lv_obj_t *label_calendar;

float get_radius(int id);
void rim_dropdown_handler(lv_event_t *e);
static void up_w_bike_handler(lv_event_t *e);
static void down_w_bike_handler(lv_event_t *e);
static void up_hours_handler(lv_event_t *e);
static void down_hours_handler(lv_event_t *e);
static void up_minutes_handler(lv_event_t *e);
static void down_minutes_handler(lv_event_t *e);
void calendar_handler(lv_event_t *e);
void submit_setup_handler(lv_event_t *e);
void setup_screen_create(lv_obj_t *screen);

#endif /* SETUP_H_ */