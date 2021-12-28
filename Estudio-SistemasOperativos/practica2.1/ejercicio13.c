#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

int main() {

	time_t tiempo;
	
	if (time(&tiempo) == -1) {
	
		printf("Error time() %d: %s\n", errno, strerror(errno));
	}
	
	printf("Segundos desde el Epoch: %li\n", tiempo);
	
	struct timeval tvIni; //TimeVal
	struct timezone tzIni; //TimeZone
	
	struct timeval tvFin; //TimeVal
	struct timezone tzFin; //TimeZone
	
	if (gettimeofday(&tvIni, &tzIni) == -1) {
	
		printf("Error gettimeofday() %d: %s\n", errno, strerror(errno));
	}
	
	int i;
	for (i = 0; i < 1000000; i++)
	
	if (gettimeofday(&tvFin, &tzFin) == -1) {
	
		printf("Error gettimeofday() %d: %s\n", errno, strerror(errno));
	}
	
	printf("Ha tardado %li microsegundos\n", (tvFin.tv_usec - tvIni.tv_usec));
	
	return 0;
}