#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#define THREAD_COUNT    2

static int x = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


static void *
thread_func(void *arg)
{
        for (int i = 0; i < 100000; i++) {
		pthread_mutex_lock(&mutex);
                x++;
		pthread_mutex_unlock(&mutex);
        }

}

int main() {
        pthread_t tid[THREAD_COUNT];
	
	pthread_mutex_init(&mutex, NULL);

        for (int i = 0; i < THREAD_COUNT; i++) {
                if (pthread_create(&tid[i], NULL, thread_func, NULL)) {
                        perror("pthrea_create");
                        assert(0);
                }
        }
        for (int i = 0; i < THREAD_COUNT; i++) {
                pthread_join(tid[i], NULL);
        }

        printf("Value of x is:%d\n", x);

	pthread_mutex_destroy(&mutex);
        return 0;
}
