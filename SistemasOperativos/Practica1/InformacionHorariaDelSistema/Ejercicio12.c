#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {

    time_t tiempo;

    //time_t time(time_t *t);
    if (time(&tiempo) == -1) {

        printf("ERROR(%d): %s\n", errno, strerror(errno));
    } 
    else {

        printf("Seconds since EPOCH (1/1/1970 00:00:00 UTC): %li\n", tiempo);
    }

    return 1;
}