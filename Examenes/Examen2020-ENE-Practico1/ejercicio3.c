#include <stdio.h>
#include <string.h>
#include <errno.h>
//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//time
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

	int fd1 = open("tuberia1", O_NONBLOCK | O_RDONLY);
	int fd2 = open("tuberia2", O_NONBLOCK | O_RDONLY);

	fd_set readfds;
	struct timeval tv;
	int retval;
	
	while (1) {
	
		FD_ZERO(&readfds);
		FD_SET(fd1, &readfds);
		FD_SET(fd2, &readfds);
		
		tv.tv_sec = 10;
		tv.tv_usec = 0;
		
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
		
			if (FD_ISSET(fd1, &readfds)) {
			
				printf("Lectura tuberia1\n");
				
				char buf[256];
				int bytes;
				
				while (bytes = read(fd1, buf, 256)) {
				
					if (bytes == -1) {
					
						printf("Error read() %d: %s\n", errno, strerror(errno));
						
						return -1;
					}
					
					buf[bytes] = '\0';
					printf("Tubería1 ha leído: %s\n", buf);
				}
				
				close(fd1);
				int fd1 = open("tuberia1", O_NONBLOCK | O_RDONLY);
			}
			
			if (FD_ISSET(fd2, &readfds)) {
			
				printf("Lectura tuberia2\n");
				
				char buf[256];
				int bytes;
				
				while (bytes = read(fd2, buf, 256)) {
				
					if (bytes == -1) {
					
						printf("Error read() %d: %s\n", errno, strerror(errno));
						
						return -1;
					}
					
					buf[bytes] = '\0';
					printf("Tubería2 ha leído: %s\n", buf);
				}
				
				close(fd2);
				int fd2 = open("tuberia2", O_NONBLOCK | O_RDONLY);
			}
		}
		else {
		
			printf("Sin datos leídos en los últimmos 10 segundos\n");
		}
	}

	return 0;
}