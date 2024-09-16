#include <stdio.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

#define ALLOC_SIZE      (2 * 1024 * 1024)

int main() {
        void *memory = NULL;
        char *ptr;

        memory = mmap(NULL, ALLOC_SIZE, PROT_READ | PROT_WRITE,  MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB, -1 , 0);
        if (!memory) {
                perror("mmap");
                return ENOMEM;
        }

        printf("Memory allocated successfully using mmap. %p\n", memory);

	/* Pinning Allocated Memroy */
        if (mlock(memory, ALLOC_SIZE)) {
                perror("mlock");
                goto done;
        }

done:
        munmap(memory, ALLOC_SIZE);
        return 0;
}

