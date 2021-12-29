#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main () {

	int fd = open("ejercicio5prueba.c", O_CREAT | O_RDWR | O_TRUNC, 0645);
	
	if (fd == -1) {
	
		printf("Error open() %d: %s\n", errno, strerror(errno));
	}
	
	return 0;
}