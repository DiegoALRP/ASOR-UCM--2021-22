//printf
#include <stdio.h>
//strerror
#include <string.h>
//errno
#include <errno.h>
//write
#include <unistd.h>
//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//select
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

	int fd1 = open("ejercicio3", O_CREAT | O_TRUNC | O_NONBLOCK | O_RDONLY, 0444);
	int fd2 = open("ejercicio4tub", O_CREAT | O_TRUNC | O_NONBLOCK | O_RDONLY, 0444);
	int fd3 = open("ejercicio5tub", O_CREAT | O_TRUNC | O_NONBLOCK | O_RDONLY, 0444);
	
	if ((fd1 == -1) || (fd2 == -1) || (fd3 == -1)) {
	
		printf("Error open() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	printf("FD1: %d\n", fd1);
	printf("FD2: %d\n", fd2);
	printf("FD3: %d\n", fd3);
	
	fd_set readfds;
	struct timeval tv;
	int retval;
	
	//mira stdin (fd 0) para ver cuando hay una entrada
	FD_ZERO(&readfds);
	FD_SET(fd1, &readfds);
	FD_SET(fd2, &readfds);
	FD_SET(fd3, &readfds);
	
	//Espera hasta 5 seg.
	int segs = 5;
	tv.tv_sec = segs;
	tv.tv_usec = 0;
	
	int n = 0;
	while (1) {
	
		FD_ZERO(&readfds);
		FD_SET(fd1, &readfds);
		FD_SET(fd2, &readfds);
		FD_SET(fd3, &readfds);
	
		//Espera hasta 5 seg.
		tv.tv_sec = segs;
		tv.tv_usec = 0;
		
		printf("FD1: %d\n", fd1);
		printf("FD2: %d\n", fd2);
		printf("FD3: %d\n", fd3);
		
		int fdAct;
		
		if ((fd1 > fd2) && (fd1 > fd3)) {
		
			fdAct = fd1;
			printf("Mayor FD1\n");
		}
		if ((fd2 > fd1) && (fd2 > fd3)) {
		
			fdAct = fd2;
			printf("Mayor FD2\n");
		}
		else {
		
			fdAct = fd3;
			printf("Mayor FD3\n");
		}
		
		retval = select(fdAct + 1, &readfds, NULL,
		              NULL, &tv);
	
		if (retval == -1) {
	
			printf("Error select() %d: %s\n", errno, strerror(errno));
		
			return -1;
		}
		else if (retval) {
	
			printf("Los datos estan disponibles ahora\n");
			
			if (FD_ISSET(fd1, &readfds)) {
			
				char buf[256];
				int bytes = read(fd1, buf, 255);
				
				while(bytes != 0) {
				
					if (bytes == -1) {
					
						printf("Error read() fd1 %d: %s\n", errno, strerror(errno));
						
						return -1;
					}
					
					buf[bytes] = '\0';
					
					printf("FD1 ha leído: %s\n", buf);
					
					bytes = read(fd1, buf, 255);
				}
				
				close(fd1);
				fd1 = open("ejercicio3", O_CREAT | O_TRUNC | O_NONBLOCK | O_RDONLY, 0444);
			}
			if (FD_ISSET(fd2, &readfds)) {
			
				char buf[256];
				int bytes = read(fd2, buf, 255);
				
				while(bytes != 0) {
				
					if (bytes == -1) {
					
						printf("Error read() fd2 %d: %s\n", errno, strerror(errno));
						
						return -1;
					}
					
					buf[bytes] = '\0';
					
					printf("FD2 ha leído: %s\n", buf);
					
					bytes = read(fd2, buf, 255);
				}
				
				close(fd2);
				fd2 = open("ejercicio4tub", O_CREAT | O_TRUNC | O_NONBLOCK | O_RDONLY, 0444);
			}
			if (FD_ISSET(fd3, &readfds)) {
			
				char buf[256];
				int bytes = read(fd3, buf, 255);
				
				while(bytes != 0) {
				
					if (bytes == -1) {
					
						printf("Error read() fd3 %d: %s\n", errno, strerror(errno));
						
						return -1;
					}
					
					buf[bytes] = '\0';
					
					printf("FD3 ha leído: %s\n", buf);
					
					bytes = read(fd3, buf, 256);
				}
				
				close(fd3);
				fd3 = open("ejercicio5tub", O_CREAT | O_TRUNC | O_NONBLOCK | O_RDONLY, 0444);
			}
		}
		else {
	
			printf("Sin datos en los últimos 5 segundos\n");
		}
		
		n++;
		printf("\nVUELTA: %d\n", n);
		//sleep(segs);
	}

	close(fd1);
	close(fd2);
	close(fd3);

	return 0;
}