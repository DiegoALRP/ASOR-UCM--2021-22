#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <locale.h>

int main() {

	time_t tiempo;
	
	if (time(&tiempo) == -1) {
	
		printf("Error time() %d: %s\n", errno, strerror(errno));
	}
	
	printf("Segundos desde el Epoch: %li\n", tiempo);
	
	struct tm tiempoLocal;
	tiempoLocal = *localtime(&tiempo);
	
	printf("Estamos en el año: %d\n", tiempoLocal.tm_year + 1900);
	
	char buf[50];
	//int LC_ALL = "es_ES";
	setlocale(LC_ALL, "es_ES");
	
	strftime(buf, 50, "%A, %d de %B de %Y, %R", &tiempoLocal);
	
	printf("Fecha: %s\n", buf);
	
	return 0;
}