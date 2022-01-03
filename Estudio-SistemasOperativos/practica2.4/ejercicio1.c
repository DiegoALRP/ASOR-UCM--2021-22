//printf
#include <stdio.h>
//strerror
#include <string.h>
//errno
#include <errno.h>
//pipe (fork, dup2, execve,..)
#include <unistd.h>

int main(int argc, char *argv[]) {

	printf("argv[0]: %s, argv[1]: %s, argv[2]: %s, argv[3]: %s, argv[4]: %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);

	if (argc != 5) {
	
		printf("Introduzca correctamente los parametros\n");
		printf("Uso: %s <comando1> <argumento1> | <comando2> <argumento2>\n", argv[0]);
		
		return -1;
	}

	//Crear tubería
	int pipefd[2];
	
	if (pipe(pipefd) == -1) {
	
		printf("Error pipe() %d: %s\n", errno, strerror(errno));
		
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
		
		close(0);
		int du = dup2(pipefd[0], 0);
		
		if (du == -1) {
		
			printf("Error Hijo dup2() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		
		//close(0);
		//close(1);
		close(pipefd[0]);
		close(pipefd[1]);
		
		int exe = execlp(argv[3], argv[3], argv[4], 0);
		
		if (exe == -1) {
		
			printf("Error Hijo execvp() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
	}
	else {	//Proceso Padre, escribe tubería
	
		printf("Padre: %d (Hijo: %d)\n", getpid(), pid);
		
		close (1);
		int du = dup2(pipefd[1], 1);
		
		if (du == -1) {
		
			printf("Error Padre dup2() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		
		//close(0);
		//close(1);
		close(pipefd[0]);
		close(pipefd[1]);
		
		int exe = execlp(argv[1], argv[1], argv[2], 0);
		
		if (exe == -1) {
		
			printf("Error Padre execvp() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
	}

	return 0;
}