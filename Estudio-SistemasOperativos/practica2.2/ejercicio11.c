#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
//strcat
#include <string.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
	
		printf("Introduce la ruta del fichero\n");
		printf("Usage: %s <filename>\n", argv[0]);
		
		return -1;
	}
    
	printf("argv[0]: %s, argv[1]: %s, argv[2]: fin\n", argv[0], argv[1]);

	struct stat info;
	
	if (stat(argv[1], &info)) {
	
		printf("Error stat() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	if (info.st_mode & S_IFREG) {
	
		printf("Es un fichero regular\n");
	}
	else {
	
		printf("No es un fichero regular, introduce la ruta de un fichero regular\n");
		
		return -1;
	}
	
	//char simbolico;
	//char src[50] = "a";
	//char dest[50] = "b";
	//strcpy(src,  "a");
	//strcpy(dest, "b");
	//strncat(src, dest, 10);
	
	char simbolico[50];
	char rigido[50];
	
	strcpy(simbolico, argv[1]);
	strcpy(rigido, argv[1]);
	
	strcat(simbolico, ".sym");
	strcat(rigido, ".hard");
	
	printf("Simbolico: %s\n", simbolico);
	printf("Rigido: %s\n", rigido);
	
	if (link(argv[1], rigido) == -1) {
	
		printf("Error link() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	if (symlink(argv[1], simbolico) == -1) {
	
		printf("Error symlink() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	

	return 0;
}

