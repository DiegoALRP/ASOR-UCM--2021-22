#include <stdio.h>
#include <errno.h>
//PIDs y Creacion de Procesos
#include <unistd.h>
#include <stdlib.h>

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


void printAttributes() {

	//pid
	pid_t pid = getpid();
	printf("\nPID: %d\n", pid);

	//parent pid
	pid_t ppid = getppid();
	printf("PID Padre: %d\n", ppid);

	//pid del grupo
	pid_t pgid = getpgid(pid);
	printf("ID Grupo: %d\n", pgid);

	//id de la sesion
	pid_t sid = getsid(pid);
	printf("ID Sesion: %d\n", sid);
}

int main(int argc, char **argv) {

	//Crear un proceso hijo
	pid_t pid;
	pid = fork();

	switch (pid) {
		case -1: //Error al crear proceso
			
			perror("Error fork");
			exit(1);

		case 0:;	//Proceso Hijo

			pid_t child_sid2;
			child_sid2 = setsid(); //Crea una nueva sesion

			if (chdir("/tmp") == -1) { //Cambio de directorio a /tmp

				perror("Error cambio de fichero a /tmp");
				exit(1);
			}
			else {

				sleep(5);
				printf("\nProceso Hijo, PID: %i (Padre: %i)\n", getpid(), getppid());
				printAttributes();
			}
			break;

		default: //Proceso Padre

			//sleep(5);
			printf("\nProceso Padre, PID: %i (Hijo: %i)\n", getpid(), pid);
			printAttributes();
			break;
	}

	return 0;
}