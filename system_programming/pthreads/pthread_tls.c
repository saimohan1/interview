#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <sched.h>
#include <unistd.h>

#define THREAD_COUNT	2

static int thread_id[THREAD_COUNT] = {0, 1};

static __thread int tls_data = 0;

static void *
thread_func(void *arg)
{
	int thread_id = *((int *)arg);
	while (1) {
		if (tls_data == 0) {
			tls_data = thread_id + 100;	
			printf("Sleeing for 30 sec for thread:%d tls_Data:%d\n", thread_id, tls_data);
			sleep(5);
			sched_yield();
		} else {
			printf("Thread:%d Value of tls data:%d\n", thread_id, tls_data);
			break;
		}
	}
	return NULL;
}

int main() {
	pthread_t tid[THREAD_COUNT];
	for (int i = 0; i < THREAD_COUNT; i++) {
		if (pthread_create(&tid[i], NULL, thread_func, &thread_id[i])) {
			perror("pthrea_create");
			assert(0);
		}
	}
	for (int i = 0; i < THREAD_COUNT; i++) {
		pthread_join(tid[i], NULL);
	}	
	return 0;
}
