#include <stdio.h>
#include <string.h>
#include <errno.h>
//getaddrinfo
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//socket, bind, recv, send
#include <sys/types.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {

	struct addrinfo hints;
	struct addrinfo *result;

	if (argc != 4) {
	
		printf("Introduce correctamente los parametros\n");
		printf("Uso: %s <direccion servidor> <puerto> <comando>\n", argv[0]);
		
		return -1;
	}

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
	hints.ai_flags = 0;
	hints.ai_protocol = 0;          /* Any protocol */

	if (getaddrinfo(argv[1], argv[2], &hints, &result) == -1) {
	
		printf("Error getaddrinfo() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}

	int socketfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	
	if (socketfd == -1) {
	
		printf("Error socket() %d: %s\n", errno, strerror(errno));
		
		close(socketfd);
		return -1;
	}

	if (connect(socketfd, result->ai_addr, result->ai_addrlen) == -1) {
	
		printf("Error connect() %d: %s\n", errno, strerror(errno));
		
		close(socketfd);
		return -1;
	}
	
	struct sockaddr_storage client;
	socklen_t client_len;
	client_len = sizeof(struct sockaddr_storage);
	
	char buf[50];
	strcpy(buf, argv[3]);
	//int bytes_sent = sendto(socketfd, buf, 50, 0,
    //              (struct sockaddr *) &client, client_len);
                 
    int bytes_sent = send(socketfd, buf, 50, 0);
                  
    if (bytes_sent == -1) {
    
    	printf("Error sendto() %d: %s\n", errno, strerror(errno));
    	
    	return -1;
    }
    
    char buf_rcv[50];
    int bytes_rcv = recv(socketfd, buf_rcv, 50, 0);
    
    if (bytes_rcv == -1) {
    
    	printf("Error revcfrom() %d: %s\n", errno, strerror(errno));
    	
    	return -1;
    }
	
	printf(buf_rcv);
	close(socketfd);
	
	freeaddrinfo(result);
}