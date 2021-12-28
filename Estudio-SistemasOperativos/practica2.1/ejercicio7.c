#include <stdio.h>
#include <unistd.h>

int main() {

	printf("Número máximo de enlances: %d\n", fpathconf(0, _PC_LINK_MAX));
	printf("Tamaño máximo de una ruta: %d\n", fpathconf(0, _PC_PATH_MAX));
	printf("Tamaño máximo de un nombre de fichero: %d\n", fpathconf(0, _PC_NAME_MAX));
	
	printf("Número máximo de enlances: %d\n", pathconf("/",_PC_LINK_MAX));
	printf("Tamaño máximo de una ruta: %d\n", pathconf("/",_PC_PATH_MAX));
	printf("Tamaño máximo de un nombre de fichero: %d\n", pathconf("/",_PC_NAME_MAX));
	
	return 0;
}