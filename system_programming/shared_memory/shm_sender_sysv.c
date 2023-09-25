#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>


int main() {
	char *buf = "This is is message for shared memory";
	void *shared_memory = NULL;
	int id;

	id = shmget((key_t)1122, 1024, 0666 | IPC_CREAT);
	if (id < 0) {
		perror("shmget");
		return -1;
	}
	
	shared_memory = shmat(id, NULL, 0);
	if (shared_memory == NULL) {
		perror("shmat");
		return -1;
	}
	
	strcpy(shared_memory, buf);
	
	printf("Successfuly written the message to the sharedmemory buffer: %s\n", buf);	


	return 0;
}
