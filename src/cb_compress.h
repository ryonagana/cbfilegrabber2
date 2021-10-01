#ifndef CB_COMPRESS_H
#define CB_COMPRESS_H
#include "miniz/miniz.h"

#include "cb_file.h"



/*
 * enters the data returns the compressed data
 *
*/
const unsigned char *cb_compress(const unsigned char* uncompressed_in, size_t size, size_t* cmp_size);
const unsigned char *cb_uncompress(const unsigned char* compressed_src, size_t compressed_len,const unsigned char* uncompressed_src, size_t uncompressed_len, size_t *out_len);
int cb_compare_data(const unsigned char *compressed_src,  const unsigned char* dst, size_t uncompressed_len);



int cb_compress_init_zip(mz_zip_archive *zip_archive, const char *zip_name);
void cb_compress_end(mz_zip_archive *zip_archive);

int cb_compress_add_file_to_zip(mz_zip_archive *zip_archive, const char *file, const char *comment);
int cb_compress_add_mem_to_zip(mz_zip_archive *zip_archive, const char* filename, void* data, size_t size);


int cb_compress_add_file_existent_zip(const char *zip_path, const char*filename, void *data, size_t size, const char *comment);
#endif // CB_COMPRESS_H
