#include <stdio.h>
#include <unistd.h>

int main() {

	printf("Longitud máxima de los argumentos: %d\n", sysconf(_SC_ARG_MAX));
	printf("Número máximo de hijos: %d\n", sysconf(_SC_CHILD_MAX));
	printf("Número máximo de ficheros abiertos: %d\n", sysconf(_SC_OPEN_MAX));
	
	return 0;
}