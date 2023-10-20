#include <stdio.h>

int main() {
	int arr[] = {1,1,3,4,5,4,2,2,3,5,33};
	int len = sizeof(arr)/sizeof(arr[0]);
	int x = 0;
	int i;

	for (i = 0; i < len; i++)
		x = x ^ arr[i];

	printf("The single Appear number is:%d\n", x);
	return 0;
}
