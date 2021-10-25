#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main(){

    uid_t uid = getuid();
    uid_t euid = geteuid();

    printf("UID Real: %d\n", uid);
    printf("UID efectivo: %d\n", euid);

    struct passwd infoUsuario = *getpwuid(uid);

    printf("Nombre de usuario: %s\n", infoUsuario.pw_name);
    printf("Directorio 'home': %s\n", infoUsuario.pw_dir);
    printf("Descripcion del usuario: %s\n", infoUsuario.pw_gecos);
    

  return 1;
}