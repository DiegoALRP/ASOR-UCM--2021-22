#include <stdio.h>
#include <string.h>
#include <errno.h>
//getaddrinfo
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//getnameinfo
#include <sys/socket.h>
#include <netdb.h>
//socket, bind, recv, send
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
//time
#include <time.h>
//select
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
//read
#include <unistd.h>

int main(int argc, char *argv[]) {

	if (argc != 3) {
	
		printf("Introduce correctamente los parámetros\n");
		printf("Uso: %s <dirección> <puerto>\n", argv[0]);
		
		return -1;
	}
	
	printf("argv[0]: %s, argv[1]: %s, argv[2]: %s\n", argv[0], argv[1], argv[2]);
	
	struct addrinfo hints;
	struct addrinfo *result;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0) {
	
		printf("Error getaddrinfo() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	int socketfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	
	if (socketfd == -1) {
	
		printf("Error socket() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}

	if (bind(socketfd, result->ai_addr, result->ai_addrlen) == -1) {
	
		printf("Error bind() %d: %s\n", errno, strerror(errno));
		
		close(socketfd);
		return -1;
	}
	
	freeaddrinfo(result);
	
	fd_set readfds;
	struct timeval tv;
	int retval;
	
	while (1) {
	
		FD_ZERO(&readfds);
		FD_SET(0, &readfds);
		FD_SET(socketfd, &readfds);
	
		tv.tv_sec = 10;
		tv.tv_usec = 0;
		
		retval = select(socketfd + 1, &readfds, NULL, NULL, &tv);
		
		if (retval == -1) {
		
			printf("Error select() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		else if (retval) {
		
			time_t tiempo;
			time(&tiempo);
			struct tm tiempolocal = *localtime(&tiempo);
		
			char buf_time[100];
			int bytes_time = strftime(buf_time, 100, "%H:%M:%S\n", &tiempolocal);
		
			if (FD_ISSET(0, &readfds)) {
			
				printf("Lectura desde terminal\n");
				
				char buf[100];
				int bytes = read(0, buf, 100);
				
				if (bytes == -1) {
				
					printf("Error read() %d: %s\n", errno, strerror(errno));
					
					return -1;
				}
				
				buf[bytes] = '\0';
				printf("Se ha leido desde terminal: %s\n", buf);
				printf("Hora: %s\n", buf_time);
			}
			
			if (FD_ISSET(socketfd, &readfds)) {
			
				struct sockaddr_storage client;
				socklen_t client_len = sizeof(struct sockaddr_storage);
		
				char buf_rd[256];
				int bytes_rd = recvfrom(socketfd, buf_rd, 256, 0, (struct sockaddr *) &client, &client_len);
		
				if (bytes_rd == -1) {
		
					printf("Error recvfrom() %d: %s\n", errno, strerror(errno));
			
					close(socketfd);
					return -1;
				}
		
				buf_rd[bytes_rd] = '\0';
				printf("El servidor ha leido: %s\n", buf_rd);
		
				char host[NI_MAXHOST];
				char serv[NI_MAXSERV];
		
				int nameInfo = getnameinfo((struct sockaddr *)&client, client_len,
										host, NI_MAXHOST,
										serv, NI_MAXSERV, 
										NI_NUMERICHOST | NI_NUMERICSERV);
								
				if (nameInfo == -1) {
		
					printf("Error getnameinfo() %d: %s\n", errno, strerror(errno));
			
					close(socketfd);
					return -1;
				}
		
				printf("Conexión desde Host: %s, Puerto: %s\n", host, serv);
		
				int bytes_sd = sendto(socketfd, buf_time, bytes_time, 0, (struct sockaddr *) &client, client_len);
		
				if (bytes_sd == -1) {
		
					printf("Error sendto() %d: %s\n", errno, strerror(errno));
			
					close(socketfd);
					return -1;
				}
		
				printf("Servidor ha enviado: %s\n", buf_time);
			}
		}
		else {
		
			printf("Ningún dato leído en los últimos 10 segundos\n");
		}
	}

	close(socketfd);

	return 0;
}