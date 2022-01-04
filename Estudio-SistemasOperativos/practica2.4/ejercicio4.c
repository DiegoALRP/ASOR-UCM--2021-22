//printf
#include <stdio.h>
//strerror
#include <string.h>
//errno
#include <errno.h>
//mkfifo
#include <sys/types.h>
#include <sys/stat.h>
//write
#include <unistd.h>
//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

	
	/*if (mkfifo("ejercicio4prueba", 0777) == -1) {
	
		printf("Error mkfifo() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}*/
	
	int fd = open("ejercicio4prueba", O_CREAT | O_TRUNC | O_WRONLY, 0222);
	
	if (fd == -1) {
	
		printf("Error open() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	
	int bytes = write(fd, argv[0], strlen(argv[0]));
	
	if (bytes == -1) {
	
		printf("Error write() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}

	return 0;
}