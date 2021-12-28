#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

	uid_t real = getuid();
	uid_t efectivo = geteuid();

	printf("UID real: %d\n", getuid());
	printf("UID efectivo: %d\n", geteuid());

	 if (uid == euid) {

        printf("El bit setuid esta activado, porque uid y euid coinciden\n");
    } 
    else {

        printf("El bit setuid no esta activado, porque uid y euid no coinciden\n");
    }

	return 0;
}