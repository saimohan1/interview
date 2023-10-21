#include <stdio.h>

/* Bubble Sort:
 * 	Reapetedly swap two adjacent elements
 * 	if they are in wrong order
 */

static void
bubble_sort(int *arr, int len)
{
	int counter = 1;
	/* The reason for counter is that every time the loop
	 * runs 1 less then the previous.
	 * first it runs for len -1, then len -2 then len -3 so on
	 * Because every time the last element would be in the correct
	 * position.
	 */
	while (counter < len) {
		for (int i = 0 ; i < len - counter; i++) {
			if (arr[i] > arr[i+1]) {
				int temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
			}
		}
		counter++;
	}
}

int main() {
	int arr[] = {12,45,23,51,19,8};
	int len = sizeof(arr) / sizeof(arr[0]);
	printf("Len:%d\n", len);	

	bubble_sort(arr, len);
	
	for (int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}	
	printf("\n");
}
