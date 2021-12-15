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
//Select
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

#define N 2

int main(int argc, char** argv) {

	if (argc != 3) {

		printf("Introduce los parámetros necesarios: %s <dirección> <puerto>\n", argv[0]);
		return -1;
	}

	printf("argv[1]: %s\nargv[2]: %s\n", argv[1], argv[2]);
	
	//Gestión de Direcciones
	struct addrinfo hints;
	struct addrinfo *resultInfo;

	memset(&hints, 0, sizeof(struct addrinfo));

	//ai.family tipo de familia de la dirección (IPv4 o IPv6)
	hints.ai_family = AF_UNSPEC;
	//ai.socktype especifica el tipo de socket a buscar.
	hints.ai_socktype = SOCK_DGRAM;
	//Especifica el protocolo de los sockets a retornar.
	/*hints.ai_protocol = 0;
	//Esta especifica opciones adicionales.
	// AI_PASSIVE indica que los sockets retornados podrán ser usados para bind(ing), que podrán aceptar conexiones.
	hints.ai_flags = AI_PASSIVE;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;*/

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

	int b = bind(socketUDP, (struct sockaddr *) resultInfo->ai_addr, resultInfo->ai_addrlen);

	if (b == -1) {

		printf("Error bind\n");
		return -1;
	}

	freeaddrinfo(resultInfo);
	
	//time_t tiempo = time(NULL);
	//struct tm *tm = localtime(&tiempo);
	//size_t max = 50;
	//char stringTiempo[max];

	int nameInfo;
	
	int i;
	for (i = 0; i < N; i++) {
	
		pid_t pid;
		pid = fork();
		
		if (pid == -1) {
			perror("Error fork()");
			return -1;
		}
		else if (pid == 0) {
		
			printf("hijo\n");
			
			while (1) {
				
				char buf[80];
				char host[NI_MAXHOST];
				char serv[NI_MAXSERV];
			
				struct sockaddr_storage client_addr;
				socklen_t client_addrlen = sizeof(struct sockaddr_storage);

				ssize_t bytes = recvfrom(socketUDP, buf, 80, 0, (struct sockaddr *) &client_addr, &client_addrlen);

				if (bytes == -1) {

					perror("Error recieve from\n");
					return -1;
				}

			
				printf("buff: %s", buf);

				buf[bytes] = '\0';
				
				nameInfo = getnameinfo((struct sockaddr *) &client_addr,
					client_addrlen, host, NI_MAXHOST,
					serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

				if (nameInfo == -1) {

					printf("Error getnameinfo\n");
					return -1;
				}

				printf("Se han recibido %d bytes de host: %s, serv: %s\n", bytes, host, serv);


				time_t tiempo = time(NULL);
				struct tm *tm = localtime(&tiempo);
				size_t max = 50;
				char stringTiempo[max];

				if (buf[0] == 't') {

					ssize_t bytesHora = strftime(stringTiempo, max, "%H:%M:%S \n", tm);

					stringTiempo[bytesHora] = '\0';

					sendto(socketUDP, stringTiempo, bytesHora, 0, 
							(struct sockaddr *) &client_addr, client_addrlen);
				}
				else if (buf[0] == 'd') {

					ssize_t bytesFecha = strftime(stringTiempo, max, "%y-%m-%d \n", tm);

					sendto(socketUDP, stringTiempo, bytesFecha, 0, 
							(struct sockaddr *) &client_addr, client_addrlen);
				}
				else if (buf[0] == 'q') {

					printf("Saliendo... \n");

					close(socketUDP);

					return 0;
				}
				else {

					buf[bytes-1]='\0'; //Para eliminar el salto de linea que envia el cliente
					printf("Comando %s no soportado \n", buf);
				}
			}
			break;
		}
		else {
		
			printf("Padre\n");
			
			while(wait(NULL)>0);
			break;
		}
	}

	close(socketUDP);
	return 0;
}







