#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char *str = NULL;
	str = malloc(sizeof(10));
	if (str == NULL) {
		printf("Failed to allocate memroy\n");
		return -1;
	}
	memset(str, 0, sizeof(*str));
	snprintf(str, 20, "This is a message");
	printf("String is :%s\n", str);
	
	realloc(str, sizeof(20));
	snprintf(str, 20, "This is a message");
	printf("String is :%s\n", str);

	free(str);	
	return 0;

}
