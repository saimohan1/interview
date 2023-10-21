#include <stdio.h>
#include <string.h>

int main() {
	char str[] = "Saimohan Rao is a Good Boy";
	
	printf("Original String is:%s\n", str);

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == ' ') {
			for (int j = i; str[j]; j++) {
				str[j] = str[j + 1];
			}
		}
	}

	printf("New String is:%s\n", str);

	return 0;
}
