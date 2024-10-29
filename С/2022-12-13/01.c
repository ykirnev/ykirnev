#include <stdio.h>
#include <stdlib.h>

int main(int arg,char *argv[]) {
    FILE *input, *output;
    int x;
    x = 1;
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "wb");
    while(fscanf(input,"%d", &x) != -1)
    {
        fwrite(&x,sizeof(int),1,output);
    }
    fclose(input);
    fclose(output);
    return 0;
}