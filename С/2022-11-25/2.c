#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, size_max;
    scanf("%d", &n);
    long int **Mas_tmp;
    long int **Mas_max;
    long int sled_tmp = 0, sled_max;
    int size_tmp;
    scanf("%d", &size_tmp);
    size_max = size_tmp;
    Mas_tmp = (long int**)malloc(size_tmp * sizeof(long int*));
    Mas_max = (long int**)malloc(size_tmp * sizeof(long int*));
    for (int j = 0; j < size_tmp; j++)
    {
        Mas_tmp[j] = (long  int*)malloc(size_tmp * sizeof(long int));
        Mas_max[j] = (long  int*)malloc(size_tmp * sizeof(long int));
        for(int k = 0; k < size_tmp; k++)
        {
            long int x;
            scanf("%ld", &x);
            Mas_tmp[j][k] = x;
            Mas_max[j][k] = x;
        
        }
    }
    for (int i = 0; i < size_tmp; i++)
    {
        sled_tmp = sled_tmp + Mas_tmp[i][i];
    }
    sled_max = sled_tmp;
    for(int j = 0; j < size_tmp; j++)
    {
        free(Mas_tmp[j]);
    }
    free(Mas_tmp);
    for(int i = 1; i < n; i++)
    {
        scanf("%d", &size_tmp);
        Mas_tmp = (long int**)malloc(size_tmp * sizeof(long int*));
        for (int j = 0; j < size_tmp; j++)
        {
            Mas_tmp[j] = (long  int*)malloc(size_tmp * sizeof(long int));
            for(int k = 0; k < size_tmp; k++)
            {
                long int x;
                scanf("%ld", &x);
                Mas_tmp[j][k] = x;
            }
        }
        sled_tmp = 0;
        for (int j = 0; j < size_tmp; j++)
        {
            sled_tmp = sled_tmp + Mas_tmp[j][j];
        }
        if (sled_tmp > sled_max)
        {
            for(int j = 0; j < size_max; j++)
            {
                free(Mas_max[j]);
            }
            free(Mas_max);
            sled_max = sled_tmp;
            size_max = size_tmp;
            Mas_max = (long int**)malloc(size_max * sizeof(long int*));
            for (int j = 0; j < size_tmp; j++)
            {
                Mas_max[j] = (long  int*)malloc(size_max * sizeof(long int));
                for(int k = 0; k < size_max; k++)
                {
                    Mas_max[j][k] = Mas_tmp[j][k] ;
                }
            }

        }
        for(int j = 0; j < size_tmp; j++)
        {
            free(Mas_tmp[j]);
        }
        free(Mas_tmp);
    }
    for(int i = 0; i < size_max; i++)
    {
        for (int j = 0; j < size_max; j++)
        {
            printf("%ld ", Mas_max[i][j]);
        }
        printf("\n");
    }
}