#include <stdio.h>
#include <string.h>
#include <errno.h>
//getaddrinfo
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//socket, bind, listen, accept
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

int main(int argc, char *argv[]) {

	if (argc != 3) {
	
		printf("Introduzca correctamente los parámetros\n");
		printf("Uso: %s <dirección> <puerto>\n");
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
	
	int s;
	if (s = getaddrinfo(argv[1], argv[2], &hints, &result) != 0) {
	
		fprintf(stderr, "Error getaddrinfo(): %s\n", gai_strerror(s));
		
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
	
	while (1) {
	
		struct sockaddr_storage client;
		socklen_t client_len = sizeof(struct sockaddr_storage);
		
		int accfd = accept(socketfd, (struct sockaddr *) &client, &client_len);
		
		
	}

	return 0;
}

