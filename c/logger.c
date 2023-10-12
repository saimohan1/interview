#include <stdio.h>
#include <time.h>
#include <string.h>

#define log(fmt, ...)	printf("[%s:%d]	%s - " fmt "", __func__, __LINE__, timestamp(), ##__VA_ARGS__);

const char *timestamp() {
	time_t now = time(NULL);
	struct tm *timestruct = localtime(&now);
	char *time_str = asctime(timestruct);
	time_str[strlen(time_str)-1] = '\0';
	return time_str;
}


int main() {

	log("This is a logger print\n");
	log("This is a logger print with value as :%d\n", 10);

	return 0;
}
