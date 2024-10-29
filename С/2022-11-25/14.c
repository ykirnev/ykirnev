#include <stdio.h>
#include <stdlib.h>

int step(int n)
{
    int a = 1;
    for(int i = 0; i < n; i++)
    {
        a = a * 10;
    }
    return a;
}
int prime(int a)
{
    if (a <= 1)
    {
        return 0;
    }
    int i = 2;
    while (i * i <= a)
    {
        if (a % i == 0)
        {
            return 0;
        } 
        i++;
    }
    return 1;
}

int main(void)
{
    int n;
    scanf("%d", &n);
    int**Mas;
    Mas = (int**)malloc(n * sizeof(int*));
    Mas[0] = (int*) malloc(5 * sizeof(int));
    Mas[0][0] = 2;
    Mas[0][1] = 3;
    Mas[0][2] = 5;
    Mas[0][3] = 7;
    Mas[0][4] = 0;
    int new;
    int counter = 5;
    int prev = 4;
    for (int i = 1; i < n; i++)
    {
        prev = counter;
        counter = 0;
        Mas[i] = (int*)malloc(10000 * sizeof(int));
        for(int j = 0; j < 1000; j++)
        {
            Mas[i][j] = 0;
        }
        for (int k = 0; k < prev; k++)
        {
            for(int j = 1; j < 10; j++)
            {
                new = Mas[i - 1][k] * 10 + j;
                if (prime(new) == 1)
                {
                    Mas[i][counter] = new;
                    counter++;
                }
            }
        } 
    }
    int i = 0;
    while (Mas[n - 1][i] != 0)
    {
        if ((0 < (Mas[n - 1][i] / step(n - 1))) && ((Mas[n - 1][i] / step(n - 1)) < 10))
        printf("%d ", Mas[n - 1][i]);
            i++;
    }
    for(int i = 0; i < n; i++)
    {
        free(Mas[i]);
    }
    free(Mas);


}