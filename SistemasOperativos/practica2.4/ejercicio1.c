#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char** argv) {

	//printf("1[%s], 2[%s], 3[%s], 4[%s]", argv[1], argv[2], argv[3], argv[4]);

	int tuberia[2];

    if (pipe(tuberia) == -1) {

		printf("ERROR PIPE");
        perror("pipe");
        return -1;
    }

    int pid = fork(); //Tambien puede ser de tipo pid_t

	switch(pid) {

        case -1: //Error fork
            perror("fork");
            return -1;
            break;

		case 0:	//Proceso Hijo

            //printf("Hijo, lector de la tuberia (%i)\n", pid);

            close(0);	//Cerramos por seguridad la entrada estandar
            dup2(tuberia[0], 0);	//duplicamos la entrada estandar a la entrada de la tuberia

			//Cerramos ambas extremos
            close(tuberia[0]);	//Se cierra porque ya se ha utilizado y no nos hace falta
            close(tuberia[1]);	//Se cierra porque no se va a utilizar la salida estandar

            execlp(argv[3], argv[3], argv[4], 0);
			break;

		default:	//Proceso Padre (no sabemos su PID)

            //printf("Padre, escritor de la tuberia (%i)\n", pid);

            close(1);	//Cerramos por seguridad la salida estandar
            dup2(tuberia[1], 1);
            close(tuberia[0]);
            close(tuberia[1]);

            execlp(argv[1], argv[1], argv[2], 0);
			break;
    }

	return 0;
}