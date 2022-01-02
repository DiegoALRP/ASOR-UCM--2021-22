#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

volatile int_count = 0;
volatile tstp_count = 0;

void manejador(int signal) {

	if (signal == SIGINT) int_count++;
	if (signal == SIGTSTP) tstp_count++;
}

int main() {

	struct sigaction action;
	
	action.sa_handler = manejador;
	action.sa_flags = SA_RESTART;
	
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGTSTP, &action, NULL);
	
	sigset_t set;
	sigemptyset(&set);
	
	while (int_count + tstp_count < 10) {
	
		sigsuspend(&set);
	}

	printf("\nNúmero SIGINT: %d\n", int_count);
	printf("Número SIGTSTP: %d\n", tstp_count);

	return 0;
}