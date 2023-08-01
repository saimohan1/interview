#include <stdio.h>

static int is_power2(int num)
{
	if (num > 0) {
		if ((num & (num - 1)) == 0)
			return 1;
	}
	return 0;
}

int main() {
	int num = 5;
	
	printf("is power of 2: %s\n", is_power2(num) ? "Yes" : "No");

	return 0;
}
