#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	char buf[100] = {0};
	int fd;

	fd = open("fifo1", O_RDONLY);
	read(fd, buf, sizeof(buf));
	printf("Successfully read: %s\n", buf);

	return 0;
}
