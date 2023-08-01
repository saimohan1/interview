#include <stdio.h>
#include <stdlib.h>

int main() {
	char *string = NULL;
	string = (char *)calloc(1, sizeof(20));
	
	snprintf(string, sizeof("saimohan rao"), "%s", "saimohan rao");
	printf("string: %s\n", string);

	char *first = string;
	char *last = string;

	while (*last != '\0')
		last++;
	
	last--;

	while (first < last) {
		int temp = *first;
		*first = *last;
		*last = temp;
		first++;
		last--;
	}
	
	printf("string:%s\n", string);
	
	free(string);
	return 0;
}
