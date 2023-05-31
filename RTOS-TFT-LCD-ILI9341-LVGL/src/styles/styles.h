/*
 * styles.h
 *
 * Created: 20/05/2022 12:08:12
 *  Author: James
 */

#include "lvgl.h"

#ifndef STYLES_H_
#define STYLES_H_

LV_FONT_DECLARE(roboto14bold);

#define GREEN_BACKGROUND 0x00F000
#define GREEN_LIGHT 0x317800
#define BLUE_LIGHT 0x1758FF
#define RED_LIGHT 0xFF0000

static lv_style_t style_labels_title;
static lv_style_t style_button_bottom;
lv_style_t style_header_label;
static lv_style_t style_header_container;

void set_label_title_style(lv_obj_t *obj);
void set_button_bottom_style(lv_obj_t *obj);
void set_header_label_style(lv_obj_t *obj);
void set_header_cont_style(lv_obj_t *obj);

#endif /* STYLES_H_ */