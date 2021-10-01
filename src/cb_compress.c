#include "cb_compress.h"
#include "cbfilegrabber2.h"

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint;

const unsigned char *cb_compress(const unsigned char *uncompressed_in, size_t size, size_t *cmp_size)
{

    int compress_status = 0;
    uLong src_len =  (uLong)size;
    uLong cmp_len = compressBound(src_len);
    uint8 *pCmp;

    if(NULL == (pCmp = (mz_uint8 *)calloc((size_t)cmp_len + 1,1))){
        return MZ_FALSE;
    }

    compress_status = compress(pCmp, &cmp_len, (void*)uncompressed_in, src_len);
    *cmp_size = cmp_len;

    if(compress_status != Z_OK){
        cbfg_error("%s Error Trying to compress file", __FUNCTION__);
        free(pCmp);

        return MZ_FALSE;
    }

    return pCmp;
}

const unsigned char *cb_uncompress(const unsigned char* compressed_src, size_t compressed_len, const unsigned char *uncompressed_src, size_t uncompressed_len, size_t *out_len)
{
    int uncompress_status = 0;
    uint8 *pUncomp =  NULL;
    mz_ulong u_len = uncompressed_len;
    if(NULL == (pUncomp = (mz_uint8 *)calloc((size_t)uncompressed_len + 1,1))){
        return MZ_FALSE;
    }

    uncompress_status = mz_uncompress(pUncomp, (mz_ulong*)uncompressed_len, compressed_src, compressed_len);  //uncompress2(pUncomp, &u_len, compressed_src, &cmp_len);

    if(uncompress_status != Z_OK){
        cbfg_error( "%s Error Trying to uncompress file", __FUNCTION__);
        free(pUncomp);
        return MZ_FALSE;
    }

    if(u_len != uncompressed_len){
        cbfg_error( "%s compressed failed ", __FUNCTION__);
        free(pUncomp);
        return NULL;
    }

    return pUncomp;
}

int cb_compare_data(const unsigned char *compressed_src,  const unsigned char* dst, size_t uncompressed_len)
{
    if(!memcmp(compressed_src, dst, uncompressed_len)){
        return 0;
    }

    return 1;
}

int cb_compress_init_zip(mz_zip_archive* zip_archive, const char *zip_name)
{
    if(!mz_zip_writer_init_file(zip_archive, zip_name, 0)){
        cbfg_error( "%s - Error to create %s", __FUNCTION__, zip_name);
        return -1;
    }
    return 0;
}

void cb_compress_end(mz_zip_archive *zip_archive)
{
    if(zip_archive){
        mz_zip_writer_finalize_archive(zip_archive);
        mz_zip_end(zip_archive);
    }
    return;
}

int cb_compress_add_file_to_zip(mz_zip_archive *zip_archive, const char *file, const char *comment)
{
    if(!zip_archive || !file){
        cbfg_error( "%s - Error to create %s", __FUNCTION__, file);
        return -1;
    }

    void *cmnt = (char*)comment;
    size_t cmnt_len = strlen(cmnt);

    int status  = 0;

    status = mz_zip_writer_add_file(zip_archive, file,file, comment, cmnt_len, MZ_BEST_COMPRESSION);
    return status;
}

int cb_compress_add_mem_to_zip(mz_zip_archive *zip_archive, const char *filename, void *data, size_t size)
{
    if(!zip_archive || !data){
        cbfg_error( "%s - Error to create %s", __FUNCTION__, filename);
        return -1;
    }


    int status  = 0;

    status =  mz_zip_writer_add_mem(zip_archive, filename, data, size, MZ_BEST_COMPRESSION);
    return status;
}

int cb_compress_add_file_existent_zip(const char *zip_path, const char *filename, void *data, size_t size, const char *comment)
{
    if(!mz_zip_add_mem_to_archive_file_in_place(zip_path, filename, data, size, comment, strlen(comment), MZ_BEST_COMPRESSION)){
        return -1;
    }
    return 0;
}
