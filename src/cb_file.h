#ifndef CB_FILE_H
#define CB_FILE_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum CB_FILE_TYPE {
    CB_FILE_TYPE_NONE,
    CB_FILE_TYPE_SPRITE,
    CB_FILE_TYPE_SOUND,
    CB_FILE_TYPE_TEXT,
    CB_FILE_TYPE_FONT,
    CB_FILE_TYPE_ANY

}CB_FILE_TYPE;

typedef struct cb_asset_file {
    char filename[56];
    size_t size;
    size_t compressed_size;
    unsigned char *data;
    unsigned char *compressed_data;
    CB_FILE_TYPE file_type;
}cb_asset_file;



cb_asset_file*  cb_asset_file_create();
void cb_asset_load_file(cb_asset_file *f, const char *name, int compress);

#endif // CB_FILE_H
