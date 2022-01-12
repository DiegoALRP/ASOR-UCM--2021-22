#include <stdio.h>
#include <string.h>
#include <errno.h>
//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//select
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
//read
#include <unistd.h>

int main() {

	int fd1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
	int fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);

	if (fd1 == -1) {
	
		printf("Error tuberia1 open() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	if (fd2 == -1) {
	
		printf("Error tuberia2 open() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	fd_set readfds;
	struct timeval tv;
	int retval;
	
	/*FD_ZERO(&readfds);
	FD_SET(fd1, &readfds);
	FD_SET(fd2, &readfds);
	
	tv.tv_sec = 5;
	tv.tv_usec = 0;*/
	
	int n = 0;
	while(1) {
	
		FD_ZERO(&readfds);
		FD_SET(fd1, &readfds);
		FD_SET(fd2, &readfds);
	
		tv.tv_sec = 5;
		tv.tv_usec = 0;
	
		printf("FD Tuberia1: %d\n", fd1);
		printf("FD Tuberia2: %d\n", fd2);
		
		int fdAct;
		
		if (fd1 > fd2) {
		
			fdAct = fd1;
		}
		else {
		
			fdAct = fd2;
		}
		
		retval = select(fdAct + 1, &readfds, NULL, NULL, &tv);
		
		if (retval == -1) {
		
			printf("Error select() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		else if (retval) {
		
			printf("Hay datos!\n");
			
			if (FD_ISSET(fd1, &readfds)) {
			
				char buf[256];
				int bytes = read(fd1, buf, 255);
				
				while (bytes != 0) {
				
					if (bytes == -1) {
				
						printf("Error fd1 read() %d: %s\n", errno, strerror(errno));
					
						return -1;
					}
					
					buf[bytes] = '\0';
					printf("Se ha leido de la tubería1: %s\n", buf);
					
					bytes = read(fd1, buf, 255);
				}
				
				printf("Se ha cerrado la escritura de la tuberia1\n");
				
				close(fd1);
				fd1 = open("tuberia1", O_RDONLY | O_NONBLOCK);
			}
			
			if (FD_ISSET(fd2, &readfds)) {
			
				char buf[256];
				int bytes = read(fd2, buf, 255);
				
				while (bytes != 0) {
				
					if (bytes == -1) {
				
						printf("Error fd2 read() %d: %s\n", errno, strerror(errno));
					
						return -1;
					}
					
					buf[bytes] = '\0';
					printf("Se ha leido de la tubería2: %s\n", buf);
					
					bytes = read(fd2, buf, 255);
				}
				
				printf("Se ha cerrado la escritura de la tuberia2\n");
				
				close(fd2);
				fd2 = open("tuberia2", O_RDONLY | O_NONBLOCK);
			}
		}
		else {
		
			printf("Sin datos en los últimos 5 segundos\n");
		}
		
		n++;
		printf("Vuelta: %d\n", n);
	}
	
	return 0;
}

