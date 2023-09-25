#include <stdio.h>
#include <stdbool.h>

static bool linear_search_num(int *arr, int len, int num)
{
	bool found = false;

	for (int i = 0 ; i < len; i++) {
		if (arr[i] == num) {
			found = true;
			break;
		}
	}

	return found;
}

int main() {
	int arr[] = {1,2,3,4,54,32,52,98,12,43};
	int len = sizeof(arr)/sizeof(arr[0]);
	int number;

	printf("The Array is\n");
	for(int i = 0; i < len; i++) {
		printf("%d ", arr[i]);
	}
	
	printf("\n");

	printf("Please enter the number to search: ");
	scanf("%d", &number);

	printf("The number is %s in the array\n", linear_search_num(arr, len, number) == true ? "present" : "not present");
		
	return 0;
}
