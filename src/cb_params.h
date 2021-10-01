#ifndef CB_PARAMS_H
#define CB_PARAMS_H
#include "cbfilegrabber2.h"
cb_bool cb_params_check(const char *param_text, const char *param_list_text, char**argv, void (*param_callback)(const char *param_text, char *argv[]));

#endif // CB_PARAMS_H
