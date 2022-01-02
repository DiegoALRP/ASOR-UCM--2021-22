#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
//Para obtener variables de entorno
#include <stdlib.h>

int main() {

	sigset_t sint;
	sigset_t pend;
	
	sigemptyset(&sint);
	sigaddset(&sint, SIGINT);
	sigaddset(&sint, SIGTSTP);
	
	sigprocmask(SIG_BLOCK, &sint, 0);
	
	
	//Obtener variable de entorno SLEEP_SECS
	//Se crea la variable de entorno con export SLEEP_SECS=10
	char *var = getenv("SLEEP_SECS");
	int segs = atoi(var);
	
	printf("El proceso se va a dormir: %d segundos\n", segs);
	sleep(segs);
	printf("El proceso se ha despertado\n");
	
	sigpending(&pend);
	
	if (sigismember(&pend, SIGINT)) {
	
		printf("Se recibió la señal SIGINT\n");
		//sigprocmask(SIG_UNBLOCK, &sint, 0);
	}
	else {
	
		printf("No se recibió la señal SIGINT\n");
	}
	
	if (sigismember(&pend, SIGTSTP)) {
	
		printf("Se recibió la señal SIGTSTP\n");
		//sigprocmask(SIG_UNBLOCK, &sint, 0);
	}
	else {
	
		printf("No se recibió la señal SIGTSTP\n");
	}
	
	sigprocmask(SIG_UNBLOCK, &sint, 0);
	
	return 0;
}