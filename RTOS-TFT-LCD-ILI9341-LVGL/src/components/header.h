/*
 * header.h
 *
 * Created: 21/05/2022 00:08:02
 *  Author: James
 */

#include "lvgl.h"
#include "styles/styles.h"

#ifndef HEADER_H_
#define HEADER_H_

lv_obj_t *header;
lv_obj_t *label_time_header;
lv_obj_t *label_date_header;

void header_create(lv_obj_t *screen);

#endif /* HEADER_H_ */