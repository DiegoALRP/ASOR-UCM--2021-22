#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

/*
*	Preguntas:
*		¿Qué sucede si el proceso padre termina antes que el hijo (observar el PPID del proceso hijo)?
*
*			El PID del proceso Padre aparece con valor 1.
*			Esto se debe a que cuando el proceso Padre termina su ejecución
*			muere y deja como huérfano al proceso Hijo,
*			y quien lo adopta es el proceso Init (que tiene como PID == 1)
*			y por eso aparece como proceso padre el proceso Init (PID == 1).
*
*			Es por esto que tampoco el proceso Hijo no aparece en la lista de los procesos del comando ps.
*
*		¿Y si el proceso que termina antes es el hijo (observar el estado del proceso hijo con ps)?
*
*			El PID del proceso Padre si aparece correctamente.
*			Debido a que esta vez el proceso Hijo terminó antes y no quedó huérfano de su Padre.
*/

int main() {

	pid_t pid;
	pid = fork();
	
	if (pid == -1) {
	
		printf("Error fork() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	else if (pid == 0) { //Proceso Hijo
	
		sleep(1);
		printf("Hijo %d (padre: %d)\n", getpid(), getppid());
		
		pid_t pgidO = getpgid(pid);
		pid_t sidO = getsid(pid);
		
		printf("Viejo PGID: %d\n", pgidO);
		printf("Viejo SID: %d\n", sidO);
		
		//Creamos nuevo grupo y sesion
		if (setsid() == -1) {
		
			printf("Error setpgid() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		
		printf("¡Se ha creado un nuevo grupo!\n");
		pid_t pgid = getpgid(pid);
		pid_t sid = getsid(pid);
		
		printf("Nuevo PGID: %d\n", pgid);
		printf("Nuevo SID: %d\n", sid);
	}
	else {
	
		printf("Padre %d (hijo: %d)\n", getpid(), pid);
		
		//sleep(1);
	}
	return 0;
}