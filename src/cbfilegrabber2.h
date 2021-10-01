#ifndef CBFILEGRABBER2_H
#define CBFILEGRABBER2_H
#include <stdint.h>
#define cbfg_log(fmt,...) fprintf(stdout, fmt "\n", ##__VA_ARGS__)
#define cbfg_error(fmt, ...) fprintf(stderr, fmt "\n", ##__VA_ARGS__)


#if !defined(__cplusplus__)
typedef int8_t cb_bool ;
#else
typedef bool cb_bool
#endif // CBFILEGRABBER2_H

#define CB_TRUE  1
#define CB_FALSE 0

#endif
