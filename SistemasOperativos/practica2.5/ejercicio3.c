#include <stdio.h>
#include <stdlib.h>
//Gestión de Direcciones (getaddrinfo)
//Socket
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//memset
#include <string.h>
//time
#include <time.h>


int main(int argc, char** argv) {

	if (argc != 4) {

		printf("Introduce los parámetros necesarios: %s <dirección> <puerto> <comando>\n", 
					argv[0]);
		return -1;
	}

	printf("argv[1]: %s\nargv[2]: %s\n", argv[1], argv[2]);
	
	//Gestión de Direcciones
	struct addrinfo hints;
	struct addrinfo *resultInfo;

	memset(&hints, 0, sizeof(struct addrinfo));

	//ai.family tipo de familia de la dirección (IPv4 o IPv6)
	//Si queremos cualquiera de las dos, se le asigna AF_UNSPEC.
	hints.ai_family = AF_UNSPEC;

	//ai.socktype especifica el tipo de socket a buscar.
	hints.ai_socktype = SOCK_DGRAM;

	//Especifica el protocolo de los sockets a retornar.
	// Le asignamos 0 para indicar que puede ser cualquier protocolo
	hints.ai_protocol = 0;

	//Esta especifica opciones adicionales.
	// AI_PASSIVE indica que los sockets retornados podrán ser usados para bind(ing),
	// que podrán aceptar conexiones.
	hints.ai_flags = AI_PASSIVE;

	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;


	return 0;
}









