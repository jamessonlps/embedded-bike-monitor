/*
 * summary.c
 *
 * Created: 21/05/2022 09:59:32
 *  Author: James
 */

#include "summary.h"
#include "components/header.h"

void summary_screen_create(lv_obj_t *screen)
{
  lv_obj_t *label_time_text;
  lv_obj_t *label_time_value;

  lv_obj_t *label_page_title;
  lv_obj_t *cont_page_title;

  lv_obj_t *btn_back;
  lv_obj_t *label_btn_back;

  header_create(screen);

  static lv_coord_t col_dsc[] = {
      SUMMARY_WIDTH_COL_GRID,
      SUMMARY_WIDTH_COL_GRID,
      LV_GRID_TEMPLATE_LAST};
  static lv_coord_t row_dsc[] = {
      SUMMARY_HEIGHT_ROW_GRID,
      SUMMARY_HEIGHT_ROW_GRID,
      SUMMARY_HEIGHT_ROW_GRID,
      SUMMARY_HEIGHT_ROW_GRID,
      SUMMARY_HEIGHT_ROW_GRID,
      LV_GRID_TEMPLATE_LAST};

  /* Page title */
  cont_page_title = lv_obj_create(screen);
  lv_obj_set_style_bg_color(cont_page_title, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_align_to(cont_page_title, header, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
  lv_obj_set_size(cont_page_title, 240, 40);
  lv_obj_set_style_border_width(cont_page_title, 1, LV_STATE_DEFAULT);
  lv_obj_set_style_border_side(cont_page_title, LV_BORDER_SIDE_BOTTOM, LV_STATE_DEFAULT);
  lv_obj_set_scrollbar_mode(cont_page_title, LV_SCROLLBAR_MODE_OFF);
  label_page_title = lv_label_create(cont_page_title);
  lv_label_set_text(label_page_title, "RESUMO");
  lv_obj_center(label_page_title);

  /*Create a container with grid*/
  lv_obj_t *cont = lv_obj_create(screen);
  lv_obj_set_style_grid_column_dsc_array(cont, col_dsc, 0);
  lv_obj_set_style_grid_row_dsc_array(cont, row_dsc, 0);
  lv_obj_set_style_pad_row(cont, 15, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_column(cont, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_pad_all(cont, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_radius(cont, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(cont, 0, LV_STATE_DEFAULT);
  lv_obj_set_size(cont, 240, 200);
  lv_obj_align_to(cont, cont_page_title, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
  lv_obj_set_layout(cont, LV_LAYOUT_GRID);

  /*------- Draw the first row of the grid ---------*/
  lv_obj_t *obj = lv_obj_create(cont);
  lv_obj_set_style_bg_color(obj, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
  lv_obj_set_style_pad_all(obj, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(obj, 1, LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(obj, lv_color_black(), LV_STATE_DEFAULT);
  lv_obj_set_style_radius(obj, 10, LV_STATE_DEFAULT);

  /* Fill cell title according to column */
  lv_obj_t *lb_title = lv_label_create(obj);
  lv_label_set_text(lb_title, "TEMPO");
  lv_obj_set_style_text_font(lb_title, &lv_font_montserrat_10, LV_STATE_DEFAULT);
  lv_obj_set_style_border_side(obj, LV_BORDER_SIDE_RIGHT, LV_STATE_DEFAULT);
  lv_obj_align_to(lb_title, obj, LV_ALIGN_TOP_LEFT, 5, 0);

  /* Fill cell value */
  label_summary_total_time = lv_label_create(obj);
  lv_obj_set_style_text_font(label_summary_total_time, &lv_font_montserrat_18, LV_STATE_DEFAULT);
  lv_label_set_text(label_summary_total_time, "00:00:00");
  lv_obj_align_to(label_summary_total_time, obj, LV_ALIGN_BOTTOM_MID, 0, 0);

  lv_obj_t *obj2 = lv_obj_create(cont);
  lv_obj_set_style_bg_color(obj2, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_set_grid_cell(obj2, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
  lv_obj_set_style_pad_all(obj2, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(obj2, 1, LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(obj2, lv_color_black(), LV_STATE_DEFAULT);
  lv_obj_set_style_radius(obj2, 10, LV_STATE_DEFAULT);

  /* Fill cell title according to column */
  lb_title = lv_label_create(obj2);
  lv_label_set_text(lb_title, "DISTANCIA");
  lv_obj_set_style_text_font(lb_title, &lv_font_montserrat_10, LV_STATE_DEFAULT);
  lv_obj_set_style_border_side(obj2, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT);
  lv_obj_align_to(lb_title, obj2, LV_ALIGN_TOP_RIGHT, -5, 0);

  /* Fill cell value */
  label_summary_distance = lv_label_create(obj2);
  lv_obj_set_style_text_font(label_summary_distance, &lv_font_montserrat_18, LV_STATE_DEFAULT);
  lv_label_set_text(label_summary_distance, "00,0");

  lv_obj_t *lb_unit = lv_label_create(obj2);
  lv_label_set_text(lb_unit, "KM");
  lv_obj_align_to(label_summary_distance, obj2, LV_ALIGN_BOTTOM_MID, -15, 0);
  lv_obj_align_to(lb_unit, label_summary_distance, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, -1);

  /*------- Draw the second row of the grid ---------*/
  lv_obj_t *obj3 = lv_obj_create(cont);
  lv_obj_set_style_bg_color(obj3, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_set_grid_cell(obj3, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
  lv_obj_set_style_pad_all(obj3, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(obj3, 1, LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(obj3, lv_color_black(), LV_STATE_DEFAULT);
  lv_obj_set_style_radius(obj3, 10, LV_STATE_DEFAULT);
  /* Fill cell title according to column */
  lb_title = lv_label_create(obj3);
  lv_label_set_text(lb_title, "VEL. MEDIA");
  lv_obj_set_style_text_font(lb_title, &lv_font_montserrat_10, LV_STATE_DEFAULT);
  lv_obj_set_style_border_side(obj3, LV_BORDER_SIDE_RIGHT, LV_STATE_DEFAULT);
  lv_obj_align_to(lb_title, obj3, LV_ALIGN_TOP_LEFT, 5, 0);
  /* Fill cell value */
  label_summary_avg_speed = lv_label_create(obj3);
  lv_obj_set_style_text_font(label_summary_avg_speed, &lv_font_montserrat_18, LV_STATE_DEFAULT);
  lv_label_set_text(label_summary_avg_speed, "00,0");
  lv_obj_align_to(label_summary_avg_speed, obj3, LV_ALIGN_BOTTOM_MID, 0, 0);
  lb_unit = lv_label_create(obj3);
  lv_label_set_text(lb_unit, "KM/H");
  lv_obj_align_to(label_summary_avg_speed, obj3, LV_ALIGN_BOTTOM_MID, -15, 0);
  lv_obj_align_to(lb_unit, label_summary_avg_speed, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, -1);

  lv_obj_t *obj4 = lv_obj_create(cont);
  lv_obj_set_style_bg_color(obj4, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_set_grid_cell(obj4, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 1, 1);
  lv_obj_set_style_pad_all(obj4, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(obj4, 1, LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(obj4, lv_color_black(), LV_STATE_DEFAULT);
  lv_obj_set_style_radius(obj4, 10, LV_STATE_DEFAULT);
  /* Fill cell title according to column */
  lb_title = lv_label_create(obj4);
  lv_label_set_text(lb_title, "VEL. MAXIMA");
  lv_obj_set_style_text_font(lb_title, &lv_font_montserrat_10, LV_STATE_DEFAULT);
  lv_obj_set_style_border_side(obj4, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT);
  lv_obj_align_to(lb_title, obj4, LV_ALIGN_TOP_RIGHT, -5, 0);
  /* Fill cell value */
  label_summary_max_speed = lv_label_create(obj4);
  lv_obj_set_style_text_font(label_summary_max_speed, &lv_font_montserrat_18, LV_STATE_DEFAULT);
  lv_label_set_text(label_summary_max_speed, "00,0");
  lb_unit = lv_label_create(obj4);
  lv_label_set_text(lb_unit, "KM");
  lv_obj_align_to(label_summary_max_speed, obj4, LV_ALIGN_BOTTOM_MID, -15, 0);
  lv_obj_align_to(lb_unit, label_summary_max_speed, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, -1);

  /*------- Draw the third row of the grid ---------*/
  lv_obj_t *obj5 = lv_obj_create(cont);
  lv_obj_set_style_bg_color(obj5, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_set_grid_cell(obj5, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 2, 1);
  lv_obj_set_style_pad_all(obj5, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(obj5, 1, LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(obj5, lv_color_black(), LV_STATE_DEFAULT);
  lv_obj_set_style_radius(obj5, 10, LV_STATE_DEFAULT);
  /* Fill cell title according to column */
  lb_title = lv_label_create(obj5);
  lv_label_set_text(lb_title, "ELEVACAO MIN.");
  lv_obj_set_style_text_font(lb_title, &lv_font_montserrat_10, LV_STATE_DEFAULT);
  lv_obj_set_style_border_side(obj5, LV_BORDER_SIDE_RIGHT, LV_STATE_DEFAULT);
  lv_obj_align_to(lb_title, obj5, LV_ALIGN_TOP_LEFT, 5, 0);
  /* Fill cell value */
  label_summary_min_altitude = lv_label_create(obj5);
  lv_obj_set_style_text_font(label_summary_min_altitude, &lv_font_montserrat_18, LV_STATE_DEFAULT);
  lv_label_set_text(label_summary_min_altitude, "000");
  lv_obj_align_to(label_summary_min_altitude, obj5, LV_ALIGN_BOTTOM_MID, 0, 0);
  lb_unit = lv_label_create(obj5);
  lv_label_set_text(lb_unit, "M");
  lv_obj_align_to(label_summary_min_altitude, obj5, LV_ALIGN_BOTTOM_MID, -15, 0);
  lv_obj_align_to(lb_unit, label_summary_min_altitude, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, -1);

  lv_obj_t *obj6 = lv_obj_create(cont);
  lv_obj_set_style_bg_color(obj6, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_set_grid_cell(obj6, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 2, 1);
  lv_obj_set_style_pad_all(obj6, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(obj6, 1, LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(obj6, lv_color_black(), LV_STATE_DEFAULT);
  lv_obj_set_style_radius(obj6, 10, LV_STATE_DEFAULT);
  /* Fill cell title according to column */
  lb_title = lv_label_create(obj6);
  lv_label_set_text(lb_title, "ELEVACAO MAX.");
  lv_obj_set_style_text_font(lb_title, &lv_font_montserrat_10, LV_STATE_DEFAULT);
  lv_obj_set_style_border_side(obj6, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT);
  lv_obj_align_to(lb_title, obj6, LV_ALIGN_TOP_RIGHT, -5, 0);
  /* Fill cell value */
  label_summary_max_altitude = lv_label_create(obj6);
  lv_obj_set_style_text_font(label_summary_max_altitude, &lv_font_montserrat_18, LV_STATE_DEFAULT);
  lv_label_set_text(label_summary_max_altitude, "000");
  lb_unit = lv_label_create(obj6);
  lv_label_set_text(lb_unit, "M");
  lv_obj_align_to(label_summary_max_altitude, obj6, LV_ALIGN_BOTTOM_MID, -15, 0);
  lv_obj_align_to(lb_unit, label_summary_max_altitude, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, -1);

  /*------- Draw the fourth row of the grid ---------*/
  lv_obj_t *obj7 = lv_obj_create(cont);
  lv_obj_set_style_bg_color(obj7, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_set_grid_cell(obj7, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 3, 1);
  lv_obj_set_style_pad_all(obj7, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(obj7, 1, LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(obj7, lv_color_black(), LV_STATE_DEFAULT);
  lv_obj_set_style_radius(obj7, 10, LV_STATE_DEFAULT);
  /* Fill cell title according to column */
  lb_title = lv_label_create(obj7);
  lv_label_set_text(lb_title, "CALORIAS");
  lv_obj_set_style_text_font(lb_title, &lv_font_montserrat_10, LV_STATE_DEFAULT);
  lv_obj_set_style_border_side(obj7, LV_BORDER_SIDE_RIGHT, LV_STATE_DEFAULT);
  lv_obj_align_to(lb_title, obj7, LV_ALIGN_TOP_LEFT, 5, 0);
  /* Fill cell value */
  label_summary_calories = lv_label_create(obj7);
  lv_obj_set_style_text_font(label_summary_calories, &lv_font_montserrat_18, LV_STATE_DEFAULT);
  lv_label_set_text(label_summary_calories, "000");
  lv_obj_align_to(label_summary_calories, obj7, LV_ALIGN_BOTTOM_MID, 0, 0);
  lb_unit = lv_label_create(obj7);
  lv_label_set_text(lb_unit, "KCAL");
  lv_obj_align_to(label_summary_calories, obj7, LV_ALIGN_BOTTOM_MID, -15, 0);
  lv_obj_align_to(lb_unit, label_summary_calories, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, -1);

  lv_obj_t *obj8 = lv_obj_create(cont);
  lv_obj_set_style_bg_color(obj8, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_set_grid_cell(obj8, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 3, 1);
  lv_obj_set_style_pad_all(obj8, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(obj8, 1, LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(obj8, lv_color_black(), LV_STATE_DEFAULT);
  lv_obj_set_style_radius(obj8, 10, LV_STATE_DEFAULT);
  /* Fill cell title according to column */
  lb_title = lv_label_create(obj8);
  lv_label_set_text(lb_title, "GANHO DE ELEV.");
  lv_obj_set_style_text_font(lb_title, &lv_font_montserrat_10, LV_STATE_DEFAULT);
  lv_obj_set_style_border_side(obj8, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT);
  lv_obj_align_to(lb_title, obj8, LV_ALIGN_TOP_RIGHT, -5, 0);
  /* Fill cell value */
  label_summary_altitude_gain = lv_label_create(obj8);
  lv_obj_set_style_text_font(label_summary_altitude_gain, &lv_font_montserrat_18, LV_STATE_DEFAULT);
  lv_label_set_text(label_summary_altitude_gain, "00");
  lb_unit = lv_label_create(obj8);
  lv_label_set_text(lb_unit, "M");
  lv_obj_align_to(label_summary_altitude_gain, obj8, LV_ALIGN_BOTTOM_MID, -15, 0);
  lv_obj_align_to(lb_unit, label_summary_altitude_gain, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, -1);

  /*------- Draw the fifth row of the grid ---------*/
  lv_obj_t *obj9 = lv_obj_create(cont);
  lv_obj_set_style_bg_color(obj9, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_set_grid_cell(obj9, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 4, 1);
  lv_obj_set_style_pad_all(obj9, 0, LV_STATE_DEFAULT);
  lv_obj_set_style_border_width(obj9, 1, LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(obj9, lv_color_black(), LV_STATE_DEFAULT);
  lv_obj_set_style_radius(obj9, 10, LV_STATE_DEFAULT);
  /* Fill cell title according to column */
  lb_title = lv_label_create(obj9);
  lv_label_set_text(lb_title, "TEMP. MEDIA");
  lv_obj_set_style_text_font(lb_title, &lv_font_montserrat_10, LV_STATE_DEFAULT);
  lv_obj_set_style_border_side(obj9, LV_BORDER_SIDE_RIGHT, LV_STATE_DEFAULT);
  lv_obj_align_to(lb_title, obj9, LV_ALIGN_TOP_LEFT, 5, 0);
  /* Fill cell value */
  label_summary_avg_temp = lv_label_create(obj9);
  lv_obj_set_style_text_font(label_summary_avg_temp, &lv_font_montserrat_18, LV_STATE_DEFAULT);
  lv_label_set_text(label_summary_avg_temp, "00,0");
  lv_obj_align_to(label_summary_avg_temp, obj9, LV_ALIGN_BOTTOM_MID, 0, 0);
  lb_unit = lv_label_create(obj9);
  lv_label_set_text(lb_unit, "°C");
  lv_obj_align_to(label_summary_avg_temp, obj9, LV_ALIGN_BOTTOM_MID, -15, 0);
  lv_obj_align_to(lb_unit, label_summary_avg_temp, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, -1);

  /* Fill each cell from grid */
  // fill_cell(cont, label_summary_total_time, 0, 0, "TEMPO", "00:00:00", NULL, 0);
  // fill_cell(cont, label_summary_distance, 1, 0, "DISTANCIA", "00,0", "KM", 1);
  // fill_cell(cont, label_summary_avg_speed, 0, 1, "VEL. MEDIA", "00,0", "KM/H", 1);
  // fill_cell(cont, label_summary_max_speed, 1, 1, "VEL. MAXIMA", "00", "KM/H", 1);
  // fill_cell(cont, label_summary_min_altitude, 0, 2, "ELEVACAO MIN.", "000", "M", 1);
  // fill_cell(cont, label_summary_max_altitude, 1, 2, "ELEVACAO MAX.", "000", "M", 1);
  // fill_cell(cont, label_summary_calories, 0, 3, "CALORIAS", "000", "KCAL", 1);
  // fill_cell(cont, label_summary_altitude_gain, 1, 3, "GANHO DE ELEV.", "00", "M", 1);
  // fill_cell(cont, label_summary_avg_temp, 0, 4, "TEMPER. MEDIA", "00,0", "°C", 1);

  /* Button to return to main page */
  btn_back = lv_btn_create(screen);
  set_button_bottom_style(btn_back);
  lv_obj_align_to(btn_back, screen, LV_ALIGN_BOTTOM_LEFT, 0, -15);
  lv_obj_set_size(btn_back, 240, 45);
  label_btn_back = lv_label_create(btn_back);
  lv_label_set_text(label_btn_back, "VOLTAR AO INICIO");
  lv_obj_set_style_text_color(label_btn_back, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_center(label_btn_back);
  lv_obj_add_event_cb(btn_back, close_summary_button_handler, LV_EVENT_ALL, NULL);
}