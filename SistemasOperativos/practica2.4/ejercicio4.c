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

    char current_dir[PATH_MAX];
    getcwd(current_dir, sizeof(current_dir));

    char* path = strcat(current_dir, "/tuberia3");

    mkfifo(path, 0777); // Se crea la tubería

	int fd = open(path, O_CREAT | O_TRUNC | O_WRONLY);

    write(fd, argv[1], strlen(argv[1])+1);

    close(fd);

    return 0;

}