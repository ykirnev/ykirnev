#include<stdio.h>

int main(void)
{
    unsigned int a11, a12, a21, a22, b1, b2, x, y, mask;
    int flag = 0;
    scanf("%u %u %u %u %u %u", &a11, &a12, &a21, &a22, &b1, &b2);
    x = 0;
    y = 0;
    flag = -1;
    for(int i = 0; i < 32; i ++)
    {
        mask = 1 << i;
        for (unsigned int x_i = 0; x_i <= 1; x_i ++)
        {
            for (unsigned int y_i = 0; y_i <= 1; y_i ++)
            {
                if ((((a11 & mask) & (x_i << i)) ^ ((a12 & mask) & (y_i << i))) == (b1 & mask))
                {
                    if ((((a21 & mask) & (x_i << i)) ^ ((a22 & mask) & (y_i << i))) == (b2 & mask))
                    {
                    
                        if (flag == (i - 1))
                        {
                            flag ++;
                            x = x | (x_i << i);
                            y = y | (y_i << i);
                        }
                    }
                }
            }
        }
    }
    if (flag == 31)
    {
        printf("Yes\n");
        printf("%u %u", x, y);
    }
    else{
        printf("No");
    }
}