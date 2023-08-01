#include <stdio.h>

int main() {
	int arr[] = {1,2,3,4,5,7,8,9};
	int size = sizeof(arr)/sizeof(arr[0]);
	int sum = 0;	
	size += 1;
	sum = (size * (size + 1))/2;

	printf("Sum:%d\n", sum);	
	
	for (int i =0; i < size-1; i++) {
		sum -= arr[i];
	}

	printf("Missing number is:%d\n", sum);
	return 0;
}
