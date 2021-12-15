#include <stdio.h>
#include <stdlib.h>
//Gestión de Direcciones (getaddrinfo)
//Socket
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//memset
#include <string.h>
//time
#include <time.h>
//read
#include <unistd.h>


int main(int argc, char** argv) {

	if (argc != 3) {

		printf("Introduce los parámetros necesarios: %s <dirección> <puerto>\n", 
					argv[0]);
		return -1;
	}

	printf("argv[1]: %s\nargv[2]: %s\n", argv[1], argv[2]);
	
	//Gestión de Direcciones
	struct addrinfo hints;
	struct addrinfo *resultInfo;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;

	int rc = getaddrinfo(
					argv[1],
					argv[2],
					&hints,
					&resultInfo);

	if (rc != 0) {

		fprintf(stderr, "getaddrinfo: %s \n", gai_strerror(rc));
		return -1;
	}

	int socketTCP = socket(resultInfo->ai_family, resultInfo->ai_socktype, 0);

	if (socketTCP == -1) {

		fprintf(stderr, "Error socket()\n");
		return -1;
	}

	
	rc = connect(socketTCP, resultInfo->ai_addr, resultInfo->ai_addrlen);

	if (rc == -1) {

		fprintf(stderr, "Error connect()\n");
		return -1;
	}

	freeaddrinfo(resultInfo);
	
	char buf[80];
	memset(buf,0,sizeof(buf));

	while (1) {

		ssize_t bytes = read(0, buf, 80);
		if (bytes == -1) {
		
			fprintf(stderr, "Error read()\n");
			return -1;
		}
		
		buf[bytes] = '\0';
		
		if (strcmp(buf, "Q\n") == 0) {
			
			printf("Saliendo...\n");
			break;
		}
		
		rc = send(socketTCP, buf, bytes, 0);
		if (rc == -1) {
		
			fprintf(stderr, "Error send()\n");
			return -1;
		}
		
		bytes = recv(socketTCP, buf, 80, 0);
		if (bytes == -1) {
		
			fprintf(stderr, "Error recv()\n");
			return -1;
		}
		
		buf[bytes] = '\0';
		printf("%s", buf);
	}	

	//freeaddrinfo(resultInfo);
	close(socketTCP);

	return 0;
}