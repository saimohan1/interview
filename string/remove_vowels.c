#include <stdio.h>
#include <stdbool.h>

static bool is_a_vowel(char ch)
{
	if (ch == 'a' || ch == 'e' || ch == 'i' ||
		ch == 'o' || ch == 'u') {
		return true;
	} 

	return false;
}

int main() {
	char str[] = "This is a test string to print number of vowels";

	for (int i = 0; str[i]; i++ ){
		if (is_a_vowel(str[i])) {
			for (int j = i; str[j]; j++) {
				str[j] = str[j+1];
			}
		}
	}

	printf("The of vovels in the string: %s\n", str);

	return 0;
}
