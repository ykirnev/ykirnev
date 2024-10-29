#include <stdlib.h>
#include<stdio.h>
#include <string.h>



int main(void)
{
    char s[20002];
    int len_a, len_b;
    char operation;
    scanf("%s", s);
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '+' || s[i] == '*' || s[i] == '-')
        {
            len_a = i - 1;
            len_b = strlen(s) - len_a - 1;
            operation = s[i];
        }
    }
    if (len_a > len_b)
    {
        int a[len_a];
        int b[len_b];
        for (int i = len_a - 1; i >= 0; i--)
        {
            a[i] = s[i] - '0';
        }
        for (int i = len_a - 1; i >= 0; i--)
        {
            b[i] = s[len_a + 1 + i] - '0';
        }
    }
    else{
        int a[len_b];
        int b[len_a];
        b = (int*)malloc(len_a * sizeof(int));
        for (int i = len_a - 1; i >= 0; i--)
        {
            b[i] = s[i] - '0';
        }

        a = (int*)malloc(len_b * sizeof(int));
        for (int i = len_a - 1; i >= 0; i--)
        {
            a[i] = s[len_a + 1 + i] - '0';
        }
        int swap = len_a;
        len_a = len_b;
        len_b = swap;
    }
    
    for (int i = len_a - 1; i = 0; i--)
    {
        printf("%d", a[i]);
    }

    if (operation == '+')
    {
        int perenos = 0;
        for (int i = 0; i < len_b; i++)
        {
            int tmp_a = a[i];
            int tmp_b;
            if (i >= len_b)
            {
                tmp_b = 0;
            }
            else
            {
                tmp_b = b[i];
            }
            a[i] = tmp_a + tmp_b + perenos;
            if (a[i] >= 10)
            {
                a[i] = a[i] - 10;
                perenos = 1;
            }
            else
            {
                perenos = 0;
            }
        }
        if (perenos != 0)
        {
            a[len_a - 1] = a[len_a] + 10;
        }
        for (int i = len_a - 1; i = 0; i--)
        {
            printf("%d", a[i]);
        }
    }
}