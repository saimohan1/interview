#include <stdio.h>

int main() {
	unsigned int num = 0x1;
	char *ptr = (char*)&num;

	if (*ptr == 0x1) {
		printf("This is little endian machine\n");
	} else {
		printf("This is Big endian machine\n");
	}
}
