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
		
		switch (pid) {
		
			case -1:
				
				perror("Error fork()");
				return -1;
			break;
			//Hijo
			case 0: ;
			
				while (1) {

					char buf[80];
					char host[NI_MAXHOST];
					char serv[NI_MAXSERV];
					
					struct sockaddr_storage client_addr;
					socklen_t client_addrlen = sizeof(struct sockaddr_storage);
		
					ssize_t bytes = recvfrom(socketUDP, buf, 80, 0, (struct sockaddr *) &client_addr, &client_addrlen);

					/*if (bytes == -1) {

						perror("Error recieve from\n");
						return -1;
					}*/
					
					printf("buff: %s\n", buf);

					buf[bytes] = '\0';
			
					nameInfo = getnameinfo((struct sockaddr *) &client_addr,
									client_addrlen, host, NI_MAXHOST,
									serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
							
					if (nameInfo == -1) {

						perror("Error getnameinfo\n");
						return -1;
					}
			
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
			
					return 0;
				}
			break;
			//Padre
			default:
			
				while(wait(NULL)>0);
				//wait(0);
				close(socketUDP);
				
				break;
		}
	}
	
	/*
	
	//Tuberia
	fd_set rfds;
	struct timeval timeout; //Tiempo máximo en el que retornará la función
	int resSelect;

	while (1) {

		FD_ZERO(&rfds); //Inicializa un conjunto como un conjunto vacío
		FD_SET(0, &rfds); // 0: standard input
		FD_SET(socketUDP, &rfds); //También agregamos la entrada del socket

		//Timeval
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;

		//Sacado de teoría: el primer argumento es el número del fd + 1
		resSelect = select(socketUDP + 1, &rfds, NULL, NULL, &timeout);

		char buf[50];

		if (resSelect == -1) {

			perror("Error select()\n");
		}
		else if (resSelect) {

			//File Descriptor: 0 (entrada estandar)
			if (FD_ISSET(0, &rfds)) { //FD_ISSET comprueba si un descriptor está en un conjunto

				int bytes = read(0, &buf, 50);
				
				if (bytes == -1) {

					perror("FD 0, Error en read()\n");
					return -1;
				}
				else if (bytes > 2) {

					buf[bytes-1] = '\0';
					printf("Comando '%s' NO reconocido. Usar 't', 'd' o 'q'\n", buf);
				}

				buf[bytes] = '\0';	//Recordar siempre esto, para evitar problemas

				time_t tiempo = time(NULL);
				struct tm *tm = localtime(&tiempo);

				if (tm == NULL) {

					perror("FD 0, Error en localtime\n");
					return -1;
				}

				char imprimir[50];

				//Lectura del comando t
				//if (buf == 't') {
				if (strcmp(buf, "t\n") == 0 ) {

					strftime(imprimir, 50, "%H:%M:%S", tm);
					printf("La hora actual es: %s\n", imprimir);
				}
				//Lectura del comando d
				else if (strcmp(buf, "d\n") == 0 ) {

					strftime(imprimir, 50, "%y-%m-%d", tm);
					printf("La fecha actual es: %s\n", imprimir);
				}
				//Lectura del comando q
				else if (strcmp(buf, "q\n") == 0 ) {

					printf("Saliendo...\n");

					close(socketUDP);
					return 0;
				}
				else {

					buf[bytes-1] = '\0';
					printf("Comando '%s' NO reconocido. Usar 't', 'd' o 'q'\n", buf);
				}
			}
			//File Descriptor Socket UDP
			else if (FD_ISSET(socketUDP, &rfds)) {

				ssize_t bytes = recvfrom(socketUDP, buf, 2, 0, (struct sockaddr *) &cliente_addr,
									&cliente_addrlen);
		
				if (bytes == -1) {

					printf("Error recieve from\n");
					return -1;
				}

				buf[bytes] = '\0';

				nameInfo = getnameinfo((struct sockaddr *) &cliente_addr,
							cliente_addrlen, host, NI_MAXHOST,
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
							(struct sockaddr *) &cliente_addr, cliente_addrlen);
				}
				else if (buf[0] == 'd') {

					ssize_t bytesFecha = strftime(stringTiempo, max, "%y-%m-%d \n", tm);

					sendto(socketUDP, stringTiempo, bytesFecha, 0, 
							(struct sockaddr *) &cliente_addr, cliente_addrlen);
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
		}
		else {

			printf("Ningún dato nuevo en 5 seg.\n");
		}
	}*/

	return 0;
}







