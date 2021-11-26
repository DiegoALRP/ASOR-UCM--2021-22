#include <stdio.h>
#include <errno.h>
//System (3)
#include <stdlib.h>

int main(int argc, char **argv) {

	//printf("\n[%s][%s][%s]\n", argv[0], argv[1], argv[2]);

	printf("\nComando introducido: %s\n", argv[1]);

	int i = system(argv[1]);

	if (i == -1) {

		printf("ERROR: el comando no se ha ejecutado correctamente!");
	}
	else {

		printf("El comando terminó de ejecutarse\n");
	}

	return 0;
}