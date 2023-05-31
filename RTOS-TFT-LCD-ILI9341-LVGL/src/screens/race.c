/*
 * race.c
 *
 * Created: 21/05/2022 15:52:02
 *  Author: James
 */

#include "race.h"
#include "components/header.h"

void race_screen_create(lv_obj_t *screen)
{
    static lv_obj_t *label_speed_avg_text;
    static lv_obj_t *label_speed_max_text;

    lv_obj_t *cont_speed_inst;
    lv_obj_t *cont_speed_avg;
    lv_obj_t *cont_speed_max;
    lv_obj_t *label_speed_unit;

    lv_obj_t *btn_play_pause;
    lv_obj_t *btn_finish;

    header_create(screen);

    lv_coord_t col_dsc1[] = {
        RACE_WIDTH_COL_GRID,
        RACE_WIDTH_COL_GRID,
        LV_GRID_TEMPLATE_LAST};
    lv_coord_t row_dsc1[] = {
        RACE_HEIGHT_ROW_GRID,
        LV_GRID_TEMPLATE_LAST};

    lv_coord_t col_dsc2[] = {
        RACE_WIDTH_COL_GRID,
        RACE_WIDTH_COL_GRID,
        LV_GRID_TEMPLATE_LAST};
    lv_coord_t row_dsc2[] = {
        RACE_HEIGHT_ROW_GRID,
        LV_GRID_TEMPLATE_LAST};

    /*Create a container with grid*/
    lv_obj_t *container1 = lv_obj_create(screen);
    lv_obj_set_style_grid_column_dsc_array(container1, col_dsc1, 0);
    lv_obj_set_style_grid_row_dsc_array(container1, row_dsc1, 0);
    lv_obj_set_style_pad_row(container1, 6, LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(container1, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(container1, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(container1, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(container1, 0, LV_STATE_DEFAULT);
    lv_obj_set_size(container1, 240, 40);
    lv_obj_align_to(container1, header, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_obj_set_layout(container1, LV_LAYOUT_GRID);

    /*------- Draw the top grid in the screen ---------*/
    lv_obj_t *obj = lv_obj_create(container1);
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
    label_total_time = lv_label_create(screen);
    lv_obj_set_style_text_font(label_total_time, &lv_font_montserrat_18, LV_STATE_DEFAULT);
    lv_label_set_text(label_total_time, "00:00");
    lv_obj_align_to(label_total_time, obj, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_obj_t *obj2 = lv_obj_create(container1);
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
    label_distance = lv_label_create(screen);
    lv_obj_set_style_text_font(label_distance, &lv_font_montserrat_18, LV_STATE_DEFAULT);
    lv_label_set_text(label_distance, "13.2");

    lv_obj_t *lb_unit = lv_label_create(obj2);
    lv_label_set_text(lb_unit, "KM");
    lv_obj_align_to(label_distance, obj2, LV_ALIGN_BOTTOM_MID, -15, 0);
    lv_obj_align_to(lb_unit, label_distance, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, -1);

    /* Fill each cell from grid */
    // fill_cell_r(screen, container1, label_total_time, 0, 0, "TEMPO", "01:34:22", NULL, 0);
    // fill_cell_r(screen, container1, label_distance, 1, 0, "DISTANCIA", "13.2", "KM", 1);

    /* Draw display circular of current speed */
    cont_speed_inst = lv_obj_create(screen);
    lv_obj_set_size(cont_speed_inst, 120, 120);
    lv_obj_set_style_border_width(cont_speed_inst, 1, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(cont_speed_inst, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cont_speed_inst, 60, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cont_speed_inst, lv_color_white(), LV_STATE_DEFAULT);
    lv_obj_align_to(cont_speed_inst, container1, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    // lv_obj_set_grid_cell(cont_speed_inst, LV_GRID_ALIGN_CENTER, 0, 2, LV_GRID_ALIGN_CENTER, 1, 2);
    label_speed_inst = lv_label_create(cont_speed_inst);
    lv_obj_set_style_text_font(label_speed_inst, &lv_font_montserrat_48, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label_speed_inst, lv_color_hex(GREEN_BACKGROUND), LV_STATE_DEFAULT);
    lv_obj_align_to(label_speed_inst, cont_speed_inst, LV_ALIGN_CENTER, 3, -10);
    lv_label_set_text(label_speed_inst, "22");
    label_speed_unit = lv_label_create(cont_speed_inst);
    lv_obj_set_style_text_font(label_speed_unit, &lv_font_montserrat_10, LV_STATE_DEFAULT);
    lv_obj_align_to(label_speed_unit, label_speed_inst, LV_ALIGN_OUT_RIGHT_BOTTOM, 7, -10);
    lv_label_set_text(label_speed_unit, "KM/H");
    label_acceleration = lv_label_create(cont_speed_inst);
    lv_obj_set_style_text_font(label_acceleration, &lv_font_montserrat_18, LV_STATE_DEFAULT);
    lv_label_set_text(label_acceleration, LV_SYMBOL_MINUS);
    lv_obj_set_style_text_color(label_acceleration, lv_color_hex(BLUE_LIGHT), LV_STATE_DEFAULT);
    lv_obj_align_to(label_acceleration, label_speed_inst, LV_ALIGN_OUT_BOTTOM_MID, 20, 5);

    /* Draw display circular of average speed */
    cont_speed_avg = lv_obj_create(screen);
    lv_obj_set_size(cont_speed_avg, 76, 76);
    lv_obj_set_style_border_width(cont_speed_avg, 1, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(cont_speed_avg, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cont_speed_avg, 38, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cont_speed_avg, lv_color_white(), LV_STATE_DEFAULT);
    lv_obj_align_to(cont_speed_avg, cont_speed_inst, LV_ALIGN_OUT_RIGHT_BOTTOM, -20, 45);
    label_speed_avg = lv_label_create(cont_speed_avg);
    lv_obj_set_style_text_font(label_speed_avg, &lv_font_montserrat_18, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label_speed_avg, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_align_to(label_speed_avg, cont_speed_avg, LV_ALIGN_CENTER, 2, 12);
    lv_label_set_text(label_speed_avg, "40");
    label_speed_avg_text = lv_label_create(cont_speed_avg);
    lv_obj_set_style_text_font(label_speed_avg_text, &lv_font_montserrat_10, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label_speed_avg_text, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label_speed_avg_text, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT);
    lv_obj_align_to(label_speed_avg_text, cont_speed_avg, LV_ALIGN_TOP_MID, -7, 0);
    lv_label_set_text(label_speed_avg_text, "VEL.\nMEDIA");

    /* Draw display circular of max speed */
    cont_speed_max = lv_obj_create(screen);
    lv_obj_set_size(cont_speed_max, 76, 76);
    lv_obj_set_style_border_width(cont_speed_max, 1, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(cont_speed_max, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cont_speed_max, 38, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cont_speed_max, lv_color_white(), LV_STATE_DEFAULT);
    lv_obj_align_to(cont_speed_max, cont_speed_inst, LV_ALIGN_OUT_LEFT_BOTTOM, 20, 45);
    label_speed_max = lv_label_create(cont_speed_max);
    lv_obj_set_style_text_font(label_speed_max, &lv_font_montserrat_18, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label_speed_max, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_align_to(label_speed_max, cont_speed_max, LV_ALIGN_CENTER, 5, 12);
    lv_label_set_text(label_speed_max, "22,6");
    label_speed_max_text = lv_label_create(cont_speed_max);
    lv_obj_set_style_text_font(label_speed_max_text, &lv_font_montserrat_10, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label_speed_max_text, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(label_speed_max_text, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT);
    lv_obj_align_to(label_speed_max_text, cont_speed_max, LV_ALIGN_TOP_MID, -4, 0);
    lv_label_set_text(label_speed_max_text, "VEL.\nMAX");

    /*Create a container with grid*/
    lv_obj_t *container2 = lv_obj_create(screen);
    lv_obj_set_style_grid_column_dsc_array(container2, col_dsc2, 0);
    lv_obj_set_style_grid_row_dsc_array(container2, row_dsc2, 0);
    lv_obj_set_style_pad_row(container2, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(container2, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(container2, 0, LV_STATE_DEFAULT);
    // lv_obj_set_style_pad_top(container2, 10, LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(container2, LV_SCROLLBAR_MODE_OFF); // Ainda tá com scrool vertical
    lv_obj_set_style_radius(container2, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(container2, 0, LV_STATE_DEFAULT);
    lv_obj_set_size(container2, 240, 40);
    lv_obj_align_to(container2, cont_speed_max, LV_ALIGN_OUT_BOTTOM_LEFT, -5, 8);
    lv_obj_set_layout(container2, LV_LAYOUT_GRID);

    /*---------- Create a grid of labels ----------*/

    lv_obj_t *obj3 = lv_obj_create(container2);
    lv_obj_set_style_bg_color(obj3, lv_color_white(), LV_STATE_DEFAULT);
    lv_obj_set_grid_cell(obj3, LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_obj_set_style_pad_all(obj3, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj3, 1, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(obj3, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj3, 10, LV_STATE_DEFAULT);

    /* Fill cell title according to column */
    lb_title = lv_label_create(obj3);
    lv_label_set_text(lb_title, "ALTITUDE");
    lv_obj_set_style_text_font(lb_title, &lv_font_montserrat_10, LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(obj3, LV_BORDER_SIDE_RIGHT, LV_STATE_DEFAULT);
    lv_obj_align_to(lb_title, obj3, LV_ALIGN_TOP_LEFT, 5, 0);

    /* Fill cell value */
    label_altitude = lv_label_create(screen);
    lv_obj_set_style_text_font(label_altitude, &lv_font_montserrat_18, LV_STATE_DEFAULT);
    lv_label_set_text(label_altitude, "00");
    lv_obj_align_to(label_altitude, obj3, LV_ALIGN_BOTTOM_MID, 0, 0);

    lb_unit = lv_label_create(obj3);
    lv_label_set_text(lb_unit, "M");
    lv_obj_align_to(label_altitude, obj3, LV_ALIGN_BOTTOM_MID, -15, 0);
    lv_obj_align_to(lb_unit, label_altitude, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, -1);

    lv_obj_t *obj4 = lv_obj_create(container2);
    lv_obj_set_style_bg_color(obj4, lv_color_white(), LV_STATE_DEFAULT);
    lv_obj_set_grid_cell(obj4, LV_GRID_ALIGN_STRETCH, 1, 1, LV_GRID_ALIGN_STRETCH, 0, 1);
    lv_obj_set_style_pad_all(obj4, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(obj4, 1, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(obj4, lv_color_black(), LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj4, 10, LV_STATE_DEFAULT);

    /* Fill cell title according to column */
    lb_title = lv_label_create(obj4);
    lv_label_set_text(lb_title, "CALORIAS");
    lv_obj_set_style_text_font(lb_title, &lv_font_montserrat_10, LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(obj4, LV_BORDER_SIDE_NONE, LV_STATE_DEFAULT);
    lv_obj_align_to(lb_title, obj4, LV_ALIGN_TOP_RIGHT, -5, 0);

    /* Fill cell value */
    label_calories = lv_label_create(screen);
    lv_obj_set_style_text_font(label_calories, &lv_font_montserrat_18, LV_STATE_DEFAULT);
    lv_label_set_text(label_calories, "00");

    lb_unit = lv_label_create(obj4);
    lv_label_set_text(lb_unit, "KCAL");
    lv_obj_align_to(label_calories, obj4, LV_ALIGN_BOTTOM_MID, -15, 0);
    lv_obj_align_to(lb_unit, label_calories, LV_ALIGN_OUT_RIGHT_BOTTOM, 10, -1);

    /* Create play/pause button */
    btn_play_pause = lv_btn_create(screen);
    set_button_bottom_style(btn_play_pause);
    lv_obj_align_to(btn_play_pause, container2, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 2);
    lv_obj_set_style_width(btn_play_pause, 119, LV_STATE_DEFAULT);
    lv_obj_set_style_height(btn_play_pause, 40, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(btn_play_pause, play_pause_button_handler, LV_EVENT_ALL, NULL);
    label_btn_play_pause = lv_label_create(btn_play_pause);
    lv_obj_set_style_text_font(label_btn_play_pause, &lv_font_montserrat_18, LV_STATE_DEFAULT);
    lv_label_set_text(label_btn_play_pause, LV_SYMBOL_PAUSE);
    lv_obj_set_style_text_color(label_btn_play_pause, lv_color_white(), LV_STATE_DEFAULT);
    lv_obj_align_to(label_btn_play_pause, btn_play_pause, LV_ALIGN_CENTER, 0, 0);

    /* Create finish button */
    btn_finish = lv_btn_create(screen);
    set_button_bottom_style(btn_finish);
    lv_obj_align_to(btn_finish, btn_play_pause, LV_ALIGN_OUT_RIGHT_MID, 2, -5);
    lv_obj_set_style_width(btn_finish, 120, LV_STATE_DEFAULT);
    lv_obj_set_style_height(btn_finish, 40, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(btn_finish, finish_race_button_handler, LV_EVENT_ALL, NULL);
    label_btn_finish = lv_label_create(btn_finish);
    lv_obj_set_style_text_font(label_btn_finish, &lv_font_montserrat_18, LV_STATE_DEFAULT);
    lv_label_set_text(label_btn_finish, LV_SYMBOL_STOP);
    lv_obj_set_style_text_color(label_btn_finish, lv_color_white(), LV_STATE_DEFAULT);
    lv_obj_align_to(label_btn_finish, btn_finish, LV_ALIGN_CENTER, 0, 0);
}