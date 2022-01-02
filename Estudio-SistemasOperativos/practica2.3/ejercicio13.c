#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

volatile int retract = 0;

void manejador(int signal) {

	if (signal == SIGUSR1) retract = 1;
}

int main(int argc, char *argv[]) {

	printf("argv[0]: %s, argv[1]: %s\n", argv[0], argv[1]);
	
	if (argc < 2) {
	
		printf("Introduce los parametros necesarios\n");
		printf("Uso: %s <segundos>\n", argv[0]);
		
		return -1;
	}

	int segs = atoi(argv[1]);

	struct sigaction action;
	
	action.sa_handler = manejador;
	action.sa_flags = SA_RESTART;
	
	sigaction(SIGUSR1, &action, NULL);
	
	sigset_t set;
	sigemptyset(&set);
	
	int contador = 0;
	printf("WARNING! Se eliminará el ejecutable en %d segundos\n", segs);
	
	while (contador < segs && !retract) {
	
		contador++;
		sleep(1);
	}
	
	if (!retract) {
	
		printf("WARNING! El ejecutable '%s' se ha eliminado.\n", argv[0]);
	}
	else {
	
		printf("Te has retractado a tiempo! El ejecutable '%s' no se ha eliminado\n", argv[0]);
	}

	return 0;
}#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

volatile int retract = 0;

void manejador(int signal) {

	if (signal == SIGUSR1) retract = 1;
}

int main(int argc, char *argv[]) {

	printf("argv[0]: %s, argv[1]: %s\n", argv[0], argv[1]);
	
	if (argc < 2) {
	
		printf("Introduce los parametros necesarios\n");
		printf("Uso: %s <segundos>\n", argv[0]);
		
		return -1;
	}

	int segs = atoi(argv[1]);

	struct sigaction action;
	
	action.sa_handler = manejador;
	action.sa_flags = SA_RESTART;
	
	sigaction(SIGUSR1, &action, NULL);
	
	sigset_t set;
	sigemptyset(&set);
	
	int contador = 0;
	printf("WARNING! Se eliminará el ejecutable en %d segundos\n", segs);
	
	while (contador < segs && !retract) {
	
		contador++;
		sleep(1);
	}
	
	if (!retract) {
	
		printf("WARNING! El ejecutable '%s' se ha eliminado.\n", argv[0]);
	}
	else {
	
		printf("Te has retractado a tiempo! El ejecutable '%s' no se ha eliminado\n", argv[0]);
	}

	return 0;
}