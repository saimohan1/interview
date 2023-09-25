#include <stdio.h>
#include <unistd.h>

int main() {
	int page_size = sysconf(_SC_PAGE_SIZE);
	int num_pages = sysconf(_SC_PHYS_PAGES);

	printf("The page size is: %d\n", page_size);	
	printf("The number of pages are:%d\n", num_pages);	
	return 0;
}
