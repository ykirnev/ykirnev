#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int 
main(void)
{
    char s1[129];
    char s2[129];
    char s3[129];
    int s1_scanf, s2_scanf, s3_scanf;
    s1_scanf = scanf("%s", s1);
    s2_scanf = scanf("%s", s2);
    s3_scanf = scanf("%s", s3);
    if (s1_scanf != 1) {
        return 1;
    }
    if (s2_scanf != 1) {
        return 1;
    }
    if (s3_scanf != 1) {
        return 1;
    }
    printf("[Host:%s,Login:%s,Password:%s]\n", s1, s2, s3);
    return 0;
}