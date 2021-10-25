#include <unistd.h>
#include <stdio.h>

int main() {

	printf("Longitud maxima de argumentos: %ld\n", sysconf(_SC_ARG_MAX));
	printf("Numero maximo de hijos: %ld\n", sysconf(_SC_CHILD_MAX));
	printf("Numero maximo de ficheros: %ld\n", sysconf(_SC_OPEN_MAX));

	return 0;
}