#include <stdio.h>
#include <stdarg.h>

int variable_args(int num_args, ...)
{
	va_list args;
	
	va_start(args, num_args);
	for (int i = 0; i < num_args; i++) {
		int x = va_arg(args, int);
		printf("%d\n", x);
	}	

	va_end(args);
}

int main() {
	
	variable_args(2, 33, 44, 55);	

	return 0;
}
