#include <stdio.h>
#include <errno.h>
#include <time.h>

int main() {

	time_t tiempo;
	
	if (time(&tiempo) == -1) {
	
		printf("Error time() %d: %s\n", errno, strerror(errno));
	}
	
	printf("Segundos desde el Epoch: %li\n", tiempo);
	
	return 0;
}