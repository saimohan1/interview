#include <stdio.h>
#include <limits.h>

int main() {
	int arr[] = {1,4,5,2,9,6,3,7,8};
	int size = sizeof(arr)/sizeof(arr[0]);
	int l = arr[0];
	int s = INT_MIN;
	for (int i = 1; i < size; i++) {
		if (arr[i] > l) {
			s = l;
			l = arr[i];
		} else if (arr[i] < l && arr[i] > s) {
			s = arr[i];
		}	
	}	
	
	printf("Second:%d\n", s);
	return 0;
}
