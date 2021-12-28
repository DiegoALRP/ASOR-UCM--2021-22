#include <stdio.h>
#include <errno.h>
#include <time.h>

int main() {

	time_t tiempo;
	
	if (time(&tiempo) == -1) {
	
		printf("Error time() %d: %s\n", errno, strerror(errno));
	}
	
	printf("Segundos desde el Epoch: %li\n", tiempo);
	
	struct tm tiempoLocal;
	tiempoLocal = *localtime(&tiempo);
	
	printf("Estamos en el año: %d\n", tiempoLocal.tm_year + 1900);
	return 0;
}