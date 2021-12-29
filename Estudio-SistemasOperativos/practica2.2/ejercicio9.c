#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
//ctime
#include <time.h>

int main() {

	struct stat info;
	
	int st = stat("ejercicio9prueba", &info);
	
	if (st == -1) {
	
		printf("Error stat() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	long majorN = (long) major(info.st_dev);
	long minorN = (long) minor(info.st_dev);
	
	printf("Número major asociado: %d\n", majorN);
	printf("Número minor asociado: %d\n", minorN);
	printf("Número de inodo del fichero: %d\n", info.st_ino);
	
	//Tipo de fichero
	if (info.st_mode & S_IFDIR) {
	
		printf("Es un directorio\n");
	}
	else if (info.st_mode & S_IFLNK) {
	
		printf("Es un enlace simbólico\n");
	}
	else if (info.st_mode & S_IFREG) {
	
		printf("Es un fichero regular/ordinario\n");
	}
	else {
	
		printf("No es ni directorio, ni enlace simbólico ni fichero regular\n");
	 }
	 
	 //Horas:
	 printf("Última vez que se cambió los permisos:	%s\n", ctime(&info.st_ctime));
     printf("Último acceso al fichero:               %s\n", ctime(&info.st_atime));
     printf("Última modificación del fichero:        %s\n", ctime(&info.st_mtime));
     
     /*
     * La diferencia reside en que st_ctime es la última vez 
     * que se cambió el estado del fichero.
     * Es decir, que se cambió sus permisos, su inodo, contador de enlaces, etc.
     *
     * Mientras que st_mtime es la última vez que se
     * cambió el fichero en términos de su contenido.
     * Por ejemplo al usar write o truncate
     */
}