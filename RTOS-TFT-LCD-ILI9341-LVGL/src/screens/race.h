/*
 * race.h
 *
 * Created: 21/05/2022 15:51:50
 *  Author: James
 */

#include "lvgl.h"
#include "styles/styles.h"

#ifndef RACE_H_
#define RACE_H_

lv_obj_t *label_speed_inst;
lv_obj_t *label_speed_avg;
lv_obj_t *label_speed_max;
lv_obj_t *label_btn_play_pause;
lv_obj_t *label_btn_finish;
lv_obj_t *label_total_time;
lv_obj_t *label_calories;
lv_obj_t *label_altitude;
lv_obj_t *label_distance;
lv_obj_t *label_acceleration;

#define RACE_WIDTH_COL_GRID 120
#define RACE_HEIGHT_ROW_GRID 40

void play_pause_button_handler(lv_event_t *e);
void finish_race_button_handler(lv_event_t *e);
void race_screen_create(lv_obj_t *screen);

#endif /* RACE_H_ */