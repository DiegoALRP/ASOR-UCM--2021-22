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
	
		printf("Introduce correctamente los parámetros\n");
		printf("Uso: %s <dirección> <puerto>\n", argv[0]);
		
		return -1;
	}
	
	printf("argv[0]: %s, argv[1]: %s, argv[2]: %s\n", argv[0], argv[1], argv[2]);
	
	struct addrinfo hints;
	struct addrinfo *result, *rp;

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
	
	int socketfd;
	
	for (rp = result; rp != NULL; rp = rp->ai_next) {
	
		socketfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		
		if (socketfd == -1)
			continue;

		if (bind(socketfd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;                  /* Success */

		close(socketfd);
	}
	
	if (listen(socketfd, 16) == -1) {
	
		printf("Error listen() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	freeaddrinfo(result);
	
	while (1) {
	
		struct sockaddr_storage client;
		socklen_t client_len = sizeof(&client);
		
		int accfd = accept(socketfd, (struct sockaddr *) &client, &client_len);
		
		if (accfd == -1) {
		
			printf("Error accept() %d: %s\n", errno, strerror(errno));
			
			close(accfd);
			return -1;
		}
		
		char host[NI_MAXHOST];
		char serv[NI_MAXSERV];

        int nameInfo = getnameinfo((struct sockaddr *) &client, client_len,
        						host, NI_MAXHOST,
        						serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
        						
       	if (nameInfo == -1) {
       	
       		printf("Error getnameinfo() %d: %s\n", errno, strerror(errno));
       		
       		close(accfd);
       		return -1;
       	}
       	
       	printf("Conexión desde Host: %s, Puerto: %s\n", host, serv);
       	
       	char buf_rd[80];
       	int bytes_rd;
       	
       	while (bytes_rd = recv(accfd, buf_rd, 80, 0)) {
       	
		   	if (bytes_rd == -1) {
		   	
		   		printf("Error recv() %d: %s\n", errno, strerror(errno));
		   		
		   		close(accfd);
		   		return -1;
		   	}
		   	
		   	int bytes_sd = send(accfd, host, strlen(host), 0);
		   	
		   	if (bytes_sd == -1) {
		   	
		   		printf("Error send() %d: %s\n", errno, strerror(errno));
		   		
		   		close(accfd);
		   		return -1;
		   	}
		}
		
		close(accfd);
	}
	
	return 0;
}


