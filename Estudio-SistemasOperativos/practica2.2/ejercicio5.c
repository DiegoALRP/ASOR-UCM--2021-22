#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main () {

	open("ejercicio5prueba.c", O_CREAT | O_RDWR | O_TRUNC, 0645);
	
	return 0;
}