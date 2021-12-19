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
//Listen & bind
#include <sys/types.h>
#include <sys/socket.h>

#define NPROC 2


int main(int argc, char** argv) {

	if (argc != 3) {

		printf("Introduce los parámetros necesarios: %s <dirección> <puerto>\n", argv[0]);
		return -1;
	}
	
	/*
	* Estructura del Patrón accept-and-fork
	* 
	* sd = socket()
	* bind(sd, ...)
	* listen()
	* accept(sd, ...)
	*
	* crear thread/proceso
	*
	*	//tratar conexion
	*	recv/send
	*
	*		//iniciar conex.
	*		connect(sd...)
	*		send/recv
	*
	* //Thread ppal. ciclo
	* //de vida del servidor
	*
	*/
	
	printf("argv[1]: %s\nargv[2]: %s\n", argv[1], argv[2]);
	
	//Gestión de Direcciones
	struct addrinfo hints;
	struct addrinfo *resultInfo;

	//Copiado del man
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
	
		fprintf(stderr, "Error getaddrinfo(): %s \n", gai_strerror(rc));
		return -1;
	}
	
	int socketTCP = socket(resultInfo->ai_family, resultInfo->ai_socktype, 0);
	
	if (socketTCP == -1) {
	
		fprintf(stderr, "Error socket()\n");
		return -1;
	}
	
	int b = bind(socketTCP, (struct sockaddr *) resultInfo->ai_addr, resultInfo->ai_addrlen);
	
	if (b == -1) {
	
		fprintf(stderr, "Error bind()\n");
		return -1;
	}
	
	//El segundo parámetro tiene que ser potencia de 2, y como mínimo 16
	int l = listen(socketTCP, 16);
	
	if (l == -1) {
	
		fprintf(stderr, "Error listen()\n");
		return -1;
	}
	
	pid_t pid;
	int count = 0;
	while (1) {
		
		printf("Vuelta %d\n", count);
		
		struct sockaddr_storage addr;
		socklen_t addrlen = sizeof(addr);
		
		int acc = accept(socketTCP, (struct sockaddr *) &addr, &addrlen);
		
		if (acc == -1) {
		
			fprintf(stderr, "Error accept()\n");
			return -1;
		}
		
		pid = fork();
		
		printf("Haciendo fork() #%d\n", count);
		count++;
		
		if (pid == -1) {
		
			fprintf(stderr, "Error fork()\n");
			return -1;
		}
		else if (pid == 0) { //Proceso Hijo
		
			printf("Proceso Hijo\n");
			
			char host[NI_MAXHOST];
			char serv[NI_MAXSERV];
			
			int nameInfo = getnameinfo((struct sockaddr *) &addr, addrlen,
									host, NI_MAXHOST,
									serv, NI_MAXSERV,
									NI_NUMERICHOST|NI_NUMERICSERV);
								
			if (nameInfo == -1) {
	
				fprintf(stderr, "Error getnammeinfo()\n");
			}
	
			printf("Conexión desde Host: %s Puerto: %s\n", host, serv);
			
			//Comprobar mensaje!!
			char buf[80];
			ssize_t bytes;
			
			//OJO: el recv se hace con el socket del accept, no el socket del socket()
			while (bytes = recv(acc, buf, 80, 0)) {
			
				if (bytes == -1) {
		
					fprintf(stderr, "Error recv()\n");
				}
		
				buf[bytes] = '\0';
				printf("\tMensaje: %s\n", buf);
				send(acc, buf, bytes, 0);
			}
			
			printf("Hijo: 'Conexión Terminada'\n");
			close(acc);
			
			return 0;
		}
		else {	//Proceso Padre
		
			printf("Proceso Padre\n");
			
			close(acc);
			//close(socketTCP);
		}
	}
	
	return 0;
}