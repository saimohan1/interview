#include <stdio.h>
#include <threads.h>
#include <stdatomic.h>

//Declaring global variables to
//be shared betweeen threads
 
atomic_int atomic_count = 0;	//atomic variable
int non_atomic_count = 0;			//non-atomic variable
 
int func(void* input)
{
    for(int n = 0; n < 1000; ++n) {
        atomic_fetch_add(&atomic_count, 1); // atomic updation
        ++non_atomic_count; // non-atomic updation
    }
    
    return 0;
}
 
int main(void)
{
    thrd_t threads[10];
    for(int i = 0; i < 10; i++)
        thrd_create(&threads[i], func, NULL);
        
    for(int i = 0; i < 10; i++)
        thrd_join(threads[i], NULL);
 
    printf("The atomic counter is: %d\n", atomic_count);
    printf("The non-atomic counter is: %d\n", non_atomic_count);
}
