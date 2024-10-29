#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    int a = -1 >> 31;
    printf("%d", a);
}