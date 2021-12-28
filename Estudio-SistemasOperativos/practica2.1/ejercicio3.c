#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {

	int i;
	for (i = 0; i < 256; i++) {
	
		printf("Error %d: %s\n", i, strerror(i));
	}
	
	return 0;
}