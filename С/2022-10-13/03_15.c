#include<stdio.h>
int main (void)
{
    int n, x, y, sum_x1 = 0, sum_y1 = 0, x1 = 0, y1 = 0, x2 = 0, y2 = 0, sum_x2 = 0, sum_y2 = 0, sgn1 = 0, sgn2 = 0, flag = 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &x);
        scanf("%d", &y);
        if (i == 1)
        {
            x1 = x;
            y1 = y;
        }
        else if(i == (n / 2 + 1))
        {
            x2 = x;
            y2 = y;
        }
        else if (i < n/2 + 1){
            sum_x1 = sum_x1 + x;
            sum_y1 = sum_y1 + y;
            if (i == 2)
            {
                if(x > 0)
                {
                    sgn1 = 1;
                }
                else{
                    sgn1 = -1;
                }
            }
            else{
                if(x * sgn1 < 0)
                {
                    flag = 0;
                }
            }
        }
        else{
            sum_x2 = sum_x2 + x;
            sum_y2 = sum_y2 + y;
            if (i == n/2 + 2)
            {
                if(x > 0)
                {
                    sgn2 = 1;
                }
                else{
                    sgn2 = -1;
                }
            }
            else{
                if(x * sgn2 < 0)
                {
                    flag = 0;
                }
            }
        }
    }
    if ((sum_x1 + sum_x2 == 0) && (x1 + x2 == 0) && (y1 + y2 == 0) && (flag == 1))
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }
    if (flag == 0)
    {
        printf("No");
    }
    else
    {
        printf("Yes");
    }
    return 0;
}