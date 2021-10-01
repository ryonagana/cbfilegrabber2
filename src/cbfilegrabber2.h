#ifndef CBFILEGRABBER2_H
#define CBFILEGRABBER2_H

#define cbfg_log(fmt,...) fprintf(stdout, fmt "\n", ##__VA_ARGS__)
#define cbfg_error(fmt, ...) fprintf(stderr, fmt "\n", ##__VA_ARGS__)
#endif // CBFILEGRABBER2_H
