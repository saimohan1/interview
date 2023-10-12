#define _GNU_SOURCE
#include <stdio.h>
#include <sched.h>

int main() {
	int core = sched_getcpu();
	printf("The current core is:%d\n", core);
	return 0;
}
