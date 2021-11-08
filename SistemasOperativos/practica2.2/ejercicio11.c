#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv) {

	char* path = argv[1];
	
	printf("Ruta: %s\n", path);

	struct stat buf;
	int st = stat(path, &buf);

	mode_t proteccion = buf.st_mode;
	if (S_ISREG(proteccion)) {

		char* symPath;
		char* hardPath;

		symPath = malloc(strlen(path));
		hardPath = malloc(strlen(path));

		strcpy(symPath, path);
		strcat(symPath, ".sym");
		strcpy(hardPath, path);
		strcat(hardPath, ".hard");
		printf("Es un fichero regular.\n");

		int hard = link(path, hardPath);
		int sym = symlink(path, symPath);

		if (hard == -1 || sym == -1) printf("ERROR(%d): %s\n", errno, strerror(errno));
		else {

			printf("Ruta sym: %s\n", symPath);
			printf("Ruta hard: %s\n", hardPath);
		}
		
		free(symPath);
		free(hardPath);
	}
	else {
		
		printf("No es un fichero regular\n");
	}
}