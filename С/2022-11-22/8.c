#include <stdio.h>
#include <string.h>

int digit(char x)
{
    int y = x - '0';
    return(y);   
}

int chislo(char a, char b, char c)
{
    return(100 * digit(a) + 10 * digit(b) + digit(c));
}

int main(void){
    char s[100];
    char c;
    for(int i = 0; i<100; i++)
    {
        s[i] = '\0';
    }
    int Mas[1000];
    for (int i = 0; i < 1000; i++)
    {
        Mas[i] = 0;
    }
    int pos = 0;
    while ((c = getchar()) != '\n')
    {
        s[pos] = c;
        pos++;
    }
    for (int i = 0; i < strlen(s) - 2; i++)
    {
        for (int j = i + 1; j < strlen(s) - 1; j++)
        {
            for (int k = j + 1; k < strlen(s); k++)
            {
                int x = chislo(s[i], s[j], s[k]);
                if (x >= 100)
                {
                    if (Mas[x] == 0)
                    {
                        Mas[x]++;
                    }
                }
            }
        }
    }
    int counter = 0;
    for (int i = 100; i < 1000; i++)
    {
        counter = counter + Mas[i];
    }
    printf("%d", counter);

}