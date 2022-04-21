#include<stdio.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<wiringSerial.h>

int main(){
    int fd;
    if((fd=serialOpen("/dev/ttyACM1",9600))<0){
        fprintf(stderr,"Unable to open serial device: %s\n", strerror(errno));
        return 1;
    }
    for(;;){
         if(serialGetchar(fd)=='1') // 시리얼 모니터에서 나오는것
        {
                for(int i =0; i<1; i++){
			system("gtts-cli \"졸음 운전 위험이 있습니다. 일어나세요\" --lang ko | mpg123 - ");
		}
        }

        fflush(stdout);
    }
}
