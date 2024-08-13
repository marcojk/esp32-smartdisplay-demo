 #include <lvgl.h>
#include <FS.h>
#include "SD.h"

#ifdef __cplusplus
extern "C"
{
#endif

void fs_init(void);
static void *sd_fs_open(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode);
static lv_fs_res_t sd_fs_close(lv_fs_drv_t *drv, void *file_p);
static lv_fs_res_t sd_fs_read(lv_fs_drv_t *drv, void *file_p, void *fileBuf, uint32_t btr, uint32_t *br);
static lv_fs_res_t sd_fs_write(lv_fs_drv_t *drv, void *file_p, const void *buf, uint32_t btw, uint32_t *bw);
static lv_fs_res_t sd_fs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence);
static lv_fs_res_t sd_fs_tell(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p);
static void *sd_dir_open(lv_fs_drv_t *drv, const char *dirpath);
static lv_fs_res_t sd_dir_read(lv_fs_drv_t *drv, void *dir_p, char *fn);
static lv_fs_res_t sd_dir_close(lv_fs_drv_t *drv, void *dir_p);
void lv_port_sd_fs_init(void);
bool open_audio_dir(void);
bool open_img_dir(void);
void next_img_file(char*);
void next_audio_file(char*);
#ifdef __cplusplus
}
#endif