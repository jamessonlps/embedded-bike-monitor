/*******************************************************************************
 * Size: 14 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#define LV_LVGL_H_INCLUDE_SIMPLE
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef ROBOTO14BOLD
#define ROBOTO14BOLD 1
#endif

#if ROBOTO14BOLD

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0028 "(" */
    0x13, 0x66, 0xcc, 0xcc, 0xcc, 0xc4, 0x62, 0x10,

    /* U+0029 ")" */
    0x8c, 0x66, 0x33, 0x33, 0x33, 0x32, 0x64, 0x80,

    /* U+002C "," */
    0x6d, 0xe0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x18, 0xc4, 0x63, 0x11, 0x8c, 0x42, 0x31, 0x0,

    /* U+0030 "0" */
    0x38, 0x9b, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc6,
    0xc8, 0xe0,

    /* U+0031 "1" */
    0x1b, 0xfe, 0x31, 0x8c, 0x63, 0x18, 0xc6,

    /* U+0032 "2" */
    0x3d, 0xcf, 0x18, 0x30, 0xe1, 0x87, 0x1c, 0x70,
    0xc3, 0xf8,

    /* U+0033 "3" */
    0x3c, 0xcf, 0x18, 0x30, 0x63, 0x81, 0x83, 0xc6,
    0xcc, 0xf0,

    /* U+0034 "4" */
    0xc, 0x38, 0xf1, 0xe6, 0xcd, 0xb3, 0x7f, 0xc,
    0x18, 0x30,

    /* U+0035 "5" */
    0x7e, 0xc1, 0x83, 0x7, 0xc9, 0xc1, 0x83, 0x46,
    0xcc, 0xf0,

    /* U+0036 "6" */
    0x18, 0xe1, 0x86, 0xf, 0xd9, 0xf1, 0xe3, 0xc6,
    0xd8, 0xe0,

    /* U+0037 "7" */
    0xfe, 0xc, 0x30, 0x60, 0xc3, 0x6, 0x18, 0x30,
    0x61, 0x80,

    /* U+0038 "8" */
    0x7d, 0x8f, 0x1e, 0x3c, 0x67, 0xb1, 0xe3, 0xc7,
    0x8d, 0xf0,

    /* U+0039 "9" */
    0x38, 0xdb, 0x1e, 0x3c, 0x7c, 0xdf, 0x83, 0xc,
    0x38, 0xc0,

    /* U+003A ":" */
    0xc0, 0x3,

    /* U+0041 "A" */
    0xc, 0xe, 0x7, 0x83, 0xc3, 0x61, 0xb8, 0xcc,
    0xfe, 0x61, 0xb0, 0xf0, 0x60,

    /* U+0042 "B" */
    0xfd, 0x8f, 0x1e, 0x3c, 0x7f, 0xb1, 0xe3, 0xc7,
    0x8f, 0xf0,

    /* U+0043 "C" */
    0x3c, 0x66, 0xc3, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc3, 0x66, 0x3c,

    /* U+0044 "D" */
    0xf8, 0xc6, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc6, 0xc6, 0xf8,

    /* U+0045 "E" */
    0xff, 0x83, 0x6, 0xc, 0x1f, 0xb0, 0x60, 0xc1,
    0x83, 0xf8,

    /* U+0046 "F" */
    0xff, 0x83, 0x6, 0xc, 0x1f, 0xb0, 0x60, 0xc1,
    0x83, 0x0,

    /* U+0047 "G" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc0, 0xc0, 0xcf, 0xc3,
    0xc3, 0x63, 0x3e,

    /* U+0048 "H" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xff, 0xc3, 0xc3,
    0xc3, 0xc3, 0xc3,

    /* U+0049 "I" */
    0xff, 0xff, 0xfc,

    /* U+004A "J" */
    0x6, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83, 0xc7,
    0x89, 0xe0,

    /* U+004B "K" */
    0xc7, 0xce, 0xcc, 0xd8, 0xf8, 0xf8, 0xf8, 0xcc,
    0xce, 0xc6, 0xc7,

    /* U+004C "L" */
    0xc1, 0x83, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc1,
    0x83, 0xf8,

    /* U+004D "M" */
    0xe1, 0xf8, 0x7e, 0x1f, 0xcf, 0xf3, 0xf4, 0xbd,
    0xef, 0x7b, 0xcc, 0xf3, 0x3c, 0xcc,

    /* U+004E "N" */
    0xc3, 0xe3, 0xe3, 0xf3, 0xf3, 0xdb, 0xcf, 0xcf,
    0xc7, 0xc7, 0xc3,

    /* U+004F "O" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x66, 0x3c,

    /* U+0050 "P" */
    0xfc, 0xc6, 0xc3, 0xc3, 0xc3, 0xc6, 0xfc, 0xc0,
    0xc0, 0xc0, 0xc0,

    /* U+0051 "Q" */
    0x3c, 0x66, 0xc2, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x66, 0x3c, 0x7, 0x2,

    /* U+0052 "R" */
    0xfd, 0x9f, 0x1e, 0x3c, 0x79, 0xff, 0x66, 0xcd,
    0x8f, 0x18,

    /* U+0053 "S" */
    0x3c, 0x47, 0xc3, 0xe0, 0xf8, 0x7e, 0x1f, 0x7,
    0xc3, 0x63, 0x3c,

    /* U+0054 "T" */
    0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+0055 "U" */
    0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0xc3, 0x66, 0x3c,

    /* U+0056 "V" */
    0xc1, 0xb1, 0xd8, 0xcc, 0x67, 0x31, 0xb0, 0xd8,
    0x6c, 0x1c, 0xe, 0x7, 0x0,

    /* U+0057 "W" */
    0xc6, 0x36, 0x63, 0x67, 0x36, 0x76, 0x6f, 0x66,
    0xd6, 0x2d, 0x63, 0x9e, 0x39, 0xc3, 0x9c, 0x38,
    0xc0,

    /* U+0058 "X" */
    0xe3, 0x31, 0x8d, 0x86, 0xc1, 0xc0, 0xe0, 0x70,
    0x6c, 0x76, 0x31, 0xb8, 0xc0,

    /* U+0059 "Y" */
    0xc3, 0xe7, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x18,
    0x18, 0x18, 0x18,

    /* U+005A "Z" */
    0xff, 0x7, 0xe, 0xc, 0x1c, 0x18, 0x38, 0x30,
    0x70, 0xe0, 0xff
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 56, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 79, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 9, .adv_w = 79, .box_w = 4, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 17, .adv_w = 55, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 19, .adv_w = 65, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 84, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 28, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 38, .adv_w = 129, .box_w = 5, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 85, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 129, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 63, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 151, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 140, .adv_w = 143, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 147, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 146, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 126, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 153, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 158, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 65, .box_w = 2, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 125, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 142, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 121, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 196, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 158, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 155, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 144, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 155, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 308, .adv_w = 143, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 138, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 139, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 147, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 351, .adv_w = 146, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 196, .box_w = 12, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 381, .adv_w = 142, .box_w = 9, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 394, .adv_w = 138, .box_w = 8, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 405, .adv_w = 136, .box_w = 8, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x8, 0x9, 0xc
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 13, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 4, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 46, .range_length = 13, .glyph_id_start = 5,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 65, .range_length = 26, .glyph_id_start = 18,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 1, 2, 0, 0, 0, 3, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 4, 5, 6, 7, 8, 9,
    0, 10, 10, 11, 12, 13, 10, 10,
    7, 14, 15, 16, 0, 17, 11, 18,
    19, 20, 21, 22
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 1, 0, 2, 3, 3, 4, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 5, 0, 6, 0, 0, 0,
    6, 0, 0, 7, 0, 0, 0, 0,
    6, 0, 6, 0, 8, 9, 10, 11,
    12, 13, 14, 15
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    -7, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 2, 4, 0, 2, 0, 0, 0,
    0, -27, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, 0, -13, -2, -8,
    -4, 0, -16, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -3, 0, -3, 0,
    0, -6, 0, 0, -3, 0, 0, 0,
    0, 0, 0, -3, 0, 0, 0, 0,
    0, 0, 0, 0, -13, 0, -2, 0,
    0, 0, -9, 0, -2, 0, -2, -5,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 2, 0, 0, 0, 0, 0, 0,
    0, 0, -30, 0, -21, 0, -23, 0,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 0, 0, 0, -3,
    0, 0, 0, 2, -3, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    2, -7, 0, 0, -22, -3, -23, -10,
    0, -31, 0, 0, 0, -44, 0, -19,
    0, -20, 0, 0, 0, 0, 0, -6,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, -4, 0, -3, -2, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -5, 0, -2, 0, 0, -5, 0,
    -7, 0, -28, 0, -13, -3, -24, -2,
    2, 0, 2, 2, 0, 2, 0, 0,
    2, -24, 0, -8, -1, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 2,
    -16, 0, -5, 0, 0, 0, 2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -3, 0, 0, 0, 0, 2,
    0, 0, 0, 0, 0, 2, -25, 0,
    -16, -3, -10, -2, 2, -10, 2, 2,
    1, 2, 0, 0, 0, 0, 0, 1,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 22,
    .right_class_cnt     = 15,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 3,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t roboto14bold = {
#else
lv_font_t roboto14bold = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if ROBOTO14BOLD*/

