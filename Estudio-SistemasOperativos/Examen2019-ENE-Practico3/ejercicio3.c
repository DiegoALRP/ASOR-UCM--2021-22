#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//socket
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
//fork
#include <unistd.h>
//wait
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {

	if (argc != 3) {
	
		printf("Introduce correctamente los parámetros\n");
		printf("Uso: %s <dirección> <puerto>\n");
		
		return -1;
	}
	
	struct addrinfo hints;
	struct addrinfo *result;

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
	
	while (1) {
	
		struct sockaddr_storage client;
		socklen_t client_len = sizeof(struct sockaddr_storage);
		
		int accfd = accept(socketfd, (struct sockaddr *) &client, &client_len);
		
		pid_t pid;
		pid = fork();
		
		if (pid == -1) {
		
			printf("Error forf() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		else if (pid == 0) {
		
			printf("Hijo %d (Padre %d)\n", getpid(), getppid());
			
			char buf_rd[80];
			int bytes_rd;
			while (bytes_rd = recv(accfd, buf_rd, 80, 0)) {
			
				printf("Le atiende el proceso: %d\n", getpid());
				
				char host[NI_MAXHOST];
				char serv[NI_MAXSERV];
				
				int nameInfo = getnameinfo((struct sockaddr *) &client, client_len,
                       host, NI_MAXHOST,
                       serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
                       
                printf("Conexión desde Host: %s, Puerto: %s\n", host, serv);
				
				if (bytes_rd == -1) {
				
					printf("Error recv() %d: %s\n", errno, strerror(errno));
					
					return -1;
				}
				
				buf_rd[bytes_rd] = '\0';
				printf("El servidor ha leido: %s", buf_rd);
				
				int bytes_sd = send(accfd, buf_rd, bytes_rd, 0);
				
				if (bytes_sd == -1) {
				
					printf("Error send() %d: %s\n", errno, strerror(errno));
					
					return -1;
				}
			}
			
			close(accfd);
			return 0;
		}
		else {
		
			printf("Padre %d (Hijo %d)\n", getpid(), pid);
		}
	}


	while(wait(NULL)>0);

	return 0;
}