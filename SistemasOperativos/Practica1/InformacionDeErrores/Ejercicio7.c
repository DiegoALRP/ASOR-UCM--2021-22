#include <unistd.h>
#include <stdio.h>

const char* path = "/";

int main() {
	printf("Numero maximo de enlaces: %ld\n", pathconf(path, _PC_LINK_MAX));
	printf("Tamaño maximo de una ruta: %ld\n", pathconf(path, _PC_PATH_MAX));
	printf("Tamaño maximo del nombre de fichero: %ld\n", pathconf(path, _PC_NAME_MAX));
	return 0;
}