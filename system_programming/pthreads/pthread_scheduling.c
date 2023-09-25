#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <stdlib.h>

static void *thread_func(void *arg)
{
	printf("The thread is running on core:%d\n", sched_getcpu());	

	return NULL;
}


int main() {
	pthread_t tid;
	cpu_set_t cpuset;
	int cpu_core = 2;
	pthread_attr_t attr;
	struct sched_param param;
	
	/* Populate the cpuset */
	CPU_ZERO(&cpuset);
	CPU_SET(cpu_core, &cpuset);

	/* Populate the attribute object */
	if (pthread_attr_init(&attr) != 0) {
		perror("pthread_attr_init");
		exit(1);
	}

	/* Set cpu affinity */
	if (pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset) != 0) {
		perror("pthread_attr_setaffinity_np");
		exit(1);
	}	

	/* Set the thread priorty and scheduling policy */
	param.sched_priority = 99;
	if (pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0) {
		perror("pthread_attr_setschedpolicy");
		exit(1);
	}

	if (pthread_attr_setschedparam(&attr, &param) != 0) {
		perror("pthread_attr_setschedpolicy");
		exit(1);
	}



	
	/* create the thread with specified affinity */
	if (pthread_create(&tid, &attr, thread_func, NULL) != 0) {
		perror("pthread_create");
		exit(1);
	}
	
	printf("Successfully created the thread\n");	
	
	/* Join the pthread */
	pthread_join(tid, NULL);
	
	/* Destroy attribute */
	pthread_attr_destroy(&attr);

	return 0;
}
