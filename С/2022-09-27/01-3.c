#include <stdio.h>

int main (void)
{
    int n;
    scanf("%d", &n);
    char c;
    scanf("%c", &c);
    while (c != '.')
    {
    
        if ((('A' <= c) && ('Z' >= c)) || (('a' <= c) && ('z' >= c)))
        {
            if (('A' <= c) && ('Z' >= c))
            {
                int number = c - 'A';
                number = (number + n) % 26;
                c = 'A' + number;

            }
            else if (('a' <= c) && ('z' >= c))
            {
                int number = c - 'a';
                number = (number + n) % 26;
                c = 'a' + number;
            }
            printf("%c", c);
        }
        else
        {
            printf("%c", c);
        }
        scanf("%c", &c);
    }
    printf(".");
    return 0;
} 