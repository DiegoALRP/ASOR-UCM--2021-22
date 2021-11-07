#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>

int main(int argc, char **argv) {

	char* path = argv[1];

	struct stat dirStat;

	if (stat(path, &dirStat) == -1) {

		printf("ERROR %i -> %s\n", errno, strerror(errno));
	}
	else {

		DIR* dir = opendir(path);
		if (S_ISDIR(dirStat.st_mode)) {

			struct dirent* dirStr = readdir(dir);

			printf("A\n");

			double kiloB = 0;

			while (dirStr != NULL) {

				struct stat statBuf;
				int st = stat(dirStr->d_name, &statBuf);

				if (dirStr->d_type == DT_REG) { //Fichero
					
					//Nombre del fichero

					if (statBuf.st_mode & S_IXUSR) printf("%s*\n", dirStr->d_name); //Fichero ejecutable
					else printf("%s\n", dirStr->d_name);    //Fichero regular

					kiloB += statBuf.st_size;
				}
				else if (dirStr->d_type == DT_DIR) {    //Directorio

					printf("%s/\n", dirStr->d_name);
				}
				else if (dirStr->d_type == DT_LNK) {

					char* buf;
					ssize_t bufsiz, nbytes;
					bufsiz = statBuf.st_size + 1;
					//bufsiz = PATH_MAX;
					if (statBuf.st_size == 0 || S_ISDIR(statBuf.st_mode)) {

						bufsiz = PATH_MAX;
					}

					buf = malloc(bufsiz);

					if (buf == NULL) {

                            perror("malloc");
                            exit(EXIT_FAILURE);
           				}

					nbytes = readlink(dirStr->d_name, buf, bufsiz);
                    if (nbytes == -1) {

                        perror("readlink");
                        exit(EXIT_FAILURE);
                    }

					printf("%s->%s\n",dirStr->d_name, buf);

					kiloB += statBuf.st_size;
				}
			
				dirStr = readdir(dir);
			}
			
			printf("\nEl tamaño total que ocupan los ficheros es de: %.2f kilobytes\n", kiloB/1000);
		}
	}
}