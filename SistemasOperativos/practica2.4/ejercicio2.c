#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//para depurar: gcc -g wall ejercicio2.c
//gdb a.out
//layout next

int main(int argc, char** argv) {

    int tuberia_ph[2];	//Tuberia de padre a hijo
    int tuberia_hp[2];	//Tuberia de hijo a padre
    int fin = 0, m = 0;
    char buffer[256];

	if (pipe(tuberia_ph) == -1) {

        perror("pipe");
        return -1;
    }
    if (pipe(tuberia_hp) == -1) {

        perror("pipe");
        return -1;
    }

	int pid = fork();

    switch (pid) {

		case -1:	//Error fork
		    
		    perror("fork");
		    return -1;
		    break;

		case 0:		//Proceso hijo

        close(tuberia_ph[1]);	//Salida estandar de tuberia padre a hijo
        close(tuberia_hp[0]);	//Entrada estandar de tuberia hijo a padre

        while (!fin) {

            int rc = read(tuberia_ph[0], buffer, 256);

            buffer[rc] = '\0';	//Ultimo caracter para indicar fin de palabra
            printf("Mensaje recibido: %s\n", buffer);
            sleep(1);

			// Q flag de fin. L flag de continuar
            if (++m == 10){

                write(tuberia_hp[1], "Q", 1);
                fin = 1;
            }
            else {

                write(tuberia_hp[1], "L", 1);
				m;
            }
        }

		close(tuberia_ph[0]);
        close(tuberia_hp[1]);

        return 0;

        break;

		default:

        close(tuberia_ph[0]);	//Entrada estandar tuberia de padre a hijo
        close(tuberia_hp[1]);	//Salida estandar tuberia de hijo a padre

        while (!fin) {

            printf("? ");

            scanf("%s", buffer);

            write(tuberia_ph[1], buffer, strlen(buffer)+1);

            read(tuberia_hp[0], buffer, 1);

            if (buffer[0] == 'Q') {

                fin = 1;
            }
        }

		close(tuberia_ph[1]);
        close(tuberia_hp[0]);

        return 0;

        break;

		}

    return 0;
}


