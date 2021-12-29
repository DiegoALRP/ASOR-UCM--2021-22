#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main () {

	umask(027);

	int fd = open("ejercicio7prueba.c", O_CREAT | O_RDWR | O_TRUNC, 0645);
	
	if (fd == -1) {
	
		printf("Error open() %d: %s\n", errno, strerror(errno));

        return -1;
	}
	
	return 0;
}