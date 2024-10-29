#include <stdio.h>
#include <stdlib.h>

extern int buf[];
int *bufp0 = &buf[0];
static int *bufp1;
void swap()
{
    int temp;
    bufp1 = &buf[1];
    *bufp0 = *bufp1;
    *bufp1 = temp;
}