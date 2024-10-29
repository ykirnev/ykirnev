#include <stdio.h>
#include <stdlib.h>

int main (void)
{
    FILE *output, *input;
    input = fopen("matrix.in", "rb");
    output = fopen("trace.out", "wb");
    int n;
    int x;
    n = 0;
    unsigned char c;
    long long int answer = 0;
    fread(&c, sizeof(char), 1, input);
    n = n + c;
    n = n << 8;
    fread(&c, sizeof(char), 1, input);
    n = n + c;
    for(int i = 0; i < n; i ++)
    {
        for(int j = 0; j < n; j++)
        {
            x = 0;
            fread(&c, sizeof(char), 1, input);
            x = x + c;
            x = x << 8; 
            fread(&c, sizeof(char), 1, input);
            x = x + c;
            x = x << 8;   
            fread(&c, sizeof(char), 1, input);
            x = x + c;
            x = x << 8;
            fread(&c, sizeof(char), 1, input);
            x = x + c;
            if (i == j)
            {
                answer = answer + x;
            }
        }
    }
    long long int mod = 0;
    for (int i = 0; i < 64; i = i + 8)
    {
        mod = 0;
        mod = answer;
        mod = mod >> (64 - i - 8);
        c = mod % 256;
        fwrite(&c, sizeof(char), 1, output);
    }
    fclose(input);
    fclose(output);
}