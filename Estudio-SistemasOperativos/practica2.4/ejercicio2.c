//printf
#include <stdio.h>
//strerror
#include <string.h>
//errno
#include <errno.h>
//pipe (fork, dup2, execve, sleep,..)
#include <unistd.h>

int main(int argc, char *argv[]) {

	/*printf("argv[0]: %s, argv[1]: %s, argv[2]: %s, argv[3]: %s, argv[4]: %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);

	if (argc != 5) {
	
		printf("Introduzca correctamente los parametros\n");
		printf("Uso: %s <comando1> <argumento1> | <comando2> <argumento2>\n", argv[0]);
		
		return -1;
	}*/

	//Crear tubería
	int pipefd_p_h[2];
	int pipefd_h_p[2];
	
	if (pipe(pipefd_p_h) == -1) {
	
		printf("Error pipefd_p_h pipe() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	if (pipe(pipefd_h_p) == -1) {
	
		printf("Error pipefd_h_p pipe() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	//Hacer fork()
	
	pid_t pid;
	pid = fork();
	
	if (pid == -1) {
	
		printf("Error fork() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	else if (pid == 0) { //Proceso Hijo, lee tubería
	
		printf("Hijo: %d (Padre: %d)\n", getpid(), getppid());
		
		close(pipefd_p_h[1]);
		close(pipefd_h_p[0]);
		
		int contador = 0;
		
		while (contador < 9) {
		
			//Lee tuberia
			char buf_lectura[100];
			int bytes_lectura = read(pipefd_p_h[0], &buf_lectura, 100);
		
			if (bytes_lectura == -1) {
		
				printf("Error Hijo readtuberia() %d: %s\n", errno, strerror(errno));
			
				return -1;
			}
			buf_lectura[bytes_lectura] = '\0';
		
			printf("Hijo, mensaje de Padre: %s\n", buf_lectura);
		
			sleep(1);
		
			char buf[1] = "l";
			int bytes_escritura = write(pipefd_h_p[1], &buf, strlen(buf));
		
			if (bytes_escritura == -1) {
		
				printf("Error Hijo writePadre() %d: %s\n", errno, strerror(errno));
			
				return -1;
			}
			
			contador++;
		}
		
		//Lee tuberia
		char buf_lectura[100];
		int bytes_lectura = read(pipefd_p_h[0], &buf_lectura, 100);
	
		if (bytes_lectura == -1) {
	
			printf("Error Hijo readtuberia() %d: %s\n", errno, strerror(errno));
		
			return -1;
		}
		buf_lectura[bytes_lectura] = '\0';
	
		printf("Hijo, mensaje de Padre: %s\n", buf_lectura);
	
		sleep(1);
	
		char buf[1] = "q";
		int bytes_escritura = write(pipefd_h_p[1], &buf, strlen(buf));
	
		if (bytes_escritura == -1) {
	
			printf("Error Hijo writePadre() %d: %s\n", errno, strerror(errno));
		
			return -1;
		}
		
		close(pipefd_p_h[0]);
		close(pipefd_h_p[1]);
	}
	else {	//Proceso Padre, escribe tubería
	
		printf("Padre: %d (Hijo: %d)\n", getpid(), pid);
		
		close(pipefd_p_h[0]);
		close(pipefd_h_p[1]);
		
		int fin = 1;
		
		while (fin == 1) {
		
			//Leer entrada estandar:
			//0: entrada estandar
		
			char buf[100];
			int bytes = read(0, &buf, 100);
		
			if (bytes == -1) {
		
				printf("Error Padre read() %d: %s\n", errno, strerror(errno));
			
				return -1;
			}
		
			printf("Padre ha leido stdin: %s\n", buf);
		
			//Escribe al hijo
			int bytes_escritura = write(pipefd_p_h[1], &buf, strlen(buf));
		
			if (bytes_escritura == -1) {
		
				printf("Error Padre write() %d: %s\n", errno, strerror(errno));
			
				return -1;
			}
		
			printf("Padre ha enviado a hijo\n");
		
			char buf_h[100];
			int bytes_readHijo = read(pipefd_h_p[0], &buf_h, 100);
		
			if (bytes_readHijo == -1) {
		
				printf("Error Padre read_hijo %d: %s\n", errno, strerror(errno));
			
				return -1;
			}
		
			buf_h[bytes_readHijo] = '\0';
		
			printf("Padre ha leido de hijo: %s\n", buf_h);
			
			if (buf_h[0] == 'q') {
			
				fin = 0;
				printf("Padre ha leido 'q'... Terminado\n");
			}
		}
		
		close(pipefd_p_h[1]);
		close(pipefd_h_p[0]);
		
	}

	return 0;
}