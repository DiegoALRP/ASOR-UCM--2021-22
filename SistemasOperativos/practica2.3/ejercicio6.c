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
	pid_t pid = fork(void);

	if (pid == 0) {	//Proceso Hijo

		printf("Proceso Hijo");
	}
	else if (pid > 0) {	//Proceso Padre

		printf("Proceso Padre");
	}
	else {

		printf("ERROR %i -> %s\n", errno, strerror(errno));
	}

	return 0;
}