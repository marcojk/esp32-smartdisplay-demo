#include <Arduino.h>

#include <esp32_smartdisplay.h>
#include <ui/ui.h>
#include <Audio.h>
#ifdef BOARD_HAS_TF
#include <fs_utility.hpp>
#endif

#define BOARD_HAS_AUDIO
#if defined BOARD_HAS_AUDIO || defined BOARD_HAS_SPEAK
Audio *audio;
#endif
#define WIFI_SSID "OpenWrt"
#define WIFI_PASSWORD "marco123marco123"
#define RADIO_URL "http://icecast.unitedradio.it/Virgin.mp3"

const char radiolist[] = "http://icecast.unitedradio.it/Virgin.mp3\nhttp://icecast.unitedradio.it/Radio105.mp3\nhttp://shoutcast.rtl.it:3060/\nhttp://icestreaming.rai.it/2.mp3\nhttp://4c4b867c89244861ac216426883d1ad0.msvdn.net/radiodeejay/radiodeejay/master_ma.m3u8\nhttp://radiocapital-lh.akamaihd.net/i/RadioCapital_Live_1@196312/master.m3u8\n";


uint8_t cnt = 0;
bool audio_file_present = false;
bool img_file_present = false;

void OnAddOneClicked(lv_event_t *e)
{
    static uint8_t cnt = 0;
    cnt++;
    lv_label_set_text_fmt(ui_lblCountValue, "%d", cnt);
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

    WiFi.disconnect();
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    if (WiFi.waitForConnectResult() == WL_CONNECTED)
    {
        #ifdef BOARD_HAS_SPEAK
        audio = new Audio(true, I2S_DAC_CHANNEL_LEFT_EN);
        audio->forceMono(true);
        #endif
        #ifdef BOARD_HAS_AUDIO
        audio = new Audio();
        audio->setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
        #endif
        audio->setVolume(4);
        while (!audio->connecttohost(RADIO_URL))
            delay(500);
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

/* 
lv_obj_t * img;
  img=lv_img_create(screenMain);
  lv_obj_set_width(img, 214);
  lv_obj_set_height(img, 184);
  lv_obj_set_pos(img, 32, 100);
  lv_img_cache_invalidate_src(NULL);
  lv_img_set_src(img,"F:/photo.png");*/