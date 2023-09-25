#include <stdio.h>
#include <pthread.h>

int var = 0;

pthread_spinlock_t spinlock;

static void *increment(void *arg)
{
	/* The  pthread_spin_lock() function locks the spin lock referred to by lock.
	 * If the spin lock is currently unlocked, the calling thread acquires the lock immediately.
	 * If the spin lock is currently locked by another thread, the calling thread spins
	 * testing the lock until it becomes available, at which point the calling thread acquires the lock.
	 */
	pthread_spin_lock(&spinlock);
	for (int i = 0; i < 100000; i++) {
		var++;
	}
	printf("Value of i:%d\n", var);
	/* The pthread_spin_unlock() function unlocks the spin lock referred to lock.
	 * If any threads are spinning on the lock, one of those threads will then acquire the lock.
	 */
	pthread_spin_unlock(&spinlock);
	return NULL;
}

static void *decrement(void *arg)
{
	pthread_spin_lock(&spinlock);
	for (int i = 0; i < 100000; i++) {
		var--;
	}
	printf("Value of i:%d\n", var);
	pthread_spin_unlock(&spinlock);

	return NULL;
}

int main() {
	pthread_t tid[2];
	int ret = 0;

	/* Initialize the spinlock */
	pthread_spin_init(&spinlock, PTHREAD_PROCESS_PRIVATE);

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

	/* Destroy spin lock */
	pthread_spin_destroy(&spinlock);

	printf("\n");
	return 0;
}
