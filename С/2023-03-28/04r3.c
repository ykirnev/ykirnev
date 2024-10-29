#include <stdio.h>
#include <stdlib.h>

//Кирнев Юра 105 группа
int m(int eax, int ecx, int edx)
{
    while (1){
        if (eax >= ecx)
        {
            if (eax > edx)
            {
                eax = eax ^ edx;
                edx = edx ^ eax;
                eax = eax ^ edx;
            }
            else
            {
                return eax;
            }
        }
        else{
            eax = eax ^ ecx;
            ecx = ecx ^ eax;
            eax = eax ^ ecx;
            if (eax > edx)
            {
                eax = eax ^ edx;
                edx = edx ^ eax;
                eax = eax ^ edx;
            }
            else
            {
                return eax;
            }
        }
    }
}

int main(void)
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    a = m(a, b, c);
    printf("%d\n", a);
    return 0;
}