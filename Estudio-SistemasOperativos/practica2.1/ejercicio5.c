#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/utsname.h>

int main() {

	struct utsname buf;
	
	if (uname(&buf) == -1) {
	
		printf("Error uname %d: %s\n", errno, strerror(errno));
		return -1;
	}
	
	printf("Sistema: %s\n", buf.sysname);
	printf("Nodename: %s\n", buf.nodename);
	printf("Release: %s\n", buf.release);
	printf("Version: %s\n", buf.version);
	printf("Machine: %s\n", buf.machine);
	
	return 0;
}