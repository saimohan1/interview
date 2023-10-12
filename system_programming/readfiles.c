#include <stdio.h>
#include <dirent.h>

int main() {
	DIR *dir;
	struct dirent *entry;
	if ((dir = opendir("/proc")) == NULL) {
		printf("error for opendir\n");
	} else {
		while ((entry = readdir(dir)) != NULL) {
			printf("%s\n", entry->d_name);
		}
	}	
	return 0;
}
