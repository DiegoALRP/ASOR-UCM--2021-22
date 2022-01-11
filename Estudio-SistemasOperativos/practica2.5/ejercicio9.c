#include <stdio.h>
#include <string.h>
#include <errno.h>
//getaddrinfo
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//socket, bind, recv, send, listen, accept
#include <sys/types.h>
#include <sys/socket.h>
//getnameinfo
#include <sys/socket.h>
#include <netdb.h>
//wait
#include <sys/types.h>
#include <sys/wait.h>
       
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
	hints.ai_socktype = SOCK_STREAM; // Stream socket
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
	
	if (listen(socketfd, 16) == -1) {
	
		printf("Error listen() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	/*struct sigaction sa;
	sa.sa_handler=SIG_IGN;
    sa.sa_flags = SA_RESTART;*/
	
	while (1) {
		
		struct sockaddr_storage client;
    	socklen_t client_len;
    	client_len = sizeof(struct sockaddr_storage);
    
    	int accfd = accept(socketfd, (struct sockaddr *) &client, &client_len);
    	
    	if (accfd == -1) {
    
			printf("Error accept() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
    	
    	pid_t pid;
    	pid = fork();
    	
    	if (pid == -1) {
    	
    		printf("Error fork() %d: %s\n", errno, strerror(errno));
    		
    		return -1;
    	}
    	else if (pid == 0) {
    	
    		printf("Hijo %d (Padre %d)\n", getpid(), getppid());
    		
    		char host[NI_MAXHOST];
			char serv[NI_MAXSERV];
		
			int nameInfo = getnameinfo((struct sockaddr *) &client, client_len,
				           host, NI_MAXHOST,
				           serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
				           
			if (nameInfo == -1) {
		
				printf("Error getnameinfo() %d: %s\n", errno, strerror(errno));
			
				return -1;
			}
		
			printf("Conexión desde Host: %s Puerto: %s\n", host, serv);
		
			char buf[80];
			int bytes;
			bytes = recv(accfd, buf, 80, 0);
		
			while (bytes > 0) {
		
				buf[bytes] = '\0';
			
				printf("Recibido: %s\n", buf);
			
				int bytes_send = send(accfd, buf, bytes, 0);
			
				if (bytes_send == -1) {
			
					printf("Error send() %d: %s\n", errno, strerror(errno));
				
					return -1;
				}
			
				bytes = recv(accfd, buf, 80, 0);
			}
		
			if (bytes == -1) {
		
				printf("Error revcfrom() %d: %s\n", errno, strerror(errno));
			
				return -1;
			}
		
			printf("Conexión terminada\n");
			close(accfd);
			
			return 0;
    	}
    	else {
    	
    		printf("Padre %d (Hijo %d)\n", getpid(), pid);
    	}
	}
	
	while(wait(NULL)>0);
	
	/*int status;
    pid_t pidTerminado = wait(&status);
    
    if (WIFEXITED(status)) {
    
   		printf("Terminado hijo %d\n", pidTerminado);
    }*/

	freeaddrinfo(result);
	close(socketfd);
	
	return 0;
	
}