#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {

	if (setuid(0) == -1) {
		
		printf("Setuid Error Code %d: %s\n",errno,strerror(errno));
		return -1;
	}
	return 1;
}