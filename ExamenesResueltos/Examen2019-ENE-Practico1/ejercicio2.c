#include <stdio.h>
#include <string.h>
#include <errno.h>
//fork
#include <unistd.h>
//getpid y get ppid
#include <sys/types.h>
#include <unistd.h>
//wait
#include <sys/types.h>
#include <sys/wait.h>
//setsid
#include <unistd.h>
//chdir
#include <unistd.h>

int main(int argc, char *argv[]) {

	pid_t pid;
	pid = fork();
	
	if (pid == -1) {
	
		printf("Error fork() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	else if (pid == 0) {
	
		printf("Hijo %d (Padre %d)\n", getpid(), getppid());
		
		//Crear una nueva sesion
		pid_t sid = setsid();
		
		if (sid == -1) {
		
			printf("Error setsid() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		
		//Cambiar de directorio
		int dir = chdir("/tmp");
		
		if (dir == -1) {
		
			printf("Error chdir() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
		
		//Mostrar pid, ppid, pgid, sid
		pid_t pid = getpid();
		printf("Identificador de proceso: %d\n", pid);
		printf("Identificador de proceso padre: %d\n", getppid());
		printf("Identificador de grupo de procesos: %d\n", getpgid(pid));
		printf("Identificador de sesión: %d\n", getsid(pid));
		
		int res = execvp(argv[1], &argv[1]);
		
		if (res == -1) {
		
			printf("Error exe() %d: %s\n", errno, strerror(errno));
			
			return -1;
		}
	}
	else {
	
		printf("Padre %d (Hijo %d)\n", getpid(), pid);
		
		//Para esperar al hijo
		//int status;
		//waitpid(pid, &status, 0); 
	}

	return 0;
}