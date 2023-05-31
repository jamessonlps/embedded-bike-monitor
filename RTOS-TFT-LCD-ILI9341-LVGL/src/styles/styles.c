/*
 * styles.c
 *
 * Created: 20/05/2022 12:07:59
 *  Author: James
 */

#include "styles.h"

/**
 * Define a style to label that is a legend for each
 * setup option (title)
 */
void set_label_title_style(lv_obj_t *obj)
{
	/* Create label title style */
	lv_style_init(&style_labels_title);
	lv_style_set_bg_color(&style_labels_title, lv_color_white());
	lv_style_set_text_font(&style_labels_title, &roboto14bold);
	lv_style_set_text_letter_space(&style_labels_title, 0);
	lv_style_set_text_line_space(&style_labels_title, 0);

	/* Apply the created style in the object */
	lv_obj_add_style(obj, &style_labels_title, LV_STATE_DEFAULT);
}

/**
 * Define a style to a green button in the bottom of some pages
 */
void set_button_bottom_style(lv_obj_t *obj)
{
	/* Create style */
	lv_style_init(&style_button_bottom);
	lv_style_set_bg_color(&style_button_bottom, lv_color_hex(GREEN_BACKGROUND));
	lv_style_set_radius(&style_button_bottom, 0);
	lv_style_set_height(&style_button_bottom, 30);

	/* Apply the created style */
	lv_obj_add_style(obj, &style_button_bottom, LV_STATE_DEFAULT);
}

/**
 * Define a style to the label in header (date and time)
 */
void set_header_label_style(lv_obj_t *obj)
{
	/* Create label title style */
	lv_style_init(&style_header_label);
	lv_style_set_text_font(&style_header_label, &roboto14bold);
	lv_style_set_text_color(&style_header_label, lv_color_white());
	lv_style_set_text_letter_space(&style_header_label, 0);
	lv_style_set_text_line_space(&style_header_label, 0);

	/* Apply the created style in the object */
	lv_obj_add_style(obj, &style_header_label, LV_STATE_DEFAULT);
}

/**
 * Define a style to the header container
 */
void set_header_cont_style(lv_obj_t *obj)
{
	/* Create style */
	lv_style_init(&style_header_container);
	lv_style_set_bg_color(&style_header_container, lv_color_hex(GREEN_BACKGROUND));
	lv_style_set_width(&style_header_container, 240);
	lv_style_set_height(&style_header_container, 25);
	lv_style_set_border_width(&style_header_container, 0);
	lv_style_set_radius(&style_header_container, 0);

	/* Apply the created style */
	lv_obj_add_style(obj, &style_header_container, LV_STATE_DEFAULT);

	/* Remove scroll bar */
	lv_obj_set_scrollbar_mode(obj, LV_SCROLLBAR_MODE_OFF);
}