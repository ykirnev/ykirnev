#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int mas[10, 1, 2, 4, 55];
    mas = qsort(mas);    
    for(int i = 0; i < 12; i++)
    {
        printf("%d", mas[i]);
    }
}