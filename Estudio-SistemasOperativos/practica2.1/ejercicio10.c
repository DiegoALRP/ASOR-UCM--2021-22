#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main() {

	uid_t real = getuid();
	uid_t efectivo = geteuid();

	printf("UID real: %d\n", getuid());
	printf("UID efectivo: %d\n", geteuid());

	 if (real == efectivo) {

        printf("El bit setuid esta activado, porque uid y euid coinciden\n");
    } 
    else {

        printf("El bit setuid no esta activado, porque uid y euid no coinciden\n");
    }

	struct passwd info;
	info = *getpwuid(real);
	
	printf("Nombre de usuario: %s\n", info.pw_name);
	printf("Directorio Home: %s\n", info.pw_dir);
	printf("Información del usuario: %s\n", info.pw_gecos);
	
	return 0;
}