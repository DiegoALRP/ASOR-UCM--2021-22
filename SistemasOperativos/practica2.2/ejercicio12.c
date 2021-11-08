#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {

	char* path = argv[1];

	int fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0777);
	
	if (fd == -1) {
		
		printf("ERROR(%d): %s\n", errno, strerror(errno));
	}
	else {
		
		int d = dup2(fd, 1);

		if (d == -1) printf("ERROR(%d): %s\n", errno, strerror(errno));
		else {
			
			printf("Prueba!\n");
			printf("Esta es una cadena de prueba\n");
			printf("1, 2, 3,... probando");
		}
	}

	close(fd);
	return 0;
}