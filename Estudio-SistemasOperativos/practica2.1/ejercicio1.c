#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {

	if (setuid(0) == -1) {
		perror("Error setuid()\n");
		strerror("Error 2 setuid()\n");
		fprintf(stderr, "Error 3 setuid()\n");
		printf("Setuid Error Code %d: %s\n",errno,strerror(errno));
		return -1;
	}
	return 1;
}