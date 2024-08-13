#include <fs_utility.hpp>

SPIClass sdCardSpi = SPIClass(VSPI);
lv_fs_dir_t img_dir;
lv_fs_dir_t audio_dir;


bool open_img_dir(void) {

lv_fs_res_t res;
res = lv_fs_dir_open(&img_dir, "S:/foto");
Serial.println("open img dir");
//lv_fs_get_ext
  if(res == LV_FS_RES_OK) {
      Serial.println("use /foto/");
      return true;
  }
  else {
    res = lv_fs_dir_open(&img_dir, "S:/pictures");
    if(res == LV_FS_RES_OK) {
      Serial.println("use /pictures/");
      return true;
    }
    else {
      Serial.println("No foto folder");
      return false;
    }
  }
}

bool open_audio_dir(void) {

  lv_fs_res_t res;
  res = lv_fs_dir_open(&audio_dir, "S:/mp3");
  if(res == LV_FS_RES_OK) {
      Serial.println("use /mp3/");
      return true;
  }
  else {
    res = lv_fs_dir_open(&audio_dir, "S:/music");
    if(res == LV_FS_RES_OK) {
      Serial.println("use /music/");
      return true;
    }
    else {
      Serial.println("No audio folder");
      return false;
    }
  }
}

void next_audio_file(char* file) {
  lv_fs_res_t res;
  if(file != NULL) {
    res = lv_fs_dir_read(&audio_dir, file);
    if(res != LV_FS_RES_OK) {
      *file = NULL;
      } 
  }
}

void next_img_file(char* file) {
  lv_fs_res_t res;
  char path[40] = "S:/foto/";
  if(file != NULL) {
    res = lv_fs_dir_read(&img_dir, file);
    if(res != LV_FS_RES_OK || *file == NULL) {
      *file = NULL;
      lv_fs_dir_close(&img_dir);
      open_img_dir();
      return;
      }
    else {
      //lv_fs_get_ext
      const char *result;
      result = lv_fs_get_ext(file);
      if(0 == strcmp(result,"png") || 0 == strcmp(result,"jpg")) {
        strcat(path,file);
        strcpy(file, path);
      return;
      }
      else *file == NULL;
      
      //if(strcmp(result,""))
    }
  }
}

void lv_port_sd_fs_init(void) {
  /*----------------------------------------------------
    * Initialize your storage device and File System
    * -------------------------------------------------*/
  fs_init();

  /*---------------------------------------------------
    * Register the file system interface in LVGL
    *--------------------------------------------------*/

  /*Add a simple drive to open images*/
  static lv_fs_drv_t fs_drv;
  lv_fs_drv_init(&fs_drv);

  /*Set up fields...*/
  fs_drv.letter = 'S';
  fs_drv.cache_size = 0;

  fs_drv.open_cb = sd_fs_open;
  fs_drv.close_cb = sd_fs_close;
  fs_drv.read_cb = sd_fs_read;
  fs_drv.write_cb = sd_fs_write;
  fs_drv.seek_cb = sd_fs_seek;
  fs_drv.tell_cb = sd_fs_tell;

  fs_drv.dir_close_cb = sd_dir_close;
  fs_drv.dir_open_cb = sd_dir_open;
  fs_drv.dir_read_cb = sd_dir_read;

  lv_fs_drv_register(&fs_drv);
}

void fs_init(void)
{

  sdCardSpi.begin(TF_SPI_SCLK, TF_SPI_MISO, TF_SPI_MOSI, TF_CS);  //SCLK, MISO, MOSI, SS 
  if (!SD.begin(TF_CS, sdCardSpi, 40000000)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %dMB\r\n", cardSize);

  Serial.printf("Total space: %dMB\r\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %dMB\r\n", SD.usedBytes() / (1024 * 1024));
}

static void *sd_fs_open(lv_fs_drv_t *drv, const char *path, lv_fs_mode_t mode) {
  LV_UNUSED(drv);

  const char *flags = "";

  if (mode == LV_FS_MODE_WR)
    flags = FILE_WRITE;
  else if (mode == LV_FS_MODE_RD)
    flags = FILE_READ;
  else if (mode == (LV_FS_MODE_WR | LV_FS_MODE_RD))
    flags = FILE_WRITE;

  File f = SD.open(path, flags);
  if (!f) {
    Serial.println("Failed to open file!");
    return NULL;
  }

  File *lf = new File{ f };

  //make sure at the beginning
  //fp->seek(0);

  return (void *)lf;
}

static lv_fs_res_t sd_fs_close(lv_fs_drv_t *drv, void *file_p) {
  LV_UNUSED(drv);

  File *fp = (File *)file_p;

  fp->close();

  delete (fp);  // when close
  return LV_FS_RES_OK;
}

static lv_fs_res_t sd_fs_read(lv_fs_drv_t *drv, void *file_p, void *fileBuf, uint32_t btr, uint32_t *br) {
  LV_UNUSED(drv);

  File *fp = (File *)file_p;

  *br = fp->read((uint8_t *)fileBuf, btr);

  return (int32_t)(*br) < 0 ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;
}

static lv_fs_res_t sd_fs_write(lv_fs_drv_t *drv, void *file_p, const void *buf, uint32_t btw, uint32_t *bw) {
  LV_UNUSED(drv);

  File *fp = (File *)file_p;

  *bw = fp->write((const uint8_t *)buf, btw);

  return (int32_t)(*bw) < 0 ? LV_FS_RES_UNKNOWN : LV_FS_RES_OK;
}

static lv_fs_res_t sd_fs_seek(lv_fs_drv_t *drv, void *file_p, uint32_t pos, lv_fs_whence_t whence) {
  LV_UNUSED(drv);

  File *fp = (File *)file_p;

  SeekMode mode;
  if (whence == LV_FS_SEEK_SET)
    mode = SeekSet;
  else if (whence == LV_FS_SEEK_CUR)
    mode = SeekCur;
  else if (whence == LV_FS_SEEK_END)
    mode = SeekEnd;

  fp->seek(pos, mode);

  return LV_FS_RES_OK;
}

static lv_fs_res_t sd_fs_tell(lv_fs_drv_t *drv, void *file_p, uint32_t *pos_p) {
  LV_UNUSED(drv);

  File *fp = (File *)file_p;

  *pos_p = fp->position();

  return LV_FS_RES_OK;
}

static void *sd_dir_open(lv_fs_drv_t *drv, const char *dirpath) {
  LV_UNUSED(drv);

  File root = SD.open(dirpath);
  if (!root) {
    Serial.println("Failed to open directory!");
    return NULL;
  }

  if (!root.isDirectory()) {
    Serial.println("Not a directory!");
    return NULL;
  }

  File *lroot = new File{ root };

  return (void *)lroot;
}

static lv_fs_res_t sd_dir_read(lv_fs_drv_t *drv, void *dir_p, char *fn) {
  LV_UNUSED(drv);

  File *root = (File *)dir_p;
  fn[0] = '\0';

  File file = root->openNextFile();
  while (file) {
    if (strcmp(file.name(), ".") == 0 || strcmp(file.name(), "..") == 0) {
      continue;
    } else {
      if (file.isDirectory()) {
        Serial.print("  DIR : ");
        Serial.println(file.name());
        fn[0] = '/';
        strcpy(&fn[1], file.name());
      } else {
        Serial.print("  FILE: ");
        Serial.print(file.name());
        Serial.print("  SIZE: ");
        Serial.println(file.size());

        strcpy(fn, file.name());
      }
      break;
    }
    file = root->openNextFile();
  }

  return LV_FS_RES_OK;
}

static lv_fs_res_t sd_dir_close(lv_fs_drv_t *drv, void *dir_p) {
  LV_UNUSED(drv);

  File *root = (File *)dir_p;

  root->close();

  delete (root);  // when close

  return LV_FS_RES_OK;
}