#include <stdio.h>
#include <stdlib.h>

enum
{
    MASK = 1
};

int 
comp (const void *a, const void *b)
{
    if (a == b) {
        return 0;
    }
    int a_copy = *(int *)a; 
    int b_copy = *(int *)b;
    int a_parity, b_parity;
    a_parity = a_copy & MASK;
    b_parity = b_copy & MASK;
    if (a_parity == b_parity) {
        if (a_parity == 1) {
            if (a_copy < b_copy) {
                return 1;
            }
            return -1;
        } else {
            if (a_copy > b_copy) {
                return 1;
            }
            return -1;
        }
    }else {
        if (a_parity == 1) {
            return 1;
        }
        return -1;
    }
}

void
sort_even_odd(size_t count, int *data) 
{
    qsort (data, count, sizeof(data[0]), comp);
}
