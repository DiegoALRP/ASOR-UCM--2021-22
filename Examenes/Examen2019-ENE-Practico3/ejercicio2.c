#include <stdio.h>
#include <string.h>
#include <errno.h>
//sigismember, sigaddset
#include <signal.h>

volatile int n_sigint;
volatile int n_sigtstp;

void manejador(int signal) {

	if (signal == SIGINT) n_sigint++;
	if (signal == SIGTSTP) n_sigtstp++;
}

int main() {

	sigset_t sigset;
	
	struct sigaction action;
	
	action.sa_handler = manejador;
	action.sa_flags = SA_RESTART;
	
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGTSTP, &action, NULL);
	
	sigemptyset(&sigset);
	
	while (n_sigint + n_sigtstp < 10) {
	
		sigsuspend(&sigset);
	}

	if (sigismember(&sigset, SIGINT)) {
	
		printf("Se ha recibido la señañ SIGINT\n");
	}
	
	if (sigismember(&sigset, SIGTSTP)) {
	
		printf("Se ha recibido la señañ SIGINT\n");;
	}

	printf("\nSe ha recibido %d señales SIGINT\n", n_sigint);
	printf("Se ha recibido %d señales SIGTSTP\n", n_sigtstp);

	return 0;
}