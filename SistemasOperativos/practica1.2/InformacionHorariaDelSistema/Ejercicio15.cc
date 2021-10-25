#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <locale.h>

int main() {

    time_t tiempo = time(NULL);
    struct tm tiempoLocal = *localtime(&tiempo);
        
    char* c;
    size_t tam = 99;

    setlocale(LC_ALL, "es_ES");
    
    tam = strftime(c, tam, "%A, %d de %B de %Y, %R", &tiempoLocal);
    printf("%s\n", c);

    return 1;
}