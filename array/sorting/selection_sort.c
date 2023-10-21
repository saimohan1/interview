#include <stdio.h>

/* Selection Sort:
 * 	Find the minimum element in unsorted array
 * 	and swap it with element at beginning
 */

static void
selection_sort(int *arr, int len)
{
	for (int i = 0; i < len - 1; i++) {
		for (int j = i + 1; j < len; j++) {
			if (arr[j] < arr[i]) {
				int temp = arr[j];
				arr[j] = arr[i];
				arr[i] = temp;	
			}
		}
	}
}

int main() {
	int arr[] = {12,45,23,51,19,8};
	int len = sizeof(arr) / sizeof(arr[0]);
	printf("Len:%d\n", len);	

	selection_sort(arr, len);
	
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}	
	printf("\n");
}
