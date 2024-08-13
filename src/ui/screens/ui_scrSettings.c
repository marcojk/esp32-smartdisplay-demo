// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#include "../ui.h"

void ui_scrSettings_screen_init(void)
{
    ui_scrSettings = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_scrSettings, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Panel1 = lv_obj_create(ui_scrSettings);
    lv_obj_set_width(ui_Panel1, lv_pct(98));
    lv_obj_set_height(ui_Panel1, lv_pct(98));
    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_set_style_outline_color(ui_Panel1, lv_color_hex(0x000000), LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_Panel1, 255, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_Panel1, 10, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_Panel1, 10, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    ui_Label1 = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label1, -187);
    lv_obj_set_y(ui_Label1, -33);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "Volume");

    ui_sldVolume = lv_slider_create(ui_Panel1);
    lv_slider_set_range(ui_sldVolume, 0, 21);
    lv_slider_set_value(ui_sldVolume, 16, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_sldVolume) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_sldVolume, 0, LV_ANIM_OFF);
    lv_obj_set_width(ui_sldVolume, 250);
    lv_obj_set_height(ui_sldVolume, 20);
    lv_obj_set_x(ui_sldVolume, 20);
    lv_obj_set_y(ui_sldVolume, -33);
    lv_obj_set_align(ui_sldVolume, LV_ALIGN_CENTER);


    ui_sldBrightness = lv_slider_create(ui_Panel1);
    lv_slider_set_value(ui_sldBrightness, 0, LV_ANIM_OFF);
    if(lv_slider_get_mode(ui_sldBrightness) == LV_SLIDER_MODE_RANGE) lv_slider_set_left_value(ui_sldBrightness, 0,
                                                                                                  LV_ANIM_OFF);
    lv_obj_set_width(ui_sldBrightness, 250);
    lv_obj_set_height(ui_sldBrightness, 20);
    lv_obj_set_x(ui_sldBrightness, 20);
    lv_obj_set_y(ui_sldBrightness, 22);
    lv_obj_set_align(ui_sldBrightness, LV_ALIGN_CENTER);


    ui_Label2 = lv_label_create(ui_Panel1);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label2, -177);
    lv_obj_set_y(ui_Label2, 23);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "Brightness");

    ui_ButtonOK = lv_btn_create(ui_scrSettings);
    lv_obj_set_width(ui_ButtonOK, 100);
    lv_obj_set_height(ui_ButtonOK, 50);
    lv_obj_set_x(ui_ButtonOK, -97);
    lv_obj_set_y(ui_ButtonOK, 98);
    lv_obj_set_align(ui_ButtonOK, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ButtonOK, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_ButtonOK, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label4 = lv_label_create(ui_ButtonOK);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "OK");

    lv_obj_add_event_cb(ui_sldVolume, ui_event_sldVolume, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_sldBrightness, ui_event_sldBrightness, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Panel1, ui_event_Panel1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_ButtonOK, ui_event_ButtonOK, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_scrSettings, ui_event_scrSettings, LV_EVENT_ALL, NULL);

}
