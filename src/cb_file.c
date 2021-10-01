#include "cb_file.h"
#include <string.h>
#include "cb_compress.h"
#include "cbfilegrabber2.h"
static int64_t s_cb_asset_file_size(FILE *fp);

cb_asset_file *cb_asset_file_create()
{
    cb_asset_file *n_file = NULL;

    if(NULL == (n_file = calloc(1,sizeof(cb_asset_file)))){
        return NULL;
    }

    return n_file;
}

void cb_asset_load_file(cb_asset_file *f, const char *name, int compress)
{
    FILE *in = NULL;

    if(NULL == (in = fopen(name, "rb+"))){
        return;
    }

    int64_t size = s_cb_asset_file_size(in);

    f->data = calloc(size,1);

    if(!f->data){
        return;
    }
    char *buf = calloc(size,1);

    if(!buf){
        cbfg_error("%s falied to alloc memory to file", __FUNCTION__);
        return;
    }
    fread(buf, size,1,in);

    f->size = size;
    f->compressed_size = 0;

    if(compress){
        const unsigned char *data = cb_compress(f->data, size, &f->compressed_size);

        if(!data){
            cbfg_error( "%s failed to compress data", __FUNCTION__);
        }
        memcpy(f->data, buf, size);
        f->compressed_data = calloc(f->compressed_size,1);
        memcpy(f->compressed_data, data, f->compressed_size);
        free((void*)data);
        data = NULL;

    }else {
       memcpy(f->data, buf, size);
    }


    f->file_type = CB_FILE_TYPE_SPRITE;
    free(buf);
    buf = NULL;
    fclose(in);


}


static int64_t s_cb_asset_file_size(FILE *fp){
    int64_t size = 0;

    if(!fp){
        return -1;
    }

    fseek(fp,0, SEEK_SET);
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    return size;


}
