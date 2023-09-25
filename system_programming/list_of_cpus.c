#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>
#include <unistd.h>


int main() {
	int num_cpus = sysconf(_SC_NPROCESSORS_ONLN);

	printf("Numer of cpu cores in the system: %d\n", num_cpus);  

	cpu_set_t core_set;
	CPU_ZERO(&core_set);

	if (sched_getaffinity(0, sizeof(cpu_set_t), &core_set) == -1) {
		perror("sched_getaffinity");
		return -1;
	}

	printf("List of CPU cores available to this process: ");
	for (int core = 0; core < num_cpus; core++) {
		if (CPU_ISSET(core,  &core_set)) {
			printf("%d ", core);
		}
	}
	printf("\n");
	return 0;
}
