#include <stdio.h>
#include <string.h>
#include <errno.h>
//sigaction
#include <signal.h>
//atoi
#include <stdlib.h>
//alarm
#include <unistd.h>

//Esta es una version mejorada del ejercicio13

volatile int retract = 0;

void manejador(int signal) {

	if (signal == SIGUSR1) retract = 1;
}

int main(int argc, char *argv[]) {

	if (argc != 2) {
	
		printf("Introduce correctamente los parámetros\n");
		printf("Uso: %s <segundos>\n", argv[0]);
		
		return -1;
	}
	
	int seconds = atoi(argv[1]);
	
	printf("Segundos introducidos %d\n", seconds);
	
	struct sigaction action;
	
	action.sa_handler = manejador;
	//action.sa_flags = SA_RESTART;
	
	int a = sigaction(SIGUSR1, &action, NULL);
	int b = sigaction(SIGALRM, &action, NULL);
	
	alarm(seconds);
	
	sigemptyset(&action.sa_mask);
	
	sigsuspend(&action.sa_mask);
	
	if (retract) {
	
		printf("Has suspendido con éxito el borrado del fichero!!! :)\n");
	}
	else {
	
		printf("Lo lamento :( se ha borrado el fichero\n");
	}
	
	return 0;
}