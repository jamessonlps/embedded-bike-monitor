/*
 * main_menu.c
 *
 * Created: 20/05/2022 17:35:41
 *  Author: James
 */

#include "img/everest.h"
#include "main_menu.h"
#include "components/header.h"

void main_menu_screen_create(lv_obj_t *screen)
{
  lv_obj_t *logo_img;

  lv_obj_t *btn_play;
  lv_obj_t *img_btn_play;
  lv_obj_t *btn_settings;
  lv_obj_t *img_btn_settings;

  static lv_obj_t *label_btn_play;
  static lv_obj_t *label_btn_settings;

  // header_create(screen);

  /* Place logo in the center of the screen */
  logo_img = lv_img_create(screen);
  lv_img_set_src(logo_img, &everest);
  lv_obj_align(logo_img, LV_ALIGN_CENTER, 0, -35);

  /* Drawn a play button */
  btn_play = lv_btn_create(screen);
  lv_obj_align_to(btn_play, logo_img, LV_ALIGN_OUT_BOTTOM_RIGHT, -55, 10);
  lv_obj_set_size(btn_play, 70, 70);
  lv_obj_set_style_bg_color(btn_play, lv_color_hex(GREEN_BACKGROUND), LV_STATE_DEFAULT);
  lv_obj_set_style_radius(btn_play, 35, LV_STATE_DEFAULT);
  lv_obj_add_event_cb(btn_play, start_race_button_handler, LV_EVENT_ALL, NULL);
  /* Drawn a play icon into the button */
  img_btn_play = lv_label_create(btn_play);
  lv_label_set_text(img_btn_play, LV_SYMBOL_PLAY);
  lv_obj_set_style_text_color(img_btn_play, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(img_btn_play, &lv_font_montserrat_40, LV_STATE_DEFAULT); // LEMBRAR DE EXCLUIR FONTES PADRÃO NÃO USADAS
  lv_obj_align_to(img_btn_play, btn_play, LV_ALIGN_CENTER, 2, 0);
  /* Drawn a play label under the button */
  label_btn_play = lv_label_create(screen);
  lv_label_set_text(label_btn_play, "PEDALAR");
  lv_obj_align_to(label_btn_play, btn_play, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);

  /* Drawn a settings button */
  btn_settings = lv_btn_create(screen);
  lv_obj_align_to(btn_settings, logo_img, LV_ALIGN_OUT_BOTTOM_LEFT, 10, 10);
  lv_obj_set_size(btn_settings, 70, 70);
  lv_obj_set_style_bg_color(btn_settings, lv_color_hex(GREEN_BACKGROUND), LV_STATE_DEFAULT);
  lv_obj_set_style_radius(btn_settings, 35, LV_STATE_DEFAULT);
  lv_obj_add_event_cb(btn_settings, open_setup_screen_handler, LV_EVENT_ALL, NULL);
  /* Drawn a setting icon into the button */
  img_btn_settings = lv_label_create(btn_settings);
  lv_label_set_text(img_btn_settings, LV_SYMBOL_SETTINGS);
  lv_obj_set_style_text_color(img_btn_settings, lv_color_white(), LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(img_btn_settings, &lv_font_montserrat_40, LV_STATE_DEFAULT); // LEMBRAR DE EXCLUIR FONTES PADRÃO NÃO USADAS
  lv_obj_align_to(img_btn_settings, btn_settings, LV_ALIGN_CENTER, 0, 0);
  /* Drawn a setting label under the button */
  label_btn_settings = lv_label_create(screen);
  lv_label_set_text(label_btn_settings, "CONFIG.");
  lv_obj_align_to(label_btn_settings, btn_settings, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
}