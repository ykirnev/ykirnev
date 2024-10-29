#include <stdio.h>

int cont(int a)
{
    int i = 10;
    while (i < a)
    {
        i = i * 10;
    }    
    a = a * i + a;
    return a;
}

int main (void)
{
    int N, A;
    int Mas [2010];
    for(int i = 0; i < 2010; i++)
    {
        Mas[i] = 0;  
    }
    scanf("%d %d", &N, &A);
    int x1 = N % 2010;
    if (x1 == A)
    {
        printf("YES");
        return 0;
    }
    if (A >= 2010)
    {
        printf("NO");
    }
    else{
        int flag = 0;
        for(int i = 0; i < 4000; i++)
        {
            Mas[x1] = Mas[x1] + 1;
            if (Mas[x1] >= 2)
            {
                printf("NO");
                return 0;
            }
            x1 = cont(x1) % 2010;
            if (x1 == A)
            {
                printf("YES");
                return 0;
            }
        }
        if (flag == 0)
        {
            printf("NO");
            return 0;
        }
    }
}