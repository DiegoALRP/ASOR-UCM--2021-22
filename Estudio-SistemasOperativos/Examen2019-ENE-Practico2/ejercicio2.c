#include <stdio.h>
#include <string.h>
#include <errno.h>
//getaddrinfo
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//socket, bind, accept, recv, send
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
//getnameinfo
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char *argv[]) {

	if (argc != 3) {
	
		printf("Introduce correctamente los parámetros\n");
		printf("Uso: %s <direccion> <puerto>\n");
		
		return -1;
	}
	
	struct addrinfo hints;
	struct addrinfo *result;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Stream socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	if (getaddrinfo(argv[1], argv[2], &hints, &result) != 0) {
	
		printf("Error getaddringfo() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}

	int socketfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	
	if (socketfd == -1) {
	
		printf("Error socket() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	if (bind(socketfd, result->ai_addr, result->ai_addrlen) == -1) {
	
		printf("Error bind() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	if (listen(socketfd, 16) == -1) {
	
		printf("Error listen() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	freeaddrinfo(result);
	
	while (1) {
	
		struct sockaddr_storage client;
		socklen_t client_len = sizeof(struct sockaddr_storage);
	
		int accfd = accept(socketfd, (struct sockaddr *) &client, &client_len);
	
		char host[NI_MAXHOST];
		char serv[NI_MAXSERV];
	
		int nameInfo = getnameinfo((struct sockaddr *) &client, client_len,
		                   host, NI_MAXHOST,
		                   serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
		                   
		if (nameInfo == -1) {
		
			printf("Error getnameinfo() %d: %s\n", errno, strerror(errno));
		}
	
		printf("Conexión desde: Host: %s, Puerto: %s\n", host, serv);
		
		char buf_recv[80];
		int bytes;
		while (bytes = recv(accfd, buf_recv, 80, 0)) {
		
			if (bytes == -1) {
			
				printf("Error recv() %d: %s\n", errno, strerror(errno));
				
				return -1;
			}
			
			buf_recv[bytes] = '\0';
			printf("Mensaje recibido: %s\n", buf_recv);
		
			int bytes_sd = send(accfd, host, strlen(host), 0);
			
			if (bytes_sd == -1) {
			
				printf("Error send() %d: %s\n", errno, strerror(errno));
				
				return -1;
			}
		}
	}

	return 0;
}

