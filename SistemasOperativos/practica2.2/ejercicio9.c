#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>

int main(int argc, char **argv) {

	struct stat buf;
	char pathname[] = "/home/cursoredes/Documents/Practica2/ejercicio9.txt";

	int fd = open(pathname, O_CREAT | O_TRUNC | O_RDONLY, 0777);	

	if (fd == -1) {
		
		printf("ERROR(%d): %s\n", errno, strerror(errno));
	}

	int st = fstat(fd, &buf);

	unsigned int majorN = major(buf.st_dev);
	unsigned int minorN = minor(buf.st_dev);
	mode_t proteccion = buf.st_mode;
	struct tm tiempo = *localtime(&(buf.st_atime));
	setlocale(LC_ALL, "es_ES");

	printf("Numero major: '%d', asociado al dispositivo.\n", majorN);
	printf("Numero minor: '%d', asociado al dispositivo.\n", minorN);
	printf("Numero de inodo: %d.\n", buf.st_ino);

	printf("Tipo de archivo: ", buf.st_mode);
	if (S_ISLNK(proteccion))printf("enalce simbolico.\n");
	else if (S_ISREG(proteccion)) printf("fichero.\n");
	else if (S_ISLNK(proteccion)) printf("directorio.\n");

	printf("Ultima hora accedida: %d/%d/%d %d:%d\n", tiempo.tm_mday, tiempo.tm_mon +1, tiempo.tm_year +1900, tiempo.tm_hour, tiempo.tm_min);
	
	/*
	* La diferecia entre st_mtime y st_ctime:
	* es que "st_mtime" se refiere a la ultima vez modificado
	* por un write, mientras que "st_ctime" se refiere la cuando
	* se altera el inodo, por modificacion de propietario, permiso.
	*/
}