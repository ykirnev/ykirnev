#include <stdio.h>
#include <stdlib.h>

long int** proisv(long int**a, long int**b, long int k, long int p)
{
    long int **Mas;
    Mas = (long int **)malloc(k * sizeof(long int *));
    for (int i = 0; i < k; i++)
    {
        Mas[i] = (long int*)malloc(10000* sizeof(long int));
    }
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            Mas[i][j] = 0;
            for (int c = 0; c < k; c++)
            {
                Mas[i][j] = Mas[i][j] + (a[i][c] * b[c][j]) % p;
            }
            Mas[i][j] = Mas[i][j] % p;
        }
    }
    for (int i = 0; i<k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            a[i][j] = Mas[i][j];
        }   
    }
    for (int i = 0; i < k; i++)
    {
        free(Mas[i]);
    }
    free(Mas);
    return a;
}

/*
int** fast_pow(int** a, int b, int k, int p)
{
    if (b == 0)
    {
        int** x;
        x = (int **)malloc(k * sizeof(int *));
        for (int i = 0; i < k; i++)
        {
            x[i] = (int*)malloc(k* sizeof(int));
            for(int j = 0; j < k; j++)
            {
                x[i][j] = 0;
                if (i == j)
                {
                    x[i][j] = 1;
                }
            }
        }
        return x;
    } 
    else if (b == 1)
    {
        return a;
    }
    else if (b % 2 == 0)
    {
        return proisv(fast_pow(a, b / 2, k, p), fast_pow(a, b / 2, k, p), k, p);
    }
    else if (b % 2 == 1)
    {
        return (proisv(fast_pow(a, b - 1, k, p), a, k, p));
    }
    int** x;
        x = (int **)malloc(k * sizeof(int *));
        for (int i = 0; i < k; i++)
        {
            x[i] = (int*)malloc(k* sizeof(int));
            for(int j = 0; j < k; j++)
            {
                x[i][j] = 0;
                if (i == j)
                {
                    x[i][j] = 1;
                }
            }
        }
    return x;
}
*/

long int** fast_pow(long int**a, long int b, long int k, long int p)
{
    long int** x;
    x = (long int **)malloc(k * sizeof(long int *));
    for (int i = 0; i < k; i++)
    {
        x[i] = (long int*)malloc(k* sizeof(long int));
        for(int j = 0; j < k; j++)
        {
            x[i][j] = 0;
            if (i == j)
            {
                x[i][j] = 1;
            }
        }
    }
    while (b > 0)
    {
        if (b % 2 == 1)
        {
            x = proisv(x, a, k, p);
            b = b - 1;
        }
        else{
            a = proisv(a, a, k, p);
            b = b / 2;
        }

    }
    return x;
}

int main (void)
{
    long int k, n, p;
    scanf("%ld %ld %ld", &k, &n, &p);
    long int*F_first;
    F_first = (long int*)malloc(k* sizeof(long int));
    for(int i = 0; i < k; i++)
    {
        scanf("%ld", &F_first[i]);
    }
    long int **a;
    a = (long int **)malloc(k * sizeof(long int *));
    for (int i = 0; i < k; i++)
    {
        a[i] = (long int*)malloc(k* sizeof(long int));
    }
    for(int i = 0; i < k; i++)
    {
        scanf("%ld", &a[0][i]);
    }
    for(int i = 1; i < k; i++)
    {
        a[i][i - 1] = 1;
    }
    a = fast_pow(a, n - k, k, p);
    if (n == k)
    {
        printf("%ld", F_first[0] % p);
        return 0;
    }
    if (n < k)
    {
        printf("%ld", F_first[k - n] % p);
        return 0;

    }
    long int answer = 0;
    for(int i = 0; i < k; i++)
    {
       answer = answer + (F_first[k - i - 1] * a[0][i]);
    }
    printf("%ld", answer % p);
    return 0;
}