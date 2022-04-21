#include<stdio.h>
#include<string.h>
#include<errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include<wiringSerial.h>

int main(){
    int fd;
    if ((fd=serialOpen("/dev/ttyACM0",9600)) < 0){
        fprintf(stderr,"Unable to open serial device: %s\n", strerror(errno));
        return 1;
    }

    for (;;){
        if (serialGetchar(fd) == '1') {
                        system("gtts-cli \"일어나세요\" --lang ko | mpg123 - ");
        } else if (serialGetchar(fd) == '2') {
                        system("gtts-cli \"잠시 창문을 열고 환기시키는건 어떨까요?\" --lang ko | mpg123 - ");
        } else if (serialGetchar(fd) == '3') {
                        system("gtts-cli \"안전운전하세요^^\" --lang ko | mpg123 - ");
        }

        fflush(stdout);
    }
}
