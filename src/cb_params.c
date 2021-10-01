#include "cb_params.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

cb_bool cb_params_check(const char *param_text, const char *param_list_text, char **argv, void (*param_callback)(const char *param_text, char **argv))
{
    if(strncmp(param_text, param_list_text,32) == 0){
        if(param_callback){
            param_callback(param_text,argv);
        }
        return CB_TRUE;
    }
    return CB_FALSE;
    /*
    if(!params){
        return CB_FALSE;
    }

    if(param_callback){
        param_callback(params, argc,argv);
    }

    return CB_TRUE;
    */
}
