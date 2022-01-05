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
//time
#include <time.h>
//pid
#include <sys/types.h>
#include <unistd.h>
//wait
#include <sys/types.h>
#include <sys/wait.h>

#define N 4
int main(int argc, char *argv[]) {

	if (argc != 3) {
	
		printf("Introduzca correctamente los parámetros\n");
		printf("Uso: %s <direccion> <puerto>\n");
		
		return -1;
	}
	
	printf("argc[0]: %s, argv[1]: %s, argv[2]: %s\n", argv[0], argv[1], argv[2]);

	struct addrinfo hints;
	struct addrinfo *result;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    // Allow IPv4 or IPv6
	hints.ai_socktype = SOCK_DGRAM; // Datagram socket
	hints.ai_flags = AI_PASSIVE;    // For wildcard IP address
	hints.ai_protocol = 0;          // Any protocol
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
		
		return -1;
	}
	
	freeaddrinfo(result);
	
	int n = 4;
	while (1) {
		int i;
		for (i = 0; i < n; i++) {
	
			pid_t pid;
			pid = fork();
		
			if (pid == -1) {
		
				printf("Error fork() %d: %s\n", errno, strerror(errno));
			
				return -1;
			}
			else if (pid == 0) {
		
				printf("Hijo %d (Padre %d)\n", getpid(), getppid());
			
				while (1) {
					struct sockaddr_storage client;
					socklen_t client_len;
					client_len = sizeof(struct sockaddr_storage);
				
					char buf[50];
					int bytes = recvfrom(socketfd, buf, 50, 0, (struct sockaddr *) &client, &client_len);
				
					if (bytes == -1) {
				
						printf("Error revcfrom() %d: %s\n", errno, strerror(errno));
					
						return -1;
					}
				
					printf("Servidor ha recibido: %s\n", buf);
				
					time_t tiempo;
					time(&tiempo);
				
					struct tm tiempoLocal = *localtime(&tiempo);
				
					char buf_send[50];
				
					if (buf[0] == 't') { //hora
				
						strftime(buf_send, 50, "%H:%M:%S\n", &tiempoLocal);
					}
					else if (buf[0] == 'd') { //fecha
				
						strftime(buf_send, 50, "%Y-%m-%d\n", &tiempoLocal);
					}
					else if (buf[0] == 'q') { //salir
				
						printf("Saliendo...\n");
					
						char buf_q[50];
						strcpy(buf_q, "Terminado conexion\n");
						int bytes_sent = sendto(socketfd, buf_q, 50, 0,
						          (struct sockaddr *) &client, client_len);
						          
						if (bytes_sent == -1) {
				
							printf("Error sendto() %d: %s\n", errno, strerror(errno));
					
							return -1;
						}
					
						//close(socketfd);
					
						return 0;
					}
					else { //decirle que introduzca bien
				
						buf[bytes-1]='\0';  //Para eliminar el salto de linea que envia el cliente
						printf("Comando %s no soportado \n", buf);
			
						char buf_q[500];
						strcpy(buf_q, "Comando ");
						strcat(buf_q, buf);
						strcat(buf_q, " no soportado \n");
						int bytes_sent = sendto(socketfd, buf_q, 50, 0,
						          (struct sockaddr *) &client, client_len);
						          
						if (bytes_sent == -1) {
				
							printf("Error sendto() %d: %s\n", errno, strerror(errno));
					
							return -1;
						}
			
						continue;
					}
				
				
					int bytes_sent = sendto(socketfd, buf_send, 50, 0,
						          (struct sockaddr *) &client, client_len);
						          
					if (bytes_sent == -1) {
				
						printf("Error sendto() %d: %s\n", errno, strerror(errno));
					
						return -1;
					}
				}
			}
			else {
		
				printf("Padre %d (Hijo %d)\n", getpid(), pid);
			}
		}
		
		int status;
		pid_t pidTerminado = wait(&status);
		n = 1;
		
		if (WIFEXITED(status)) {
			printf("Ha terminado el hijo %d\n", pidTerminado);
		}
	}
	
	

	return 0;
	
}