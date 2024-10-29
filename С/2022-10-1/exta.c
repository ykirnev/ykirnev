#include <stdio.h>


int main(void)
{
    int stepen[100], sum_stepen[100];
    int i = 1, n, x, counter;
    for (int n = 1; n < 1000; n ++){
        stepen[0] = 1;
        for(long int j = 1; j <= 3000000000; j = j * 3)
        {
            stepen[i] = j;
            i ++;
        }
        int len = i;
        sum_stepen [0] = 0;
        for (i = 1; i <= len; i ++)
        {
            sum_stepen[i] = sum_stepen[i - 1] + stepen[i];
        }
        i = 0;
        while (sum_stepen[i] < n)
        {
            i ++;
        }
        x = sum_stepen[i];
        counter = i;
        for (int j = i; j > 0; j --)
        {
        
            if ((x - 2 * stepen[j]) >= n)
            {
                x = x - 2 * stepen[j];
            }
            else if ((x - stepen[j]) >= n)
            {
                x = x - stepen[j];
                counter = counter - 1;
            }
        }
        if (x == n){
            x = x + 1;
        }
        else{
            printf("%d -1\n",n);
        }
    }

}