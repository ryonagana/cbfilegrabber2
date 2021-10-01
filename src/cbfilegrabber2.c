#include <stdio.h>
#include "data/list.h"
#include "cb_file.h"
#include "cb_compress.h"
#include "cbfilegrabber2.h"


mz_zip_archive zip_archive = {0};
char *exe_name = NULL;

void zip_start(mz_zip_archive* zip, const char *filename);
void zip_end(mz_zip_archive* zip);
void zip_add_file(const char *zip_path, const char *filename);
void help(void);
char* basename(const char *path){
#if defined(WIN32) || defined(__WIN32__)
        char *s = strrchr(path,'\\');
#else
        char *s = strrchr(path,'/');
#endif
        if(!s){
            return strdup(path);
        }

        return strdup(s + 1);
}

void help(void){
    cbfg_log("CB File Grabber 2.0 - archdark\n\n");
    cbfg_log("%s --zip <zip name> --file  <file.extension>\n\n", exe_name);
    cbfg_log("e.g:  %s --zip myassets.zip --file myasset.png\n", exe_name);
    cbfg_log("please consider creating a .bat or .sh file to process assets\n\n");
}

void process_args(int* argc, char** argv){

    (void)argc;

    if(!argv[1] || *argc <= 1){
        help();
        exit(-1);
    }else if(*argc > 1){
        switch(*argv[1]){
            case '-':{
                if(strncmp("--zip", argv[1], 32) != -1 || strncmp("--package", argv[1], 32) != -1  ){

                    if(strlen(argv[2]) == 0){
                        zip_start(&zip_archive, "assets.zip");
                    }else {
                           zip_start(&zip_archive, argv[2]);
                    }

                    zip_end(&zip_archive);
                }


                if(strncmp("--file", argv[3], 32) != -1){
                    if(strlen(argv[4]) == 0){
                        cbfg_error( "%s - file is missing\n", __FUNCTION__);
                        exit(-1);
                        return;
                    }else {
                        //cb_compress_add_file_to_zip(&zip_archive, argv[4], "Assets CBEngine");
                        zip_add_file(argv[2], argv[4]);
                    }
                }
             }
             break;
        }
    }

   zip_end(&zip_archive);
}




void zip_start(mz_zip_archive* zip, const char *filename){
    FILE* fp = NULL;

    if(NULL == (fp = fopen(filename,"rb+"))){
        if(cb_compress_init_zip(zip,filename) < 0){
            cbfg_error( "%s - zip file failed to create\n", __FUNCTION__);
            return;
        }
    }

    fclose(fp);


}
void zip_end(mz_zip_archive* zip){
    cb_compress_end(zip);
}



void zip_add_file(const char *zip_path, const char *filename){
    const char* comment = "Cb Archive\n";
    FILE *fp = NULL;

    if(NULL == (fp = fopen(filename, "rb+"))){
        cbfg_error( "file %s does not exists, ignoring.", filename);
        return;
    }

    unsigned char *buf = NULL;
    mz_uint64 size  = 0;

    fseek(fp,0,SEEK_END);
    size = ftell(fp);
    fseek(fp,0,SEEK_SET);
    buf = calloc(size + 1, 1);
    fread(buf,size,1,fp);
    fclose(fp);
    mz_zip_add_mem_to_archive_file_in_place(zip_path, filename, buf, size, (const char*)comment, strlen(comment), MZ_BEST_COMPRESSION);
    free(buf);
    cbfg_log("file %s added to resource: %s", filename, zip_path);
    return;
}



int main(int argc, char *argv[])
{
    exe_name = basename(argv[0]);
    process_args(&argc, argv);
    if(exe_name) free(exe_name);
    return 0;
}

