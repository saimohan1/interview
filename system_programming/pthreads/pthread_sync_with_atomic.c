#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#define THREAD_COUNT    2

static int x = 0;

static void *
thread_func(void *arg)
{
        for (int i = 0; i < 100000; i++) {
                //x++;
                __atomic_add_fetch(&x, 1, __ATOMIC_RELAXED);
        }

}

int main() {
        pthread_t tid[THREAD_COUNT];
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
        return 0;
}
