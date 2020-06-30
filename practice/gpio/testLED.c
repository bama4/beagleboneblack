#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define MAX_PATH 255
#define PIN_SIZE 2
#define OUT_SIZE 3
#define DELAY 4
const char * GPIO_DEV = "gpio";
const char * GPIO_EXPORT = "export";
const char * GPIO_UNEXPORT = "unexport";
const char * GPIO_PATH = "/sys/class/gpio";
const char * GPIO_DIR = "direction";
const char * GPIO_VAL = "value";
const char * PATH_DELIMIT = "/";
const char * GPIO_DIR_OUT = "out";
const int  GPIO_HIGH = 1;
const int  GPIO_LOW = 0;
const char * PIN = "67";

int main(){  
    char path[MAX_PATH+1];
    memset(path, '\0', MAX_PATH+1);
    /* Need to set pin exposed to userspace
    int err = 0;
    int char_count = snprintf(path, MAX_PATH, "%s/%s", GPIO_PATH, GPIO_EXPORT);
    FILE * file_ptr = fopen(path,"w");
    err = fprintf(file_ptr, "67\n");
    fclose(file_ptr);
    printf("%s count: %d\n", path, char_count);
    memset(path, '\0', MAX_PATH);
    */
    
    snprintf(path, MAX_PATH, "%s/%s%s/%s", GPIO_PATH, GPIO_DEV, PIN, GPIO_DIR);
    //printf("%s\n", path);
    FILE * file_ptr = fopen(path,"w");
    if (file_ptr == NULL){
        printf("Null\n");
    }
    //printf("b\n");
    fprintf(file_ptr, GPIO_DIR_OUT);
    printf("%s\n", path);
    //printf("%s errno: %s\n", path, strerror(errno));
    fclose(file_ptr);
    memset(path, '\0', MAX_PATH);
    
    snprintf(path, MAX_PATH, "%s/%s%s/%s", GPIO_PATH, GPIO_DEV, PIN, GPIO_VAL);
    file_ptr = fopen(path,"w");
    if (file_ptr == NULL){
        printf("Null\n");
    }
    int on = GPIO_HIGH;
    while(1){
        fprintf(file_ptr, "%d\n", on);
        fflush(file_ptr);
        printf("%s errno: %s\n", path, strerror(errno));
        if(!on){
            on = GPIO_HIGH;
        }else{
            on = GPIO_LOW;
        }
        sleep(DELAY);
    //Add code for cleanup later on
    //fclose(file_ptr);
        
    }
    fclose(file_ptr);
    return 0;
}