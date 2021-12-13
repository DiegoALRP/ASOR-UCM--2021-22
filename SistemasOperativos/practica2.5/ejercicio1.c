#include <stdio.h>
#include <stdlib.h>
//Gestión de Direcciones (getaddrinfo)
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
//memset
#include <string.h>


int main(int argc, char** argv) {

	if (argc != 2) {

		printf("Introduce los parámetros necesarios: %s <nombre host o dirección>", argv[0]);
		return -1;
	}

	printf("1: %s, 2: %s \n", argv[1], argv[2]);
	
	//Gestión de Direcciones
	struct addrinfo hints;
	struct addrinfo *res;

	//Sockets
	//struct sockaddr_in;

	//Otener todas las posibles direcciones con las que se podría crear un socket asociado a un 	//host dado como primer argumento del programa

	memset(&hints, 0, sizeof(struct addrinfo));

	//ai.family tipo de familia de la dirección (IPv4 o IPv6)
	//con AF_INET y AF_INET6 respectivamente.
	//Si queremos cualquiera de las dos, se le asigna AF_UNSPEC.
	hints.ai_family = AF_UNSPEC;

	//ai.socktype especifica el tipo de socket a buscar.
	// SOCK_STREAM, SOCK_DATAGRAM (como en UDP).
	// Para nuestro caso, como queremos cualquiera, le asignamos 0.
	hints.ai_socktype = 0;

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

	int result = getaddrinfo(
					argv[1],
					NULL,
					&hints,
					&res);

	if (result != 0) {

		printf("getaddrinfo: %s \n", gai_strerror(result));
		return -1;
	}
	else {

		
		}
	}

	freeaddrinfo(res);

	return 0;

}