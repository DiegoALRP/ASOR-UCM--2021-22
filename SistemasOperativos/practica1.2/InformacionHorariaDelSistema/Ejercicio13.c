#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

const int MILLON = 1000000;

int main() {

    struct timeval tiempoA;
    //struct timezone zonaA;
    struct timeval tiempoB;
    //struct timezone zonaB;

    //int gettimeofday(struct timeval *tv, struct timezone *tz);
    int start = gettimeofday(&tiempoA, NULL);

    if (start == -1) {

        printf("ERROR %i -> %s", errno, strerror(errno));
    
    }
    else {

        for (int i = 0; i < MILLON; ++i);

        int end = gettimeofday(&tiempoB, NULL);

        if (end == -1) {
    
            printf("ERROR %i -> %s", errno, strerror(errno));
    
        } else {
            
            printf("Tiempo de ejecucion: %li us\n", tiempoB.tv_usec-tiempoA.tv_usec);        

        }
    }

    return 1;
}