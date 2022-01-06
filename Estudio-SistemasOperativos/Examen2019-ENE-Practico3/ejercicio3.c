#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//socket
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

int main(int argc, char *argv[]) {

	if (argc != 3) {
	
		printf("Introduce correctamente los parámetros\n");
		printf("Uso: %s <dirección> <puerto>\n");
		
		return -1;
	}
	
	struct addrinfo hints;
	struct addrinfo *result;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
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
		
		return -1;
	}

	if (listen(socketfd, 16) == -1) {
	
		printf("Error listen() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	while (1) {
	
		struct sockaddr_storage peer_addr;
		socklen_t peer_addr_len;
	}




	return 0;
}