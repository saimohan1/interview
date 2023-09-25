#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

static void *thread_func(void *arg)
{	
	printf("This is a thread function\n");
	return NULL;
}

int main() {
	pthread_t thread;
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	if (pthread_create(&thread, &attr, thread_func, NULL) != 0) {
		perror("Thread create failed\n");
		return EXIT_FAILURE;	
	}		

	pthread_attr_destroy(&attr);
	
	pthread_join(thread, NULL);
	printf("Main Thread continues\n");
	return 0;
}
