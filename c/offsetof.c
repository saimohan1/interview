#include <stdio.h>
#include <stddef.h>

#define offsetoff(type, member)  (size_t)(&((type*)0)->member)

struct temp {
	int a;
	int d;
	char b;
};

int main() {
	/* Standard Function */
	printf("Offsetof b is:%ld\n", offsetof(struct temp, b));
	/* own implementation */
	printf("Offsetof b is:%ld\n", offsetoff(struct temp, b));
	
	return 0;
}
