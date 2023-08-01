#include <stdio.h>
#include <stdint.h>

int main() {
	uint8_t num = 1;
	uint8_t res;
	
	for (int i= 0; i < 8; i++) {
		res = (res << 1) | (num & 1);
		num = num >> 1;
	}	

	printf("%d\n", res);
	return 0;
}
