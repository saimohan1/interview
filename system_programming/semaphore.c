#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int var = 0;
/* semaphore variable declaration */
sem_t semaphore;

static void *increment(void *arg)
{
	/* sem_wait()  decrements (locks) the semaphore pointed to by sem.
	 * If the semaphore's value is greater than zero, then the decrement
	 * proceeds, and the function returns, immediately.  If
         * the semaphore currently has the value zero, then the call blocks
	 * until either it becomes possible to perform the decrement 
	 * (i.e., the semaphore value rises above zero),  or  a  signal
         * handler interrupts the call.
	*/       
	sem_wait(&semaphore);
	for (int i = 0; i < 100000; i++) {
		var++;
	}
	printf("Value of i:%d\n", var);
	/* sem_post()  increments  (unlocks)  the  semaphore  pointed  to  by  sem.
	 * If the semaphore's value consequently becomes greater than zero,
	 * then another process or thread blocked in a
	 * sem_wait(3) call will be woken up and proceed to lock the semaphore.
       */
	sem_post(&semaphore);
	return NULL;
}

static void *decrement(void *arg)
{
	sem_wait(&semaphore);
	for (int i = 0; i < 100000; i++) {
		var--;
	}
	printf("Value of i:%d\n", var);
	sem_post(&semaphore);

	return NULL;
}

int main() {
	pthread_t tid[2];
	int ret = 0;

	sem_init(&semaphore, 0, 1);
	ret = pthread_create(&tid[0], NULL, 
		       increment, NULL);	
	if (ret) {
		printf("Failed to create pthread\n");
		return -1;
	}
	
	ret = pthread_create(&tid[1], NULL, 
		       decrement, NULL);	
	if (ret) {
		printf("Failed to create pthread\n");
		return -1;
	}

	pthread_join(tid[0], NULL);	
	pthread_join(tid[1], NULL);	
	sem_destroy(&semaphore);

	printf("\n");
	return 0;
}
