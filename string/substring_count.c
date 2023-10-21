#include <stdio.h>
#include <string.h>

int
substring_occ(char *str, char *subs)
{
	int str_len = strlen(str);
	int subs_len = strlen(subs);
	int i,j, count = 0;
	
	for (i = 0; i < str_len; i++) {
		for (j = 0; j < subs_len; j++) {
			if (str[i + j] != subs[j])
				break;
		}
		if (j == subs_len) {
			count++;
		}	
	}
	
	return count;
}


int main() {
	char str[] = "Hello This is a Hello string of Hello";
	char subs[] = "Hello";

	printf("The of Substring Occurance is:%d\n", substring_occ(str, subs));
	return 0;
}
