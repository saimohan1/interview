/* Write a c program to reset range of bits in a 32bit unsigned intiget */
#include <stdio.h>
#include <stdint.h>

static uint32_t
reset_bits(uint32_t num, int start, int end)
{
        uint32_t mask = 0;
        for(int i = 0; i < 32; i++) {
                if (i >= start && i <= end) {
                        printf("Setting i:%d bit\n", i);
                        mask |= 1 << i;
                }
        }

        return num = num & (~(mask));
}

int main() {
        uint32_t num = 0xFFFFFFFF;

        printf("The final numer:%x\n",reset_bits(num, 6, 9));
}
