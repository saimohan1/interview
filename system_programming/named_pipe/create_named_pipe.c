#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
	int ret = 0;
	
	ret = mkfifo("fifo1", 0777);	
	if (ret < 0) {
		perror("mkfifo");
		return -1;
	}

	printf("Successfully creaded mkfifo\n");
	
	return 0;
}	
