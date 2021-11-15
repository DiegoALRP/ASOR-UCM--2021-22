#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <locale.h>

int main(int argc, char **argv) {

	char* path = argv[1];

	int fd = open(path, O_CREAT | O_TRUNC | O_RDWR, 0777);

	int lock = lockf(fd, F_TEST, 0);

	if (lock == -1) {

		printf("Cerrojo bloqueado, vuelva a intentarlo mas tarde\n");
	}
	else {
		
		int block = lockf(fd, F_LOCK, 0);
		time_t tiempoLocal = time(NULL);
		struct tm tiempo = *localtime(&tiempoLocal);
		printf("Lock tomado\n");
		printf("Hora actual: %d/%d/%d %d:%d\n", tiempo.tm_mday, tiempo.tm_mon +1, tiempo.tm_year +1900, tiempo.tm_hour, tiempo.tm_min);
		sleep(30);
	}

	close(fd);
	return 0;