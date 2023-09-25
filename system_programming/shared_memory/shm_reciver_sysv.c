#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>


int main() {
	char buf[1024] = {0};
	void *shared_memory = NULL;
	int id;

	id = shmget((key_t)1122, 1024, 0666);
	if (id < 0) {
		perror("shmget");
		return -1;
	}
	
	shared_memory = shmat(id, NULL, 0);
	if (shared_memory == NULL) {
		perror("shmat");
		return -1;
	}
	
	strcpy(buf, shared_memory);
	
	printf("Successfuly Read the message to the sharedmemory buffer: %s\n", buf);	


	return 0;
}
