#include "main.h"
#include "auton.h"
#include "display.h"

lv_obj_t * btnRedOne;
lv_obj_t * btnRedOne__label;
lv_style_t btnRedOne__style;

lv_obj_t * btnRedTwo;
lv_obj_t * btnRedTwo__label;
lv_style_t btnRedTwo__style;

lv_obj_t * btnBluOne;
lv_obj_t * btnBluOne__label;
lv_style_t btnBluOne__style;

lv_obj_t * btnBluTwo;
lv_obj_t * btnBluTwo__label;
lv_style_t btnBluTwo__style;

lv_obj_t * confirmBtn;
lv_obj_t * confirmBtn__label;
lv_style_t confirmBtn__style;

lv_obj_t * wallpaper;
lv_style_t wallpaper_style;

lv_obj_t * Description;
lv_style_t Description_style;
lv_obj_t * Description_label;

lv_style_t * createBtnStyle(lv_style_t * copy, lv_color_t rel, lv_color_t pr,
    lv_color_t tglRel, lv_color_t tglPr, lv_color_t tglBorder, lv_color_t textColor, lv_obj_t * btn)
{
    lv_style_t * btnStyle = (lv_style_t *)malloc(sizeof(lv_style_t) * 4);

    for(int i = 0; i < 4; i++) lv_style_copy(&btnStyle[i], copy);

    btnStyle[0].body.main_color = rel;
    btnStyle[0].body.grad_color = rel;
    btnStyle[0].text.color = textColor;

    btnStyle[1].body.main_color = pr;
    btnStyle[1].body.grad_color = pr;
    btnStyle[1].text.color = textColor;

    btnStyle[2].body.main_color = tglRel;
    btnStyle[2].body.grad_color = tglRel;
    btnStyle[2].body.border.width = 6;
    btnStyle[2].body.border.color = tglBorder;
    btnStyle[2].text.color = textColor;

    btnStyle[3].body.main_color = tglPr;
    btnStyle[3].body.grad_color = tglPr;
    btnStyle[3].body.border.width = 6;
    btnStyle[3].body.border.color = tglBorder;
    btnStyle[3].text.color = textColor;

    lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btnStyle[0]);
    lv_btn_set_style(btn, LV_BTN_STYLE_PR, &btnStyle[1]);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, &btnStyle[2]);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, &btnStyle[3]);

    return btnStyle;
}

void setBtnStyle(lv_style_t * btnStyle, lv_obj_t * btn)
{
    lv_btn_set_style(btn, LV_BTN_STYLE_REL, &btnStyle[0]);
    lv_btn_set_style(btn, LV_BTN_STYLE_PR, &btnStyle[1]);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_REL, &btnStyle[2]);
    lv_btn_set_style(btn, LV_BTN_STYLE_TGL_PR, &btnStyle[3]);
}

lv_obj_t * createBtn(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height,
    int id, const char * title)
{
    lv_obj_t * btn = lv_btn_create(parent, NULL);
    lv_obj_set_pos(btn, x, y);
    lv_obj_set_size(btn, width, height);
    lv_obj_set_free_num(btn, id);

    lv_obj_t * label = lv_label_create(btn, NULL);
    lv_label_set_text(label, title);
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_MID, 0, 5);

    return btn;
}

static lv_res_t BtnPressed(lv_obj_t * btn) {
    uint8_t id = lv_obj_get_free_num(btn);
    char out[22];
    if (id == 0) {
        autoMode = 1;
        sprintf(out,"Red One Selected: %d",autoMode);
        lv_label_set_text(Description_label,out);
    } else if (id == 1) {
        autoMode = 2;
        sprintf(out,"Red Two Selected: %d",autoMode);
        lv_label_set_text(Description_label,out);
    } else if (id == 2) {
        autoMode = 3;
        sprintf(out,"Blue One Selected: %d",autoMode);
        lv_label_set_text(Description_label,out);    
    } else if (id == 3) {
        autoMode = 4;
        sprintf(out,"Blue Two Selected: %d",autoMode);
        lv_label_set_text(Description_label,out);
    }
    return LV_RES_OK;
}

void DisplaySetup() {
    wallpaper = lv_obj_create(NULL,NULL);
    lv_style_copy(&wallpaper_style,&lv_style_plain);
     wallpaper_style.body.main_color = LV_COLOR_GRAY;
    wallpaper_style.body.grad_color = LV_COLOR_GRAY;
    lv_obj_set_style(wallpaper,&wallpaper_style);
    lv_scr_load(wallpaper);

    btnRedOne = createBtn(wallpaper,0,0,120,60,0,"Red One");
    lv_obj_set_free_num(btnRedOne,0);
    lv_btn_set_action(btnRedOne,LV_BTN_ACTION_CLICK,BtnPressed);
    btnRedTwo = createBtn(wallpaper,120,0,120,60,1,"Red Two");
    lv_obj_set_free_num(btnRedTwo,1);
    lv_btn_set_action(btnRedTwo,LV_BTN_ACTION_CLICK,BtnPressed);
    btnBluOne = createBtn(wallpaper,240,0,120,60,2,"Blue One");
    lv_obj_set_free_num(btnBluOne,2);
    lv_btn_set_action(btnBluOne,LV_BTN_ACTION_CLICK,BtnPressed);
    btnBluTwo = createBtn(wallpaper,360,0,120,60,3,"Blue Two");
    lv_obj_set_free_num(btnBluTwo,3);
    lv_btn_set_action(btnBluTwo,LV_BTN_ACTION_CLICK,BtnPressed);
    confirmBtn = createBtn(wallpaper,180,180,120,60,4,"Confirm");

    btnRedOne__style =  createBtnStyle(&lv_style_plain,
                                      LV_COLOR_MAKE(255,51,51),
                                      LV_COLOR_MAKE(204,0,0),
                                      LV_COLOR_MAKE(255,51,51),
                                      LV_COLOR_MAKE(204,0,0),
                                      LV_COLOR_MAKE(102,0,0),
                                      LV_COLOR_BLACK,
                                      btnRedOne);
    setBtnStyle(&btnRedOne__style,btnRedOne);
    btnRedTwo__style =  createBtnStyle(&lv_style_plain,
                                      LV_COLOR_MAKE(255,51,51),
                                      LV_COLOR_MAKE(204,0,0),
                                      LV_COLOR_MAKE(255,51,51),
                                      LV_COLOR_MAKE(204,0,0),
                                      LV_COLOR_MAKE(102,0,0),
                                      LV_COLOR_BLACK,
                                      btnRedTwo);
    setBtnStyle(&btnRedTwo__style,btnRedTwo);
    btnBluOne__style = createBtnStyle(&lv_style_plain,
                                      LV_COLOR_MAKE(51,153,255),
                                      LV_COLOR_MAKE(0,102,204),
                                      LV_COLOR_MAKE(51,153,255),
                                      LV_COLOR_MAKE(0,102,204),
                                      LV_COLOR_MAKE(0,51,102),
                                      LV_COLOR_BLACK,
                                      btnBluOne);
    setBtnStyle(&btnBluOne__style,btnBluOne);
    btnBluTwo__style = createBtnStyle(&lv_style_plain,
                                      LV_COLOR_MAKE(51,153,255),
                                      LV_COLOR_MAKE(0,102,204),
                                      LV_COLOR_MAKE(51,153,255),
                                      LV_COLOR_MAKE(0,102,204),
                                      LV_COLOR_MAKE(0,51,102),
                                      LV_COLOR_BLACK,
                                      btnBluTwo);
    setBtnStyle(&btnBluTwo__style,btnBluTwo);
    confirmBtn__style = createBtnStyle(&lv_style_plain,
                                       LV_COLOR_MAKE(0,255,128),
                                       LV_COLOR_MAKE(0,153,76),
                                       LV_COLOR_MAKE(0,255,128),
                                       LV_COLOR_MAKE(0,153,76),
                                       LV_COLOR_MAKE(0,102,51),
                                       LV_COLOR_BLACK,
                                       confirmBtn);
    setBtnStyle(&confirmBtn__style,confirmBtn);

    Description = lv_obj_create(wallpaper,NULL);
    lv_obj_set_width(Description,300);
    lv_style_copy(&Description_style,&lv_style_plain);
    Description_style.body.grad_color = LV_COLOR_GRAY;
    Description_style.body.main_color = LV_COLOR_GRAY;
    lv_obj_set_pos(Description,90,80);

    Description_label = lv_label_create(Description,NULL);
    lv_label_set_text(Description_label,"Nothing selected");
    lv_obj_align(Description_label, NULL, LV_ALIGN_CENTER, 0, 0);
}


void CleanPointers() {
    lv_obj_del(wallpaper);
    wallpaper = nullptr;
    btnRedOne = nullptr;
    btnRedTwo = nullptr;
    btnBluOne = nullptr;
    btnBluTwo = nullptr;
    Description = nullptr;

    btnRedOne__label = nullptr;
    btnRedTwo__label = nullptr;
    btnBluOne__label = nullptr;
    btnBluTwo__label = nullptr;
    Description_label = nullptr;
}

