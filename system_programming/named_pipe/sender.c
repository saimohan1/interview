#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
	char *buf = "Saimohan";
	int fd;

	fd = open("fifo1", O_WRONLY);
	write(fd, buf, sizeof(buf));
	printf("Successfully written by write\n");

	return 0;
}
