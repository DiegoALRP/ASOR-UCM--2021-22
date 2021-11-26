#include <stdio.h>
#include <errno.h>
#include <signal.h>

volatile int int_cont = 0;
volatile int tstp_cont = 0;

const int num_signals = 10;

int retract = 0;

void manejador (int signal) {

	if (signal == SIGUSR1) retract = 1;
}

int main(int argc, char **argv) {

	struct sigaction action;

	sigaction(SIGUSR1, NULL, &action);
	action.sa_handler = manejador;
	sigaction(SIGUSR1, &action, NULL);

	int segs = atoi(argv[1]);
	printf("WARNING! Se eliminará el ejecutable en %d segundos\n", segs);
	//sleep(segs);

	int cont = 0;
	while (cont < segs && !retract) {

		cont++;
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