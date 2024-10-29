#include <stdio.h>
#include <string.h>

int main(void)
{
    int n;
    char c[81];
    scanf("%d", &n);
    scanf("%s", c);
    n = n % strlen(c);
    char answer[81];
    for (int i = 0; i < 81; i++)
    {
        answer[i] = '\0';
    }
    
    int cnt = 0;
    for (int i = n; i < strlen(c); i++)
    {
        answer[cnt] = c[i];
        cnt++;
    }
    for (int i = 0; i < n; i++)
    {
        answer[cnt] = c[i];
        cnt++;
    }
    printf("%s", answer);
}