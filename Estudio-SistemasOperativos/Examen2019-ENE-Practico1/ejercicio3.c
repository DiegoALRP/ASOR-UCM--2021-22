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
//socket
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

int main(int argc, char *argv[]) {

	if (argc != 3) {
	
		printf("Introduce correctamente los parámetros\n");
		printf("Uso: %s <dirección> <puerto>\n", argv[0]);
		
		return -1;
	}
	
	printf("argv[0]: %s, argv[1]: %s, argv[2]: %s\n", argv[0], argv[1], argv[2]);
	
	struct addrinfo hints;
	struct addrinfo *result;
	int sfd, s;

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
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		
		return -1;
	}
	
	int socketfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	
	if (socketfd == -1) {
	
		printf("Error socket() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}

	


	return 0;
}