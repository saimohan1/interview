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
	char *str = "This is a test string to print number of vowels";
	char *b = str;
	int count = 0;	

	while (*str != '\0') {
		count += is_a_vowel(*str) ? 1 : 0;
		str++;
	}
	
	printf("The of vovels in the string: %s are %d\n", b, count);

	return 0;
}
