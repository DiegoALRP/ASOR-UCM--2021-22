#include <stdio.h>
#include <errno.h>
#include <sched.h>
#include <unistd.h>

int main(int argc, char **argv) {

	pid_t pid = getpid();

	printf("pid: %d\n", pid);

	//Obtener la politica de planificacion
	int policy = sched_getscheduler(pid);

	// 0: SCHED_OTHER
	// 1: SCHED_FIFO
	// 2: SCHED_RR

	printf("Plotica numero: %d\n", policy);

	if (policy == -1) {

		printf("ERROR %i -> %s\n", errno, strerror(errno));
	}
	else if (policy == SCHED_OTHER) {

		printf("Politica: %s\n", "SCHED_OTHER");
		
	}
	else if (policy == SCHED_FIFO) {

		printf("Politica: %s\n", "SCHED_FIFO");
	}
	else if (policy == SCHED_RR) {

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

		int max_priority = sched_get_priority_max(policy);
		int min_priority = sched_get_priority_min(policy);

		printf("Maxima Prioridad: %d\n", max_priority);
		printf("Minima Prioridad: %d\n", min_priority);
	}
}