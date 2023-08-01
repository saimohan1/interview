#include <stdio.h>

int main() {
	int num = 5;
	int pos = 4;

	num  = num | (1 << pos);
	printf("num :%d\n", num);

	return 0;
}
