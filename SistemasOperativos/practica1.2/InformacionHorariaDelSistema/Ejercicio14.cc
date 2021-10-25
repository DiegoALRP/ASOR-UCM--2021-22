#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

int main() {

    time_t tiempo = time(NULL);

    //time_t time(time_t *t);
    if (time(&tiempo) == -1) {

        printf("ERROR(%d): %s\n", errno, strerror(errno));
    } 
    else {

        struct tm tiempoLocal = *localtime(&tiempo);
        
        // tm_year años desde 1900 (man 3 localtime)
        printf("Estamos en el año: %li\n", tiempoLocal.tm_year + 1900);
    }

    return 1;
}