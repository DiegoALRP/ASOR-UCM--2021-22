#include <stdio.h>
#include <string.h>
#include <errno.h>
//execvp
#include <stdlib.h>

int main(int argc, char *argv[]) {

	printf("argv[0]: %s, argv[1]: %s\n", argv[0], argv[1]);
	
	if (argc < 2) {
	
		printf("Introduce los parametros necesarios\n");
		printf("Uso: %s <comando>\n", argv[0]);
		
		return -1;
	}
	
	
	if (execvp(argv[1], &argv[1]) == -1) {
	
		printf("Error system() %d: %d\n", errno, strerror(errno));
		
		return -1;
	}

	printf("El comando terminó de ejecutarse\n");
    //Para que se imprima habria que hacer fork y escribir el mensaje
    //a traves del proceso padre, ya que con execvp se borra el programa
    //y solo se ejecuta lo del execvp
	
	return 0;
}