#include <stdio.h>
#include <stdlib.h>
//Gestión de errores:
#include <errno.h>
//Getuid/sysconf
#include <unistd.h>
//Perror
#include <string.h>
//Uname
#include <sys/utsname.h>
//id
#include <sys/types.h>

int main(){

    uid_t uid = getuid();

    printf("UID Real: %d\n", getuid());
    printf("UID efectivo: %d\n", geteuid());

  return 1;
}