#include <stdio.h>

static int count_set_bits(int num)
{
	int count = 0;
	
	while (num) {
		if (num & 0x1)
			count++;
		num = num >> 1;
	}	
	return count;

}

int main() {
	int num;
	printf("Enter the number: ");
	scanf("%d", &num);	
	printf("%d\n",count_set_bits(num));
	return 0;

}
