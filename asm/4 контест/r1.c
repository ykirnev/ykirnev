#include <stdlib.h>
#include <stdio.h>
//Кирнев Юра 105 группа
unsigned int f(unsigned int x);
unsigned int rec(unsigned int x);

unsigned int rec(unsigned int x)
{
    x = x - 1;
    unsigned int a = f(x);
    x = 3 * a; 
    return x;
}

unsigned int f(unsigned int x)
{
    if (x == 0)
    {
        return 1;
    }
    return rec(x);
}

int main(void){
    unsigned int x;
    scanf("%u", &x);
    x = f(x);
    printf("%u\n", x);
    return 0;
}