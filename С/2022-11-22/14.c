#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[1000000];
    scanf("%s", s);
    int cnt_0 = 0;
    int cnt_1 = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == 'A')
        {
            if (i % 2 == 1)
            {
                cnt_1++;
            }
            else
            {
                cnt_0++;
            }
        }
    }
    int left_1 = 0;
    int left_0 = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == 'A')
        {
            if (i % 2 == 1)
            {
                cnt_1--;
            }
            else
            {
                cnt_0--;
            }
        }
        if (left_1 + cnt_0 == left_0 + cnt_1)
        {
            printf("%d ", i + 1);
        }
        if (s[i] == 'A')
        {
            if (i % 2 == 1)
            {
                left_1++;
            }
            else
            {
                left_0++;
            }
        }
    }

}