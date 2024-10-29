#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    long int n;
    scanf("%ld", &n);
    long int **Mas_R;
    long int **Mas_C;
    Mas_R = (long int**)malloc(n * sizeof(long int*));
    Mas_C = (long int**)malloc(n * sizeof(long int*));
    for (long int i = 0; i < n; i++)
    {
        Mas_R[i] = (long  int*)malloc(n * sizeof(long int));
        Mas_C[i] = (long  int*)malloc(n * sizeof(long int));
        for (long int j = 0; j < n; j++)
        {
            scanf("%ld", &Mas_R[i][j]);
            scanf("%ld", &Mas_C[i][j]);
        }
    }

    for (long int i = 0; i < n; i++)
    {
        for (long int j = 0; j < n; j++)
        {
            Mas_C[i][j] = Mas_C[i][j] * (-1);
        }
    }
    for (long int i = 0; i < n; i++)
    {
        for(long int j = 0; j < n; j++)
        {
            printf("%ld ", Mas_R[j][i]);
            printf("%ld ", Mas_C[j][i]);
        }
        printf("\n");
    }
    for (long int i = 0; i < n; i++)
    {
        free(Mas_R[i]);
        free(Mas_C[i]);
    }
    free(Mas_R);
    free(Mas_C);

    return 0;
}