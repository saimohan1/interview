#include <stdio.h>
#include <string.h>

static void reverse(char *str, int s, int e)
{
	char tmp;

	while (s <  e) {
		tmp = str[s];
		str[s] = str[e];
		str[e] = tmp;
		s++;
		e--;
	}	
}

static void reverse_words(char *str)
{
	int start = 0;

	/* First reverse the string */
	reverse(str, 0, strlen(str) -1);

	/* Now Rverse word by Word */
	for (int end = 1; str[end] != '\0'; end++) {
		if (str[end] == ' ') {
			reverse(str, start, end - 1);	
			start = end + 1;
		}
	}

	reverse(str, start, strlen(str) -1);

	printf("Final:%s\n", str);

}

int main() {
	char str[] = "Saimohan Rao";
	reverse_words(str);

	return 0;
}
