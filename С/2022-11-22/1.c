#include <stdio.h> 
#include <string.h>
int mn(int x, int y)
{
    if (x > y)
    {
        return x;
    }
    return y;
}

int main(void)
{
    char a[10001], b[10001];
    scanf("%s", b);
    scanf("%s", a);
    int answer = 0;
    for (int i = 0; i < mn (strlen(a), strlen(b)); i++)
    {
        int flag = 1;
        for (int j = 0; j < i; j++)
        {
            if (b[j] != a[strlen(a) - i + j])
            {
                flag = 0;
            }   
        }
        if (flag == 1)
        {
            answer = i;
        }
    }
    printf("%d ", answer);
    answer = 0;
    for (int i = 0; i < mn (strlen(a), strlen(b)); i++)
    {
        int flag = 1;
        for (int j = 0; j < i; j++)
        {
            if (a[j] != b[strlen(b) - i + j])
            {
                flag = 0;
            }   
        }
        if (flag == 1)
        {
            answer = i;
        }
    }
    printf("%d", answer);
}