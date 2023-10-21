#include <stdio.h>

int main() {
	int num;
	printf("Enter the number: ");
	scanf("%d", &num);	
	printf("%d\n",__builtin_popcount(num));
	return 0;

}
