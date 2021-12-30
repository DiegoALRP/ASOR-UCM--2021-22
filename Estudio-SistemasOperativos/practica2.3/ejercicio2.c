#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
       
int main() {

	//int sched_getscheduler(pid_t pid);
	
	pid_t pid = getpid();
	
	printf("PID del proceso actual: %d\n", pid);
	
	int policy = sched_getscheduler(pid);
	
	if (policy == -1) {
	
		printf("Error sched_getscheduler() %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	else if (policy == SCHED_OTHER) {
	
		printf("Politica SCHED_OTHER\n");
	}
	else if (policy == SCHED_FIFO) {
	
		printf("Politica SCHED_FIFO\n");
	}
	else if (policy == SCHED_RR) {
	
		printf("Politica SCHED_RR\n");
	}
	else {
	
		printf("Politica: %d\n", policy);
	}
	
	struct sched_param param;
	
	if (sched_getparam(pid, &param) == -1) {
	
		printf("Error sched_getparam %d: %s\n", errno, strerror(errno));
		
		return -1;
	}
	
	printf("Prioridad del proceso actual: %d\n", param.sched_priority);
	
	int max = sched_get_priority_max(policy);

    int min = sched_get_priority_min(policy);
    
    printf("Prioridad máxima: %d\n", max);
    printf("Prioridad mínima: %d\n", min);

	return 0;
}