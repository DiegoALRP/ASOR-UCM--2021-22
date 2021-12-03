#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//mknod
#include <sys/types.h>
#include <sys/stat.h>
//open
#include <fcntl.h>
#include <limits.h>

int main(int argc, char** argv) {

	// Nombre del fichero a crear
    char current_dir1[PATH_MAX];
    getcwd(current_dir1, sizeof(current_dir1));

	char current_dir2[PATH_MAX];
    getcwd(current_dir2, sizeof(current_dir2));

    char* path1 = strcat(current_dir1, "/tuberia1");
	char* path2 = strcat(current_dir2, "/tuberia2");

	mkfifo(path1, 0777);
	mkfifo(path2, 0777);
	int tuberia1 = open(path1, O_RDONLY | O_NONBLOCK);
	int tuberia2 = open(path2, O_RDONLY | O_NONBLOCK);

	if (tuberia1 == -1) {

		perror("No se ha podido abrir la tuberia #1\n");
		return -1;
	}
	else {

		printf("Se ha creado la tubería #1!\n");
	}

	if (tuberia2 == -1) {

		perror("No se ha podido abrir la tuberia #2\n");
		return -1;
	}
	else {

		printf("Se ha creado la tubería #2!\n");
	}

	char buffer[256];

	fd_set rfds;

	int seleccion;
	int tuberiaAct;

	while (1) {
		
		FD_ZERO(&rfds);
		FD_SET(tuberia1, &rfds);
		FD_SET(tuberia2, &rfds);

		printf("fd tuberia1: %d, fd tuberia2: %d\n", tuberia1, tuberia2);

		if (tuberia1 > tuberia2) {

			tuberiaAct = tuberia1;
		}
		else {

			tuberiaAct = tuberia2;
		}

		seleccion = select(tuberiaAct + 1, &rfds, 0, 0, 0);

		if (seleccion == -1) {

			perror("Error al hacer el select\n");
		}
		else {

			printf("Todo va bien, el select ha ido bien\n");

			if (FD_ISSET(tuberia1, &rfds)) {

				printf("Lectura de tuberia #1\n");

				int bytes = read(tuberia1, buffer, 255);
				buffer[bytes] = '\0';

				if (bytes == 0) {

					printf("Cero bytes\n");
					close(tuberia1);
					tuberia1 = open(path1, O_RDONLY | O_NONBLOCK);

					if (tuberia1 == -1) {

						perror("(1) No se ha podido abrir la tubería #1\n");
						return -1;
					}
				}
				else {

					printf("\n--Tuberia1: %s", buffer);
				}
			}
			else if (FD_ISSET(tuberia2, &rfds)) {

				printf("Lectura de tuberia #2\n");

				int bytes = read(tuberia2, buffer, 255);
				buffer[bytes] = '\0';

				if (bytes == 0) {

					printf("Cero bytes\n");
					close(tuberia2);
					tuberia2 = open(path2, O_RDONLY | O_NONBLOCK);

					if (tuberia2 == -1) {

						perror("(2) No se ha podido abrir la tubería #2\n");
						return -1;
					}
				}
				else {

					printf("\n--Tuberia2: %s", buffer);
				}

			}
			else {

				continue;
			}
		}
	}

    return 0;

}