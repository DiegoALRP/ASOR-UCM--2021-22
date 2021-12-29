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

int main(int argc, char *argv[]) {

	if (argc != 2) {
	
		printf("Introduce la ruta del fichero\n");
		printf("Usage: %s <filename>\n", argv[0]);
		
		return -1;
	}

	printf("argv[0]: %s, argv[1]: %s\n", argv[0], argv[1]);
	
	int fd = open(argv[1], O_CREAT | O_TRUNC | O_RDWR, 0777);	
	
	if (fd == -1) {
	
		printf("Error open() %d: %s\n", errno, strerror(errno));
		
		close(fd);
		
		return -1;
	}
	
	if (lockf(fd, F_TLOCK, 0) == -1) {
	
		printf("El fichero está siendo usado!\n");
		printf("Error lockf() %d: %s\n", errno, strerror(errno));
		
		close(fd);
		
		return -1;
	}
	
	time_t tiempo;
	time(&tiempo);
	
	char buf[50];
	
	struct tm local;
	local = *localtime(&tiempo);
	
	strftime(buf, 50, "Tiempo actual: %T\n", &local);
	
	printf(buf);
	
	sleep(10);
	
	close(fd);
	
	return 0;
}