#include <stdio.h>

static void convert_le_to_be(int num)
{
	

//	num = (num & 0xFF) << 24 | (num & 0xFF00) << 8 | (num & 0xFF00)  >> 8 | (num & 0xFF000000) >> 24;
	num = ((num >> 24) & 0xFF) | ((num >> 8) & 0xFF00) | ((num << 8) & 0xFF0000) | ((num << 24) & 0xFF000000);

	printf("0x%x\n", num);

}

int main() {
	int num = 0xFA32DE12;
	printf("Orinal Number:0x%x\n", num);
	convert_le_to_be(num);
	return 0;
}
