#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//mkfifo
#include <sys/types.h>
#include <sys/stat.h>
//open
#include <fcntl.h>
#include <limits.h>

int main(int argc, char** argv) {

	// Nombre del fichero a crear
    char current_dir[PATH_MAX];
    getcwd(current_dir, sizeof(current_dir));

    char* path = strcat(current_dir, "/tuberia3");

    // Creamos la tubería
	dev_t p;
	mknod(path, S_IFIFO, p);

	int fd = open(path, O_CREAT | O_TRUNC | O_WRONLY);
	// Si queremos que sea no bloqueante:
	// int fd = open(path, O_CREAT | O_TRUNC | O_WRONLY | O_NONBLOCK);

    write(fd, argv[1], strlen(argv[1])+1);

    close(fd);

    return 0;

}