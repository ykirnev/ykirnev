#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned int x;
    scanf("%u", &x);
    unsigned int b = x;
    b -= 1;
    x ^= b;
    x += 1;
    if (x == 0)
    {
        x = (1 << 31) + (x >> 1);
    }
    else{
        x = x >> 1;
    }
    printf("%u\n", x);    
}