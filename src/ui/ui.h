// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.2
// LVGL version: 8.3.6
// Project name: SquareLine_Project

#ifndef _SQUARELINE_PROJECT_UI_H
#define _SQUARELINE_PROJECT_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"

// SCREEN: ui_scrMain
void ui_scrMain_screen_init(void);
void ui_event_scrMain(lv_event_t * e);
extern lv_obj_t * ui_scrMain;
void ui_event_pnlMain(lv_event_t * e);
extern lv_obj_t * ui_pnlMain;
extern lv_obj_t * ui_Image1;
void ui_event_Button1(lv_event_t * e);
extern lv_obj_t * ui_Button1;
// SCREEN: ui_scrSettings
void ui_scrSettings_screen_init(void);
void ui_event_scrSettings(lv_event_t * e);
extern lv_obj_t * ui_scrSettings;
void ui_event_Panel1(lv_event_t * e);
extern lv_obj_t * ui_Panel1;
extern lv_obj_t * ui_Label1;
void ui_event_sldVolume(lv_event_t * e);
extern lv_obj_t * ui_sldVolume;
void ui_event_sldBrightness(lv_event_t * e);
extern lv_obj_t * ui_sldBrightness;
extern lv_obj_t * ui_Label2;
void ui_event_ButtonOK(lv_event_t * e);
extern lv_obj_t * ui_ButtonOK;
extern lv_obj_t * ui_Label4;
// SCREEN: ui_scrRadio
void ui_scrRadio_screen_init(void);
void ui_event_scrRadio(lv_event_t * e);
extern lv_obj_t * ui_scrRadio;
void ui_event_btnStart(lv_event_t * e);
extern lv_obj_t * ui_btnStart;
extern lv_obj_t * ui_lblButton4;
void ui_event_btnStop(lv_event_t * e);
extern lv_obj_t * ui_btnStop;
extern lv_obj_t * ui_lblButton5;
void ui_event_btnAggiorna(lv_event_t * e);
extern lv_obj_t * ui_btnAggiorna;
extern lv_obj_t * ui_lblButton3;
void ui_event_Dropdown2(lv_event_t * e);
extern lv_obj_t * ui_Dropdown2;
extern lv_obj_t * ui_LabelArtista;
extern lv_obj_t * ui_LabelCanzone;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_Label5;
extern lv_obj_t * ui____initial_actions0;


LV_IMG_DECLARE(ui__temporary_image);






void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
