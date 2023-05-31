/*
 * summary.h
 *
 * Created: 21/05/2022 09:59:42
 *  Author: James
 */

#include "lvgl.h"
#include "styles/styles.h"

#ifndef SUMMARY_H_
#define SUMMARY_H_

#define SUMMARY_WIDTH_COL_GRID 120
#define SUMMARY_HEIGHT_ROW_GRID 40

lv_obj_t *label_summary_max_speed;
lv_obj_t *label_summary_avg_speed;
lv_obj_t *label_summary_total_time;
lv_obj_t *label_summary_calories;
lv_obj_t *label_summary_distance;
lv_obj_t *label_summary_min_altitude;
lv_obj_t *label_summary_max_altitude;
lv_obj_t *label_summary_altitude_gain;
lv_obj_t *label_summary_avg_temp;

void summary_screen_create(lv_obj_t *screen);
void close_summary_button_handler(lv_event_t *e);

#endif /* SUMMARY_H_ */