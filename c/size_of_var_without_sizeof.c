#include <stdio.h>

int main() {
	int a;
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	printf("Sizeof array:%lu\n", sizeof(arr));
	printf("sizeof array:%lu\n", (char*)(&arr + 1) - (char*)&arr);
	printf("Size is:%lu\n", (char*)(&a + 1) - (char*)&a);
	return 0;
}
