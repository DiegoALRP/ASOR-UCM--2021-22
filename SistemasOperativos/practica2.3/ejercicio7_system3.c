#include <stdio.h>
#include <errno.h>
//System (3)
#include <stdlib.h>

int main(int argc, char **argv) {

	//printf("\n[%s][%s][%s]\n", argv[0], argv[1], argv[2]);

	printf("\nComando introducido: %s\n", argv[1]);

	int i = system(argv[1]);

	printf("El comando terminó de ejecutarse\n");

	return 0;
}