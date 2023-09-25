#include <stdio.h>

typedef void(*func_ptr)(int, int);

void add(int a, int b) {
	printf("Addition is :%d\n", a+b);
}

void substract(int a, int b) {
	printf("Subtraction is :%d\n", a-b);
}

int main() {
	/* First type of array of function pointer */
	void (*func_ptr1[])(int, int) = {add, substract};
	/* Second type of array of function pointer */
	func_ptr arr[] = {add, substract};
	int choice;
	int a = 5, b = 5;
	printf("Please enter you choice(0/1): ");
	scanf("%d", &choice);

	func_ptr1[choice](a,b);
	arr[choice](a,b);
	return 0;
}
