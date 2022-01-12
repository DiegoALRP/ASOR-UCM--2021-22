#include <stdio.h>
#include <string.h>
#include <errno.h>
//fork, getpid, getppid, pipe, dup, dup2, execvp
#include <unistd.h>

int main(int argc, char *argv[]) {

	printf("argv[0]: %s, argv[1]: %s, argv[2]: %s, argv[3]: %s, argv[4]: %s\n", argv[0], argv[1], argv[2], argv[3], argv[4]);

	if (argc < 3) {
	
		printf("Introduzca correctamente los parametros\n");
		printf("Uso: %s <comando1> <comando2> <argumentos comando 2>\n");
		
		return -1;
	}
	
	//Crear tuberia sin nombre
	int pipefds[2];
	
	if (pipe(pipefds) == -1) {
	
		printf("Error pipe() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	pid_t pid;
	pid = fork();
	
	if (pid == -1) {
	
		printf("Error fork() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	else if (pid == 0) {
	
		//Usaremos el hijo para la salida
		printf("Hijo %d (Padre %d)\n", getpid(), getppid());
		
		//Cerrar descriptores sin usar
		close(0); //Cerramos por seguridad la entrada estandar
		
		if (dup2(pipefds[0], 0) == -1) {
		
			printf("Error Hijo dup2() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		
		close(pipefds[0]);	//Se cierra porque ya se ha utilizado y no nos hace falta
        close(pipefds [1]);	//Se cierra porque no se va a utilizar la salida estandar
		
		if (execvp(argv[2], &argv[2]) == -1) { //execvp para cuando no conocemos el número de argumentos que tiene
		
			printf("Error Hijo execvp() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
	}
	else {
	
		//Usaremos el padre para la entrada
		printf("Padre %d (Hijo %d)\n", getpid(), pid);
		
		//Cerrar descriptores sin usar
		
		close(1);	//Cerramos por seguridad la salida estandar
		
		if (dup2(pipefds[1], 1) == -1) {
		
			printf("Error Padre dup2() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		
		close(pipefds[0]); 	//Se cierra porque no se va a utilizar la entrada estandar
        close(pipefds[1]);	//Se cierra porque ya se ha utilizado y no nos hace falta
		
 		if (execlp(argv[1], argv[1], 0) == -1) { //Execlp para cuando conocemos el número de argumentos que tiene
		
			printf("Error Padre execvp() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
	}
	
	return 0;
}