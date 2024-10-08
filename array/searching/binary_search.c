#include <stdio.h>
#include <stdbool.h>

/* Binary Search */
/* Time Complexity: O(logn) */

static bool
binary_search_num(int *arr, int len, int num)
{
	bool found = false;
	int start = 0;
	int end = len - 1;
	int mid;

	while (start <= end) {
		mid = (start + end)/2;
		if (arr[mid] == num) {
			found = true;
			break;
		}

		if (num < arr[mid]) {
			end = mid - 1;
		} else {
			start = mid + 1;
		}

	}
	
	return found;
}

int main() {
	//int arr[] = {1,2,3,4,54,32,52,98,12,43};
	int arr[] = {1,13,22,35,48,53,66,71,89,99};
	int len = sizeof(arr)/sizeof(arr[0]);
	int number;

	printf("The Array is\n");
	for(int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	
	printf("\n");

	printf("Please enter the number to search: ");
	scanf("%d", &number);

	printf("The number is %s in the array\n", binary_search_num(arr, len, number) == true ? "present" : "not present");
		
	return 0;
}
