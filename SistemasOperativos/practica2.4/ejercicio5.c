#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//mknod
#include <sys/types.h>
#include <sys/stat.h>
//open
#include <fcntl.h>
#include <limits.h>

int main(int argc, char** argv) {

	char buffer[256];

	fd_set rfds;

	mkfifo("/home/cursoredes/Documents/Practica4/tub", 0777);
	int fd = open("/home/cursoredes/Documents/Practica4/tub", O_RDONLY | O_NONBLOCK);

	while (1) {

		int listo = 1;
		
		FD_ZERO(& rfds);
		FD_SET(0, & rfds);
		FD_SET(fd, & rfds);

		select(fd + 1, & rfds, 0, 0, 0);

		if (FD_ISSET(0, & rfds)) {

			listo = 0;
			printf("STDIU");
		}
		else if (FD_ISSET(fd, & rfds)) {

			listo = fd;
			printf("Tubería");
		}
		else {

			continue;
		}

		int bytes = read(fd, buffer, 255);

		buffer[256] = '\0';

		if (bytes == 0 && listo == fd) {

			close(fd);
			
			int fd = open("/home/cursoredes/Documents/Practica4/tub", O_RDONLY | O_NONBLOCK);
			continue;
		}

		printf("buffer");
	}

    return 0;

}