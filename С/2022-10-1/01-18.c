#include<stdio.h>

int pr(void)
{
    int a = getchar();
    if ((a >= (int)'1') && (a <= (int)'9'))
    {
        a = a - (int)'1' + 1;
    }
    else{
        if (a == (int)'a')
        {
            a = 10;
        }
        if (a == (int)'b')
        {
            a = 11;
        }
        if (a == (int)'c')
        {
            a = 12;
        }
        if (a == (int)'d'){
            a = 13;
        }
        if (a == (int)'e')
        {
            a = 14;
        }
        if (a == (int)'f')
        {
            a = 15;
        }
    }
    return a;
}
int main(void)
{
    int a, b, c, d, x, mask;
    a = pr();
    b = pr();
    c = pr();
    d = pr();
    mask = 1 << 3;
    x = (mask & a)| (mask & b) >> 1 | (mask & c) >> 2| (mask & d) >> 3;
    printf("%x", x); 
    mask = 1 << 2;
    x = (mask & a) << 1| (mask & b)| (mask & c) >> 1| (mask & d) >> 2;
    printf("%x", x);  
    mask = 1 << 1;
    x = (mask & a) << 2| (mask & b) << 1 | (mask & c)| (mask & d) >> 1;
    printf("%x", x); 
    mask = 1;
    x = (mask & a) << 3| (mask & b) << 2 | (mask & c) << 1| (mask & d);
    printf("%x", x);      
}