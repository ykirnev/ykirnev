#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[2000001];
    char c;
    for(int i = 0; i < 2000001; i++)
    {
        s[i] = '\0';
    }
    int pos = 0;
    while ((c = getchar()) != '\n')
    {
        s[pos] = c;
        pos++;
    }
    char min[2000001];
    for(int i = 0; i < 2000001; i++)
    {
        min[i] = '\0';
    }
    for (int i = 0; i < strlen(s); i++)
    {
        min[i] = s[i];
    }
    for (int j = 1; j < strlen(s); j++)
    {
        if (s[j] == '0')
        {
            char sdvig[strlen(s)];
            for (int i = 0; i < strlen(s); i++)
            {
                sdvig[i] = '\0';
            }
            int pos = 0;
            for (int i = j; i < strlen(s); i++)
            {
                sdvig[pos] = s[i];
                pos++;
            }
            for (int i = 0; i < j; i++)
            {
                sdvig[pos] = s[i];
                pos++;
            }

            for(int i = 0; i < strlen(s); i++)
            {
                if (sdvig[i] > min[i])
                {
                    break;
                }
                else if (min[i] > sdvig[i])
                {
                    for (int k = 0; k < strlen(s); k++)
                    {
                        min[k] = sdvig[k];
                    }
                    break;
                }
            }
        }
    }
    printf("%s", min);
}