
#ifndef __QUEUE_H__
#define __QUEUE_H__
struct queue {
	void **queue;
	uint32_t head;
	uint32_t tail;
	size_t qsize;
	bool qfull;
	bool qempty;
};

bool is_queue_full(struct queue *queue);
bool is_queue_empty(struct queue *queue);
int enqueue(struct queue *queue, void *data);
void* dequeue(struct queue *queue);
struct queue *create_queue(size_t qsize);
void delete_queue(struct queue *queue);
#endif
