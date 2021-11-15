#include <stdio.h>
#include <errno.h>
//PIDs y Creacion de Procesos
#include <unistd.h>
//Limites de recursos
#include <sys/time.h>
#include <sys/resource.h>
//Malloc
#include <limits.h>
#include <stdlib.h>

private void printAttributes() {

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
	pid = fork(void);

	switch (pid) {
		case -1: //Error al crear proceso
			
			perror("fork");
			exit(1);

		case 0:	//Proceso Hijo

			printf("Proceso Hijo, PID: %i (Padre: %i)\n", getpid(), getppid());
			break;

		default: //Proceso Padre

			printf("Proceso Padre, PID: %i (Hijo: %i)\n", getpid(), pid);
			break;
	}

	return 0;
}