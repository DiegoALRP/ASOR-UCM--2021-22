#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {

	sigset_t sint;
	sigset_t pend;

	sigemptyset(&sint);
	sigaddset(&sint, SIGINT);
	sigaddset(&sint, SIGTSTP);
	
	sigprocmask(SIG_BLOCK, &sint, 0);

	//Obtener variable de entorno SLEEP_SECS
	char *sleep_secs;
	size_t size = 10;
	sleep_secs = malloc(size);
	getenv("SLEEP_SECS");

  	int secs = atoi(sleep_secs);
	printf("El proceso se dormirá durante %d segundos.\n", sleep_secs);
	sleep(secs);


	sigpending(&pend);

	if (sigismember(&pend, SIGINT)) {

		printf("Señal SIGINT recibida");
		sigprocmask(SIG_BLOCK, &sint, 0);
		sigdelset(&sint, SIGINT);
	}
	if (sigismember(&pend, SIGTSTP)) {

		printf("Señal SIGTSTP recibida");
		sigprocmask(SIG_BLOCK, &sint, 0);
		sigdelset(&sint, SIGTSTP);
	}

	return 0;
}