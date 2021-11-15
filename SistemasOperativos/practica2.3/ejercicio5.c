#include <stdio.h>
#include <errno.h>
//PIDs y Directorio
#include <unistd.h>
//Limites de recursos
#include <sys/time.h>
#include <sys/resource.h>
//Malloc
#include <limits.h>
#include <stdlib.h>

int main(int argc, char **argv) {

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

	struct rlimit lim;
	//Resource: RLIMIT_NOFILE. Numero de descriptores de ficheros
	int limit = getrlimit(RLIMIT_NOFILE, &lim);

	if (limit == -1) {

		printf("ERROR %i -> %s\n", errno, strerror(errno));
	}
	else {

		printf("\nNumero maximo de descriptores de fichero:\n");
		printf("Limite actual: %d\n", lim.rlim_cur);
		printf("Valor maximo: %d\n", lim.rlim_max);
	}

	char* buffer;
	size_t size = PATH_MAX + 1;
	buffer = malloc(size);

	getcwd(buffer, size);

	printf("\nDirectorio de trabajo actual: %s\n\n", buffer);

	free(buffer);
}