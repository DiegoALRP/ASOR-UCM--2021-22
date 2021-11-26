#include <stdio.h>
#include <errno.h>
//PIDs y Creacion de Procesos y Execvp (3)
#include <unistd.h>
//Procesos
#include <stdlib.h>
//Open (2)
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


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

				//sleep(5);
				printf("\nProceso Hijo, PID: %i (Padre: %i)\n", getpid(), getppid());
				printAttributes();

				int std_out = open("/tmp/daemon.out", O_CREAT | O_TRUNC | O_RDWR, 0777);
        			int std_err = open("/tmp/daemon.err", O_CREAT | O_TRUNC | O_RDWR, 0777);
        			int std_in = open("/dev/null", O_CREAT | O_TRUNC | O_RDWR, 0777);        

        			int fd0 = dup2(std_in, 0);
        			int fd1 = dup2(std_err, 1);
				int fd2 = dup2(std_out, 2);

        			if (execvp(argv[1], &(argv[1])) == -1) {
            				
					printf("Error(%i) -> %s\n", errno, strerror(errno));
        			}
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