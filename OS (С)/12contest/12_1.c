#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    int i = 0;
    char summon[6] = "summon";
    char reject[6] = "reject";
    char disqualify[10] = "disqualify";
    int x;
    while (scanf("0", &x) == 1) {
        printf("%s", x>5?summon:disqualify);
    }
    return 0;
}
