#include<stdio.h>


int main (void)
{
    int n, flag = 1;
    int sgn_1 = 0, sgn_2 = 0, c = 0;
    scanf("%d", &n);
    int x[n], y[n];
    for(int i = 0; i < n; i++)
    {
        scanf("%d %d", &x[i], &y[i]);
        if (i + 1 == 1)
        {
            if (x[i] != 0) 
            {
                flag = 0;
                printf("тут 1");
            } 
        }
        else if ((i + 1) == n / 2)
        {
            if (x[i] != 0) 
            {
                flag = 0;
                printf("тут 2");
                printf("%d", &)
            }   
        }
        else if (i + 1 == 2)
        {
            if (x[i] > 0)
            {
                sgn_1 = 1;
                sgn_2 = -1;
            }
            else
            {
                sgn_1 = - 1;
                sgn_2 = 1;
            }
        }
        else if ((i + 1) < n / 2)
        {
            if (sgn_1 * x[i] < 0)
            {
                flag = 0;
                printf("тут 3");
            }
        }
        else if (i + 1 > n / 2)
        {
            if (sgn_2 * x[i] < 0)
            {
                flag = 0;
                printf("тут 4");
            }   
        }

        if (i + 1 > n / 2)
        {
            if ((x[i] + x[n - i] == 0) && (y[i]  == y[n - i]))
            {
                c = c + 1;
            }
            else
            {
                flag = 0;
            }
        }
    }
    if (flag == 1)
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
    printf("%d", sgn_1);
}