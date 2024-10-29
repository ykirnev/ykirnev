#include <stdio.h>


int main(void)
{
    int stepen[100], sum_stepen[100];
    int i = 1, n, x, counter;
    scanf("%u", &n);
    stepen[0] = 1;
    for(long int j = 1; j <= 1000000000; j = j * 3)
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
    int right_weight = x;
    counter = i;
    for (int j = i; j > 0; j --)
    {
    
        if ((x - 2 * stepen[j]) >= n)
        {
            x = x - 2 * stepen[j];
            right_weight = right_weight - stepen[j];
        }
        else if ((x - stepen[j]) >= n)
        {
            x = x - stepen[j];
            right_weight = right_weight - stepen[j];
            counter = counter - 1;
        }
    }
    if ((x == n) && (right_weight <= 1000000))
    {
        printf("%u", counter);
    }
    else{
        printf("-1");
    }
    


}