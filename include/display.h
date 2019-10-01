#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "main.h"

  /*******************/
 /* Display Objects */
/*******************/

extern lv_obj_t * btnRedOne;
extern lv_obj_t * btnRedOne__label;
extern lv_style_t * btnRedOne__style;

extern lv_obj_t * btnRedTwo;
extern lv_obj_t * btnRedTwo__label;
extern lv_style_t * btnRedTwo__style;

extern lv_obj_t * btnBluOne;
extern lv_obj_t * btnBluOne__label;
extern lv_style_t * btnBluOne__style;

extern lv_obj_t * btnBluTwo;
extern lv_obj_t * btnBluTwo__label;
extern lv_style_t * btnBluTwo__style;

extern lv_obj_t * confirmBtn;
extern lv_obj_t * confirmBtn__label;
extern lv_style_t * confirmBtn__style;

extern lv_obj_t * wallpaper;
extern lv_style_t wallpaper_style;

extern lv_obj_t * Description;
extern lv_style_t Description_style;
extern lv_obj_t * Description_label;

  /*********************/
 /* Display Functions */
/*********************/

static lv_res_t BtnPressed(lv_obj_t * btn);
lv_style_t * createBtnStyle(lv_style_t * copy, lv_color_t rel, lv_color_t pr,
    lv_color_t tglRel, lv_color_t tglPr, lv_color_t tglBorder, lv_color_t textColor, lv_obj_t * btn);
void setBtnStyle(lv_style_t * btnStyle, lv_obj_t * btn);
lv_obj_t * createBtn(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
    int id, const char * title);
void DisplaySetup();
void DisplayControl();
#endif