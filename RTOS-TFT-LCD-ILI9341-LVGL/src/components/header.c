/*
 * header.c
 *
 * Created: 21/05/2022 00:08:10
 *  Author: James
 */

#include "header.h"

void header_create(lv_obj_t *screen)
{
  /* Set background color */
  lv_obj_set_style_bg_color(screen, lv_color_white(), LV_STATE_DEFAULT);

  /* Create header */
  header = lv_obj_create(screen);
  set_header_cont_style(header);

  /* Fill header with date */
  label_date_header = lv_label_create(header);
  set_header_label_style(label_date_header);
  lv_label_set_text(label_date_header, "02/06/2022");
  lv_obj_align_to(label_date_header, header, LV_ALIGN_LEFT_MID, -4, 0);

  /* Fill header with time */
  label_time_header = lv_label_create(header);
  set_header_label_style(label_time_header);
  lv_label_set_text(label_time_header, "15:54:32");
  lv_obj_align_to(label_time_header, header, LV_ALIGN_RIGHT_MID, 0, 0);
}