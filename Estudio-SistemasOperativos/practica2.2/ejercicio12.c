#include <stdio.h>
#include <errno.h>
#include <unistd.h>
//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
       
int main(int argc, char *argv[]) {

	printf("argv[0]: %s, argv[1]: %s\n", argv[0], argv[1]);
	
	int oldfd = 1;
	int newfd = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 0777);
	
	if (dup2(newfd, oldfd) == -1) {
	
		printf("Error dup2 %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	printf("Hola\n");
	printf("Esto es una prueba\n");
	
	close(newfd);
	
	return 0;
}