#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv) {

	char pathname[] = "/home/cursoredes/Documents/Practica2/ejercicio5.txt";

	int fd = open(pathname, O_CREAT | O_TRUNC | O_RDWR, 645);
	
	if (fd == -1) {
		
		printf("ERROR(%d): %s\n", errno, strerror(errno));
	}
	else {
		
		printf("FileDescriptor: %d\n", fd);
	}

	close(fd);
	return 0;
}