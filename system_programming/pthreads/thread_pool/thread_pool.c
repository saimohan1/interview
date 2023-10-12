#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdint.h>
#include <assert.h>
#include <unistd.h>
#include <sched.h>
#include <signal.h>
#include "queue.h"

#define MAX_WORKERS	10
#define MAX_WORKS	3

/* Global varibale to handle stop and clean up */
volatile sig_atomic_t thread_pool_stop = 0;

/* Work Struct */
struct work {
	uint32_t value;
};

/* Thread Pool Structure */
struct tpool {
	/* Queue data structure */
	struct queue *queue;	
	/* Worker threads, ie Pthreads */
	pthread_t *workers;
	/* Number of workers */	
	uint32_t num_workers;
	/* Mutex and CV for worker synchronization */
	pthread_mutex_t worker_mutex;
	pthread_cond_t worker_cond;
	/* Work producer thread */
	pthread_t producer;
};

struct worker_arg {
	pthread_t worker_id;
	struct tpool *tpool;	
};

static struct work *alloc_work(void)
{
	struct work *w = NULL;
	
	w = calloc(1, sizeof(*w));
	if (w == NULL) {
		printf("could not able to allocate work\n");
		return NULL;
	}
	assert(w != NULL);
	return w;
}

static void free_work(struct work *work)
{
	assert(work != NULL);
	free(work);
}

/* Main Worker Routine */
static void *worker_func(void *arg)
{
	struct worker_arg *worker_arg = (struct worker_arg*)arg;
	struct tpool *tpool = worker_arg->tpool;
	struct queue *queue = tpool->queue;
	int worker_id = worker_arg->worker_id;
	struct work *work = NULL;

	assert(queue);
	free(worker_arg);
	
	while(true) {
		pthread_mutex_lock(&tpool->worker_mutex);

		while(is_queue_empty(queue) && !thread_pool_stop) {
			pthread_cond_wait(&tpool->worker_cond, &tpool->worker_mutex);
		}	

		if (thread_pool_stop) {
			printf("worker[%d]Going to send broadcast for all the waiting threads\n",
					worker_id);
			pthread_mutex_unlock(&tpool->worker_mutex);
			break;
		}

		/* Queue has some work, Get the work and process */
		work = dequeue(queue);	
		if (work == NULL) {
			printf("Work is NULL\n");
			continue;
		}
		printf("[Worker:CPU %d:%d] The Work is completed, value:%d square:%d\n",
				worker_id, sched_getcpu(), work->value, work->value * 2);
		/* Release work */
		free_work(work);
		pthread_mutex_unlock(&tpool->worker_mutex);
	}
	
	printf("worker thread %d exiting\n", worker_id);
	return NULL;
}

static void init_workers(struct tpool *tpool)
{
	int ret = 0;
	for (int i = 0; i < tpool->num_workers; i++) {
		struct worker_arg *arg = calloc(1, sizeof(*arg));
		assert(arg);
		arg->worker_id = i;
	       	arg->tpool = tpool;	

		ret = pthread_create(&tpool->workers[i], NULL, worker_func,
				arg);	
		if (ret < 0) {
			printf("Failed to create pthread at index:%d\n", i);
		} else {
			printf("Worker-%d created successfully.\n", i);
		}
	}
}

static void * produce_work(void *arg)
{
	struct tpool *tpool = (struct tpool *)arg;
	struct queue *queue = tpool->queue;
	struct work *work = NULL;	

	while (!thread_pool_stop) {
		work = alloc_work();
		assert(work);
		work->value = rand() % 100;
		//printf("Successfully queued a work with value:%d\n", work->value);
		enqueue(queue, work);
		pthread_cond_signal(&tpool->worker_cond);
		sleep(1);
	}	
	
	/* Now we got the signal for stop,So release all the works 
	 * so that the threads will wakeup
	 */
	printf("Sending broadcast to the worker threads\n");
	pthread_cond_broadcast(&tpool->worker_cond);
	printf("Producer thread exiting\n");
	return NULL;
}

static void signal_handler(int signum)
{
	printf("Signal handler num:%d\n", signum);
	thread_pool_stop = 1;
}

static void init_sig_handler(void)
{
	struct sigaction sa;
	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	if (sigaction(SIGINT, &sa, NULL) < 0) {
		perror("sigaction");
		exit(1);
	}
	printf("Successfully Initialized signal handler\n");
}

static void clean_up(struct tpool *tpool)
{
	struct queue *queue = tpool->queue;
	
	assert(queue);

	/* Check if any works are there in the queue. Just Release the memory*/	
	while (!is_queue_empty(queue)) {
		struct work *work = dequeue(queue);
		if (work != NULL) {
			printf("Releasing work object in cleanup\n");
			free_work(work);
		}
	}

	/* Delete the Queue */	
	delete_queue(queue);	

	/* Release workers memory */
	free(tpool->workers);

	/* Release Thread pool memory */
	free(tpool);
	printf("All clean up done!\n");
}

static struct tpool *create_thread_pool(uint32_t num_workers)
{
	struct tpool *tpool = NULL;
	
	tpool = calloc(1, sizeof(struct tpool));
	if (tpool == NULL) {
		return NULL;
	}
	
	tpool->workers = calloc(1, num_workers * sizeof(pthread_t));
	if (tpool->workers == NULL) {
		goto fail_worker_alloc;
	}

	tpool->num_workers = num_workers;	

	/* Create work queue for tpool */ 	
	tpool->queue = create_queue(MAX_WORKS);
	if (tpool->queue == NULL) {
		goto fail_queue_alloc;
	}
	
	assert(tpool != NULL);
	assert(tpool->workers != NULL);
	assert(tpool->queue != NULL);

	return tpool;

fail_queue_alloc:
	free(tpool->workers);
fail_worker_alloc:
	free(tpool);
	tpool = NULL;
	return tpool;
}


int main() {
	struct tpool *tpool = NULL;
	
	/* Create a thread pool */
	tpool = create_thread_pool(MAX_WORKERS); 
	if (tpool == NULL) {
		printf("Failed to create a thread pool\n");
		exit(1);
	}
	
	/* Intialize signal handler */
	init_sig_handler();

	/* Initialize worker threads */
	init_workers(tpool);

	/* Create a thread which will produce works */
	pthread_create(&tpool->producer, NULL, produce_work, tpool);  
	printf("num of workers:%d\n", tpool->num_workers); 

	/* Wait for producer thread */
	pthread_join(tpool->producer, NULL);

	/* waiting for threads */
	for (int i = 0; i < tpool->num_workers; i++) {
		pthread_join(tpool->workers[i], NULL);
	}

	/* Clean up */
	clean_up(tpool);

	return 0;
}
