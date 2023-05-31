/*
 * main_menu.h
 *
 * Created: 20/05/2022 17:35:56
 *  Author: James
 */
#include "lvgl.h"
#include "styles/styles.h"

#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

void open_setup_screen_handler(lv_event_t *e);
void start_race_button_handler(lv_event_t *e);
void main_menu_screen_create(lv_obj_t *screen);

#endif /* MAIN_MENU_H_ */