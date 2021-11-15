#include <stdio.h>
#include <errno.h>
#include <sched.h>
#include <unistd.h>

int main(int argc, char **argv) {

	pid_t pid = getpid();

	printf("pid: %d\n", pid);

	//Obtener la politica de planificacion
	int polit = sched_getscheduler(pid);

	// 0: SCHED_OTHER
	// 1: SCHED_FIFO
	// 2: SCHED_RR

	printf("Plotica numero: %d\n", polit);

	if (polit == -1) {

		printf("ERROR %i -> %s\n", errno, strerror(errno));
	}
	else if (polit == SCHED_OTHER) {

		printf("Politica: %s\n", "SCHED_OTHER");
		
	}
	else if (polit == SCHED_FIFO) {

		printf("Politica: %s\n", "SCHED_FIFO");
	}
	else if (polit == SCHED_RR) {

		printf("Politica: %s\n", "SCHED_RR");
	}

	//Obtener prioridad de planificacion

	struct sched_param p;

	int priority = sched_getparam(pid, &p);

	if (priority == -1) {

		printf("ERROR %i -> %s\n", errno, strerror(errno));
	}
	else {

		printf("Prioridad: %d\n", p.sched_priority);
	}





}