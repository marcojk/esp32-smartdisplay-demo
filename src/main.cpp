#include <Arduino.h>

#include <esp32_smartdisplay.h>
#include <ui/ui.h>
#include <Audio.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#ifdef BOARD_HAS_TF
#include <fs_utility.hpp>
#endif

//#define BOARD_HAS_AUDIO
#if defined BOARD_HAS_AUDIO || defined BOARD_HAS_SPEAK
Audio *audio;
#endif
//#define WIFI_SSID "Cerba HealthCare Italia - Guest"
//#define WIFI_PASSWORD "4estER!&F95rgSka"
//#define WIFI_SSID "OpenWrt"
//#define WIFI_PASSWORD "marco123marco123"

#define RADIO_URL "http://icecast.unitedradio.it/Virgin.mp3"

const char radiolist[] = "http://icecast.unitedradio.it/Virgin.mp3\nhttp://icecast.unitedradio.it/Radio105.mp3\nhttp://shoutcast.rtl.it:3060/\nhttp://icestreaming.rai.it/2.mp3\nhttp://4c4b867c89244861ac216426883d1ad0.msvdn.net/radiodeejay/radiodeejay/master_ma.m3u8\nhttp://radiocapital-lh.akamaihd.net/i/RadioCapital_Live_1@196312/master.m3u8\n";

uint8_t cnt = 0;
bool audio_file_present = false;
bool img_file_present = false;
WiFiMulti wifiMulti;
void OnAddOneClicked(lv_event_t *e)
{
    static uint8_t cnt = 0;
    cnt++;
    //lv_label_set_text_fmt(ui_lblCountValue, "%d", cnt);
}


void ShowImage() {
  char filename[30];
  next_img_file(filename);
  Serial.print("filename: ");Serial.println(filename);
  if ( *filename != NULL) lv_img_set_src(ui_Image1,filename);

}

void OnRotateClicked(lv_event_t *e)
{
    auto disp = lv_disp_get_default();
    auto rotation = (lv_disp_rot_t)((lv_disp_get_rotation(disp) + 1) % (LV_DISP_ROT_270 + 1));
    lv_disp_set_rotation(disp, rotation);
}

void setup()
{

    Serial.begin(115200);
    Serial.setDebugOutput(true);
    log_i("Board: %s", BOARD_NAME);
    log_i("CPU: %s rev%d, CPU Freq: %d Mhz, %d core(s)", ESP.getChipModel(), ESP.getChipRevision(), getCpuFrequencyMhz(), ESP.getChipCores());
    log_i("Free heap: %d bytes", ESP.getFreeHeap());
    log_i("Free PSRAM: %d bytes", ESP.getPsramSize());
    log_i("SDK version: %s", ESP.getSdkVersion());

    smartdisplay_init();
    
    #ifdef BOARD_HAS_TF
    lv_port_sd_fs_init();
    #endif

    if(open_audio_dir())
    audio_file_present = true;
    if(open_img_dir())
    img_file_present = true;
    
    __attribute__((unused)) auto disp = lv_disp_get_default();
    lv_disp_set_rotation(disp, LV_DISP_ROT_90);
    // lv_disp_set_rotation(disp, LV_DISP_ROT_180);
    // lv_disp_set_rotation(disp, LV_DISP_ROT_270);

    ui_init();
    //WiFi.mode(WIFI_STA);
    //WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    //if (WiFi.waitForConnectResult() == WL_CONNECTED)
    wifiMulti.addAP("OpenWrt","marco123marco123");
    wifiMulti.addAP("Cerba HealthCare Italia - Guest","4estER!&F95rgSka");
    if(wifiMulti.run() == WL_CONNECTED)
    {
        #ifdef BOARD_HAS_SPEAK
        audio = new Audio(true, I2S_DAC_CHANNEL_LEFT_EN);
        audio->forceMono(true);
        audio->setVolume(4);
        while (!audio->connecttohost(RADIO_URL))
            delay(500);
        #endif
        #ifdef BOARD_HAS_AUDIO
        audio = new Audio();
        audio->setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
        audio->setVolume(9);
        while (!audio->connecttohost(RADIO_URL))
            delay(500);
        #endif

    }
}

ulong next_millis;

void loop()
{
/*     auto const now = millis();
    if (now > next_millis)
    {
        next_millis = now + 500;

        char text_buffer[32];
        sprintf(text_buffer, "%lu", now);
        lv_label_set_text(ui_lblMillisecondsValue, text_buffer);

#ifdef BOARD_HAS_RGB_LED
        auto const rgb = (now / 2000) % 8;
        smartdisplay_led_set_rgb(rgb & 0x01, rgb & 0x02, rgb & 0x04);
#endif

#ifdef BOARD_HAS_CDS
        auto cdr = analogReadMilliVolts(CDS);
        sprintf(text_buffer, "%d", cdr);
        lv_label_set_text(ui_lblCdrValue, text_buffer);
#endif 
    }
*/
auto const now = millis();
    if (now > next_millis)
    {
        next_millis = now + 3000;
        cnt++;
        ShowImage();
    }
    audio->loop();
    lv_timer_handler();
}

void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info){  //end of file
    Serial.print("eof_mp3     ");Serial.println(info);
}
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle ");Serial.println(info);
    //lv_label_set_text(ui_LabelCanzone, info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}

/* 
lv_obj_t * img;
  img=lv_img_create(screenMain);
  lv_obj_set_width(img, 214);
  lv_obj_set_height(img, 184);
  lv_obj_set_pos(img, 32, 100);
  lv_img_cache_invalidate_src(NULL);
  lv_img_set_src(img,"F:/photo.png");*/
  
void OnButtonStartClicked(lv_event_t *e)
{
  #if defined(BOARD_HAS_SPEAK) || defined(BOARD_HAS_AUDIO)
    audio->pauseResume();
    Serial.println("Start audio");  
  #endif
}

void OnButtonStopClicked(lv_event_t *e)
{
  #if defined(BOARD_HAS_SPEAK) || defined(BOARD_HAS_AUDIO)
    audio->stopSong();
    Serial.println("Stop audio");
  #endif
}

void onVolumeSliderChanged(lv_event_t * e)
{
  #if defined BOARD_HAS_SPEAK || defined BOARD_HAS_AUDIO
    lv_obj_t * slider = lv_event_get_target(e);
    audio->setVolume((int)lv_slider_get_value(slider));
    Serial.print("Volume ");
    Serial.println((int)lv_slider_get_value(slider));
  #endif
}

void OnButtonAggiornaClicked(lv_event_t * e)
{
  lv_obj_t * dropdown = lv_event_get_target(e);

}

void onChangeRadioURL(lv_event_t * e)
{
	lv_obj_t * dropdown = lv_event_get_target(e);
  char buf[200];
  lv_dropdown_get_selected_str(dropdown, buf, 200);
  audio->stopSong();
  audio->connecttohost(buf);
}

void onBrightnessSliderChanged(lv_event_t * e)
{
  lv_obj_t * slider = lv_event_get_target(e);
  smartdisplay_lcd_set_backlight(lv_slider_get_value(slider)/100.0f);
}

void OnButtonNextClicked(lv_event_t *e)
{
    cnt++;
    ShowImage();  
}