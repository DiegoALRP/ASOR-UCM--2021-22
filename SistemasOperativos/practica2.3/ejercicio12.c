#include <stdio.h>
#include <errno.h>
#include <signal.h>

volatile int int_cont = 0;
volatile int tstp_cont = 0;

const int num_signals = 10;

void manejador (int signal) {

	if (signal == SIGINT) int_cont++;
	if (signal == SIGTSTP) tstp_cont++;
}

int main(int argc, char **argv) {

	struct sigaction action;

	sigaction(SIGINT, NULL, &action);
	action.sa_handler = manejador;
	sigaction(SIGINT, &action, NULL);

	sigaction(SIGTSTP, NULL, &action);
	action.sa_handler = manejador;
	sigaction(SIGTSTP, &action, NULL);

	sigset_t sint;

	while (int_cont + tstp_cont < num_signals) {

		sigsuspend(&sint);
	}

	printf("\nSeñales SIGINT capturadas: %d\n", int_cont);
	printf("Señales SIGTSTP capturadas: %d\n", tstp_cont);

	return 0;
}