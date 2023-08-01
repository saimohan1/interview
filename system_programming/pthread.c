#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

static int is_upper_case = 1;

static void *print_upper_case(void *arg)
{
	for (int i = 'A';  i <= 'Z'; i++) {
		pthread_mutex_lock(&mutex);
		while(!is_upper_case)
			pthread_cond_wait(&cond, &mutex);
		
		printf("%c", i);
		fflush(stdout);
		is_upper_case = 0;	
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

static void *print_lower_case(void *arg)
{
	for (int i = 'c';  i <= 'z'; i++) {
		pthread_mutex_lock(&mutex);
		while(is_upper_case)
			pthread_cond_wait(&cond, &mutex);
		
		printf("%c", i);
		fflush(stdout);
		is_upper_case = 1;	
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main() {
	pthread_t tid[2];
	int ret = 0;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);

	ret = pthread_create(&tid[0], NULL, 
		       print_upper_case, NULL);	
	if (ret) {
		printf("Failed to create pthread\n");
		return -1;
	}
	
	ret = pthread_create(&tid[1], NULL, 
		       print_lower_case, NULL);	
	if (ret) {
		printf("Failed to create pthread\n");
		return -1;
	}

	pthread_join(tid[0], NULL);	
	pthread_join(tid[1], NULL);	
	
	printf("\n");
	return 0;
}
