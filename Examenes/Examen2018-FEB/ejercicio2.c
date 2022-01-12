#include <stdio.h>
#include <string.h>
#include <errno.h>
//readdir
#include <dirent.h>
//stat
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main (int argc, char *argv[]) {

	printf("argv[0]: %s, argv[1]: %s\n", argv[0], argv[1]);
	
	if (argc != 2) {
	
		printf("Ingresa los parametros correctamente\n");
		printf("Uso: %s <ruta del directorio>\n");
	}
	
	DIR *dir = opendir(argv[1]);
	
	struct dirent *entrada;

    entrada = readdir(dir);
    
    while (entrada != NULL) {
    
    	printf("DENTRO\n");
    	
    	char nombre[256];
    	strcpy(nombre, entrada->d_name);
    	
    	if ((strcmp(nombre, ".") == 0) || (strcmp(nombre, "..") == 0)) {
    	
    		struct stat buf;
    	
			if (stat(nombre, &buf) == -1) {
			
				printf("Error stat() %d: %s\n", errno, strerror(errno));
				
				return -1;
			}
			
			printf("UID propietario: %d\n", buf.st_uid);
			printf("Número de i-nodo: %d\n", buf.st_ino);
			printf("Tamaño del fichero: %d\n", buf.st_size);
    		entrada = readdir(dir);
    		continue;
    	}
    	
    	char prueba[256];
    	strcpy(prueba, argv[1]);
    	strcat(prueba, "/");
    	strcat(prueba, nombre);
    	
    	printf("Nombre: %s\n", nombre);
    	printf("Ruta completa: %s\n", prueba);
    	
    	struct stat buf;
    	
    	if (stat(prueba, &buf) == -1) {
    	
    		printf("Error stat() %d: %s\n", errno, strerror(errno));
    		
    		return -1;
    	}
    	
    	printf("UID propietario: %d\n", buf.st_uid);
    	printf("Número de i-nodo: %d\n", buf.st_ino);
    	printf("Tamaño del fichero: %d\n", buf.st_size);
    	
    	entrada = readdir(dir);
    }
	
	return 0;
}