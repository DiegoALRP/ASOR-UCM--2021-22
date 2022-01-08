#include <stdio.h>
#include <string.h>
#include <errno.h>
//getaddrinfo
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int main(int argc, char *argv[]) {

	if (argc != 3) {
	
		printf("Introduce los parámetros correctamente\n");
		printf("Uso: %s <direccion> <puerto>\n", argv[0]);
		
		return -1;
	}

	printf("argv[0]: %s, argv[1]: %s, argv[2]: %s, argv[3]: %s\n", argv[0], argv[1], argv[2], argv[3]);
	
	
	
	return 0;
}