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


int main(int argc, char** argv) {

	if (argc != 4) {

		printf("Introduce los parámetros necesarios: %s <dirección> <puerto> <comando>\n", 
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

		printf("getaddrinfo: %s \n", gai_strerror(rc));
		return -1;
	}

	int socketUDP = socket(resultInfo->ai_family, resultInfo->ai_socktype, 0);

	if (socketUDP == -1) {

		printf("Error socket UDP\n");
		return -1;
	}

	
	rc = connect(socketUDP, resultInfo->ai_addr, resultInfo->ai_addrlen);

	if (rc == -1) {

		printf("Error connect()\n");
		return -1;
	}

	char cmd[2];
	cmd[0] = argv[3][0]; // argv[3][0] significa obtener el primer caracter del 3er string
	cmd[1] = '\0';

	rc = sendto(socketUDP, cmd, 2, 0, resultInfo->ai_addr, resultInfo->ai_addrlen);

	if (rc == -1) {

		printf("Error sendto()\n");
		return -1;
	}

	char buf[50];
	struct sockaddr_storage addr;
	socklen_t addr_len = sizeof(addr);
	
	int bytes = recvfrom(socketUDP, buf, 50, 0, (struct sockaddr *) &addr, &addr_len);
	buf[bytes] = '\0';

	printf("Recibido: %s\n", buf);

	freeaddrinfo(resultInfo);

	return 0;
}









