#include <stdio.h>
#include <errno.h>
#include <sched.h>
#include <unistd.h>

int main(int argc, char **argv) {

	pid_t pid = getpid();

	printf("pid: %d\n", pid);

	//Obtener la política de planificación
	//Se puede poner como PID el 0, debido a que eso indica que es el
	//PID del propio proceso
	int policy = sched_getscheduler(pid);

	// Politicas:
	// 0: SCHED_OTHER
	// 1: SCHED_FIFO
	// 2: SCHED_RR

	printf("Política número: %d\n", policy);

	if (policy == -1) {

		printf("ERROR %i -> %s\n", errno, strerror(errno));
	}
	else if (policy == SCHED_OTHER) {

		printf("Política: %s\n", "SCHED_OTHER");
		
	}
	else if (policy == SCHED_FIFO) {

		printf("Política: %s\n", "SCHED_FIFO");
	}
	else if (policy == SCHED_RR) {

		printf("Política: %s\n", "SCHED_RR");
	}

	//Obtener prioridad de planificacion

	//Estructura que se pasa como parámetro
	//Almacena en la estructura la información de la prioridad
	struct sched_param p;
	
	//Para obtener información de la prioridad actual
	int priority = sched_getparam(pid, &p);

	if (priority == -1) {

		printf("ERROR %i -> %s\n", errno, strerror(errno));
	}
	else {

		//p.sched_priority devuelve la prioridad actual
		printf("Prioridad: %d\n", p.sched_priority);

		//Como parámetro se pasa la política de prioridad
		int max_priority = sched_get_priority_max(policy);
		int min_priority = sched_get_priority_min(policy);

		printf("Máxima Prioridad: %d\n", max_priority);
		printf("Mínima Prioridad: %d\n", min_priority);
	}
}