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
       
int main(int argc, char *argv[]) {

	if (argc != 2) {
	
		printf("Introduzca correctamente los parámetros\n");
		printf("Uso: %s <host>\n");
		
		return -1;
	}

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
	
	int socketfd;

	if (getaddrinfo(argv[1], NULL, &hints, &result) == -1) {
	
		printf("Error getaddrinfo() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	struct addrinfo *rp;
	for (rp = result; rp != NULL; rp = rp->ai_next) {
	
		char host[NI_MAXHOST];
		char serv[NI_MAXSERV];
		
		int resNameInfo = getnameinfo(rp->ai_addr, rp->ai_addrlen,
                       host, NI_MAXHOST,
                       serv, NI_MAXSERV, 
                       NI_NUMERICHOST | NI_NUMERICSERV);
                       
        if (resNameInfo == -1) {
        
        	printf("Error getnameinfo() %d: %s\n", errno, strerror(errno));
        	
        	return -1;
        }
        
        printf("IP Númerica: %s\n", host);
        printf("Familia de protocolos: %d\n", rp->ai_family);
        printf("Tipo de socket: %d\n", rp->ai_socktype);
	}
	
	printf("Terminado!\n");
	return 0;
}