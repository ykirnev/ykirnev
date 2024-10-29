#include <stdio.h>
int stolb(char c)
{
    c = c - 'a' + 1;
    c = (int)c;
    return c;
}
int mx(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    return b;
}
int mn(int a, int b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}

int main(void)
{
    int a[8][8];
    char c1, c2;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            a[i][j] = 0;
        }

    }
    while ((c1 != '\n') || (c1 != EOF))
    {
        c1 = getchar();
        if ((c1 == '\n') || (c1 == EOF))
        {
            break;
        }
        c1 = stolb(c1);
        c2 = (int)(getchar() - '0');  
        a[c1 - 1][c2 - 1] = 1;
        for (int i = mx(0, c1 - 2); i <= mn(7, c1); i ++)
        {
            for (int j = mx(0, c2 - 2); j <= mn(7, c2); j ++)
            {
                a[i][j] = 1;
            }
        }
    }
    int counter = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (a[i][j] == 0)
            {   
                counter ++; 
            }   
        }
    }
    printf("%d", counter);
}