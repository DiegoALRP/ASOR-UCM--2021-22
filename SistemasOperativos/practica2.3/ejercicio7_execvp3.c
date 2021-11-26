#include <stdio.h>
#include <errno.h>
//Execvp (3)
#include <unistd.h>
//Procesos
#include <stdlib.h>

int main(int argc, char **argv) {

	//printf("\n[%s][%s][%s]\n", argv[0], argv[1], argv[2]);

	printf("\nComando introducido: %s\n", argv[1]);

	int i = execvp(argv[1], &(argv[1]));

	if (i == -1) {
    		
		printf("ERROR: No se ha ejecutado correctamente.\n");
  	}
	else {

		printf("El comando terminó de ejecutarse\n");
	}

	return 0;
}