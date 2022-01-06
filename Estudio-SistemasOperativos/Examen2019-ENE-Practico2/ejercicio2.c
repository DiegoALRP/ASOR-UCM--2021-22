#include <stdio.h>
#include <string.h>
#include <errno.h>
//getaddrinfo
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//socket
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

int main(int argc, char *argv[]) {

	if (argc != 3) {
	
		printf("Introduce correctamente los parámetros\n");
		printf("Uso: %s <direccion> <puerto>\n");
		
		return -1;
	}
	
	struct addrinfo hints;
	struct addrinfo *result;
	
	struct sockaddr_storage peer_addr;
	socklen_t peer_addr_len;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Stream socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	if (getaddrinfo(argv[1], argv[2], &hints, &res) != 0) {
	
		printf("Error getaddringfo() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}



	return 0;
}