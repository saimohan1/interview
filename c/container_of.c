#include <stdio.h>
#include <stdint.h>
#include <stddef.h>


/* First way of container of*/
//#define container_of(ptr, type, member)	(type*)((uintptr_t)ptr - offsetof(type, member))	


/* Second way container of */
//#define container_of(ptr, type, member)	({\
//		void *__mptr = (void *)ptr;	\
//		(type*)(__mptr - offsetof(type, member));})

/* 3rd method */
//#define container_of(ptr, type, member)	({\
//		const typeof(((type*)0)->member) *__mptr = (ptr);	\
//		(type*)((char*)__mptr - offsetof(type, member));})


#define container_of(ptr, type, member)	({	\
		(type*)((void*)(ptr) - offsetof(type, member));})

struct temp {
	int a;
	float b;
	char c;
};

int main() {
	struct temp test;
	char *c = &test.c;

	printf("Address of test: %p\n", &test);
	printf("Address of c: %p\n", c);


	printf("Address of test using container of and c variable:%p\n",
			container_of(c, struct temp, c));
	return 0;
}
