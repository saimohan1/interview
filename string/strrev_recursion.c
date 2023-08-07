#include <stdio.h>
#include <string.h>


static void reverse(char *str, int s, int e)
{
	if (s < e) {
		char temp = str[s];
		str[s] = str[e];
		str[e] = temp;
		reverse(str, s + 1, e - 1);
	}
}


int main() {
	char str[] = "Saimohan Rao";
	int len = strlen(str) - 1;

	reverse(str, 0, len); 

	printf("%s\n", str);
	return 0;
}
