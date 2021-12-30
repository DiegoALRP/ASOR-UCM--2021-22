#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

	printf("argv[0]: %s, argv[1]: %s\n", argv[0], argv[1]);
	
	if (argc < 2) {
	
		printf("Introduce los parametros necesarios\n");
		printf("Uso: %s <comando>\n", argv[0]);
		
		return -1;
	}
	
	pid_t pid;
	pid = fork();
	
	if (pid == -1) {
	
		printf("Error fork() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	else if (pid == 0) { //Proceso Hijo
	
		sleep(10);
		printf("Hijo %d (padre: %d)\n", getpid(), getppid());
		
		//Creamos nuevo grupo y sesion
		if (setsid() == -1) {
		
			printf("Error setpgid() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		
		if (chdir("/tmp") == -1 ) {
		
			printf("Error chdir() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		
		int fdSalida = open("/tmp/daemon.out", O_CREAT | O_TRUNC | O_RDWR, 0777);
		int fdError = open("/tmp/daemon.err", O_CREAT | O_TRUNC | O_RDWR, 0777);
		int fdEntrada = open("/dev/null", O_CREAT | O_TRUNC | O_RDWR, 0777); 
		
		int salida = dup2(fdSalida, 1);
		int salidaErr = dup2(fdError, 2);
		int entrada = dup2(fdEntrada, 0);
		
		pid_t pgidO = getpgid(pid);
		pid_t sidO = getsid(pid);
		
		printf("Viejo PGID: %d\n", pgidO);
		printf("Viejo SID: %d\n", sidO);
		
		
		printf("¡Se ha creado un nuevo grupo!\n");
		pid_t pgid = getpgid(pid);
		pid_t sid = getsid(pid);
		
		printf("Nuevo PGID: %d\n", pgid);
		printf("Nuevo SID: %d\n", sid);
		
		if (execvp(argv[1], &argv[1]) == -1) {
	
			printf("Error system() %d: %d\n", errno, strerror(errno));
		
			return -1;
		}
	}
	else {
	
		printf("Padre %d (hijo: %d)\n", getpid(), pid);
		
		int status;
		waitpid(pid, &status, 0);
	}
	return 0;
}