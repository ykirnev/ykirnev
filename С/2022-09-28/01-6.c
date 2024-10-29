#include <stdio.h>

int main(void)
{
    int t;
    unsigned int x;
    int n;
    scanf("%u", &x);
    scanf("%d", &n);
    x = (x >> n) | (x << (32 - n));
    printf("%u", x);
    return 0; 
}