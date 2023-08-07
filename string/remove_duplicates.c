#include <stdio.h>
#include <stdbool.h>

int main() {
	char str[] = "Saimohan Rao";
	int len = sizeof(str) -1;
	int index = 0;

	for (int i =0;i < len; i++) {
		int j;
		for (j = 0; j < i; j++) {
			if (str[i] == str[j]) {
				break;
			}
		}
		if (j == i) {
			str[index++] = str[i];
		}
	}
	
	str[index] = '\0';

	printf("str:%s\n", str);
	return 0;
}
