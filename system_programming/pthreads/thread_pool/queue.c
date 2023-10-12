#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h> 
#include "queue.h"

bool is_queue_full(struct queue *queue)
{
	return queue->qfull;
}

bool is_queue_empty(struct queue *queue)
{
	return queue->qempty;
}

int enqueue(struct queue *queue, void *data)
{
	if (is_queue_full(queue)) {
		printf("Queue is FULL\n");
		return -1;
	}

	queue->tail = (queue->tail + 1) % queue->qsize;
	queue->queue[queue->tail] = data;
	queue->qempty = false;
	queue->qsize++;
	if (queue->tail == queue->qsize + 1)
		queue->qfull = true;

	return 0;
}

void * dequeue(struct queue *queue) {
	
	void *data = NULL;

	if (is_queue_empty(queue)) {
		printf("Queue is empty\n");
		return NULL;
	}

	queue->head = (queue->head + 1) % queue->qsize;
	data = queue->queue[queue->head];
	queue->qsize++;
	if (queue->head == queue->tail)
		queue->qempty = true;
	queue->qfull = false;
	return data;
}	


static void init_queue(struct queue *queue)
{
	/* Mark all the queue as NULL */		
	for (int i = 0; i < queue->qsize; i++) {
		queue->queue[i] = NULL;
	}
	
	queue->head = 0;
	queue->tail = 0;
	queue->qfull = false;
	queue->qempty = true;
}

struct queue *create_queue(size_t qsize) {
	struct queue *queue = NULL;
	
	queue = calloc(1, sizeof(*queue));
	if (queue == NULL)
		return NULL;
	
	assert(queue);
	
	queue->queue = (void**)calloc(1, qsize * sizeof(void*));
	if (queue->queue == NULL) {
		free(queue);
		return NULL;
	}

	queue->qsize = qsize;
	/* Initialize queue */	
	init_queue(queue);

	return queue;
}

void delete_queue(struct queue *queue)
{
	assert(queue != NULL);
	
	/* Release queue array memory */
	free(queue->queue);
	free(queue);
	queue = NULL;
}
