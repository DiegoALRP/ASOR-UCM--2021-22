#include <stdio.h>
#include <string.h>
#include <errno.h>
//getaddrinfo
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

int main(int argc, char *argv[]) {

	if (argc != 3) {
	
		printf("Introduce correctamente los paramentros\n");
		printf("Uso: %s <dirección> <puerto>\n");
		
		return -1;
	}
	
	printf("argv[0]: %s, argv[1]: %s, argv[2]: %s\n", argv[0], argv[1], argv[2]);
	
	/*struct addrinfo hints;
	struct addrinfo *result;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	//hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	//hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	//hints.ai_protocol = 0;          /* Any protocol */
	/*hints.ai_canonname = NULL;
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
	
	freeaddrinfo(result);*/
	
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
	
	while(1) {
	
		struct sockaddr_storage client;
		socklen_t client_len = sizeof(struct sockaddr_storage);
		
		char buf_rd[100];
		int bytes_rd = recvfrom(socketfd, buf_rd, 100, 0, (struct sockaddr *) &client, &client_len);
		
		if (bytes_rd == -1) {
		
			printf("Error recvfrom() %d: %s\n", errno, strerror(errno));
		}
		
		char host[NI_MAXHOST];
		char serv[NI_MAXSERV];

		int nameInfo = getnameinfo((struct sockaddr *) &client, client_len,
						host, NI_MAXHOST,
						serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
						
		if (nameInfo == -1) {
		
			printf("Error getnameinfo() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		
		printf("Conexión desde Host: %s, Puerto: %s\n", host, serv);
		
		int bytes_sd = sendto(socketfd, host, strlen(host), 0, (struct sockaddr *) &client, client_len);
		
		if (bytes_sd == -1) {
		
			printf("Error sendto() %d: %s\n", errno, strerror(errno));
		}
	}
	
	close(socketfd);
	
	return 0;
}