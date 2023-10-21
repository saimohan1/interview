#include <stdio.h>


int main() {
	char str[] = "Saimohan";
	char str1[] = "SAIMOHAN";

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'a' && str[i] <= 'z')	
			str[i] = str[i] - 32; 
	}
	
	for (int i = 0; str1[i] != '\0'; i++) {
		if (str1[i] >= 'A' && str1[i] <= 'Z')	
			str1[i] = str1[i] + 32; 
	}

	printf("%s\n", str);
	printf("%s\n", str1);
	return 0;
}
