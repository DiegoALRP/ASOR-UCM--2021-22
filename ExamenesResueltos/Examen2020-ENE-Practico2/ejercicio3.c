#include <stdio.h>
#include <string.h>
#include <errno.h>
//pipe, fork, dup2
#include <unistd.h>

int main(int argc, char *argv[]) {

	if (argc < 3) {
	
		printf("Introduce correctamente los parámetros\n");
		printf("Uso: %s <comando1> <comando2> <argumentos comando2> \n", argv[0]);
		
		return -1;
	}
	
	printf("argv[0]: %s, argv[1]: %s, argv[2]: %s, argv[3]: %s\n", argv[0], argv[1], argv[2], argv[3]);
	
	int tuberia[2];
	
	if (pipe(tuberia) == -1) {
	
		printf("Error pipe() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	pid_t pid;
	pid = fork();
	
	if (pid == -1) {
	
		printf("Error fork() %d: %s\n", errno, strerror(errno));
		
		return 0;
	}
	else if (pid == 0) {
	
		printf("Hijo %d (Padre %d)\n", getpid(), getppid());
		
		close(0);
		
		if (dup2(tuberia[0], 0) == -1) {
		
			printf("Error Hijo dup2() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		
		close(tuberia[0]);
		close(tuberia[1]);
		
		if (execvp(argv[2], &argv[2]) == -1) {
		
			printf("Error Hijo execvp() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		
	}
	else {
	
		printf("Padre %d (Hijo %d)\n", getpid(), pid);
		
		
		close(1);
		close(0);
		
		if (dup2(tuberia[1], 1) == -1) {
		
			printf("Error Padre dup2() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		
		close(tuberia[0]);
		close(tuberia[1]);
		
		if (execlp(argv[1], argv[1], 0) == -1) {
		
			printf("Error Padre execlp() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
	}
	

	return 0;
}