#include <unistd.h>
#include <stdio.h>
#include <errno.h>
//time
#include <time.h>
//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
//opendir
#include <sys/types.h>
#include <dirent.h>

int recursion(char *argv) {

	int contador = 0;
	
	DIR *dir = opendir(argv);
	
	if (dir == NULL) {
	
		printf("Error opendir() %d: %s\n", errno, strerror(errno));
	}
	
	struct dirent *entradas = readdir(dir);
	//readdir devuelve un puntero al primer fichero del directorio
	
	while (entradas != NULL) {
	
		printf("Nombre: %s\n", entradas->d_name);
		printf("Numero: %d\n", entradas->d_off);
		
		if (entradas->d_type & DT_REG) {
		
			struct stat buf;
			if (stat(entradas->d_name, &buf) == -1) {
			
				printf("Error stat() %d: %s\n", errno, strerror(errno));
				
				return -1;
			}
			
			if ((buf.st_mode & S_IXUSR) || (buf.st_mode & S_IXGRP) || (buf.st_mode & S_IXOTH)) {
			
				printf("Fichero Regular con permiso de ejecución para usuario, grupos u otros:\n");
				printf("*%s\n", entradas->d_name);
			}
			else {
			
				printf("Fichero Regular:\n");
				printf("%s\n", entradas->d_name);
			}
			
			contador += buf.st_size;
		}
		else if (entradas->d_type & DT_DIR) {
		
			printf("Directorio: \n");
			printf("/%s\n", entradas->d_name);
			
			if (strcmp(entradas->d_name, ".") == 0);
			else if (strcmp(entradas->d_name, "..") == 0);
			else {
			
				char ini[50];
				char fin[50];
				strcpy(ini, argv);
				strcat(ini, "/");
				strcpy(fin, entradas->d_name);
				strcat(ini, fin);
				printf("Nuevo nombre: %s\n", ini);
				contador += recursion(ini);
			}
		}
		else if (entradas->d_type & DT_LNK) {
		
			char enlace[50];
			if (readlink(entradas->d_name, enlace, 50) == -1) {
			
				printf("Error readlink() %d: %s\n", errno, strerror(errno));
				
				return -1;
			}
			
			printf("Fichero con enlace simbolico: \n");
			printf("%s->%s\n", entradas->d_name, enlace);
		}
		else {
		
			printf("No es ni directorio, ni fichero ni regular ni simbolico\n");
			printf("%s\n", entradas->d_name);
		}
		
		entradas = readdir(dir);
	}
	
	return contador;
}

int main(int argc, char *argv[]) {

	if (argc != 2) {
	
		printf("Introduce la ruta del directorio\n");
		printf("Usage: %s <dirpath>\n", argv[0]);
		
		return -1;
	}

	printf("argv[0]: %s, argv[1]: %s\n", argv[0], argv[1]);

	int contador = 0;
	
	contador += recursion(argv[1]);
	
	printf("Número total de bytes: %d\n", contador);
	
	return 0;
}