#include <stdio.h>
#include <string.h>

int main(void)
{
    int n;
    scanf("%d\n", &n);
    char c;
    char s [1000001];
    for (int i = 0; i < 1000001; i++)
    {
        s[i] = '\0';
    }
    int counter = 0;
    int pos = 0;

    while ((c = getchar()) != '\n')
    {
        s[pos] = c;
        pos++;
        if (c == ' ')
        {
            counter++;
        }
    }
    n = n - strlen(s);
    int add = n / counter;
    int add_2 = n % counter;
    counter = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        printf("%c", s[i]);
        if (s[i] == ' ')
        {
            for (int i = 0; i < add; i++)
            {
                printf(" ");
            }
            if (counter < add_2)
            {
                printf(" ");
            }
            counter++;
        }
    }

}