#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){

    uid_t uid = getuid();
    uid_t euid = geteuid();

    printf("UID Real: %d\n", uid);
    printf("UID efectivo: %d\n", euid);

    if (uid == euid) {

        printf("El bit setuid esta activado, porque uid y euid coinciden\n");
    } 
    else {

        printf("El bit setuid no esta activado, porque uid y euid no coinciden\n");
    }

  return 1;
}