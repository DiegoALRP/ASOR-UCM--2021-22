#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
       
int main() {

	pid_t pid = getpid();
    pid_t ppid = getppid();
    pid_t pgid = getpgid(pid);
    pid_t sid = getsid(pid);
    
    printf("PID: %d\n", pid);
    printf("PPID: %d\n", ppid);
    printf("PGID: %d\n", pgid);
    printf("SID: %d\n", sid);

	struct rlimit rlim;
	
	if (getrlimit(RLIMIT_NOFILE, &rlim) == -1) {
	
		printf("Error getrlimit() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	printf("Limite actual obligado por el kernel: %d\n", rlim.rlim_cur);
	printf("Limite máximo: %d\n", rlim.rlim_max);

	char buf[100];
	getcwd(buf, 100);
	
	printf("Directorio actual: %s\n", buf);
	
	return 0;
}