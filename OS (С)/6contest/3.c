#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct s1
{
    char f1;
    long long f2;
    char f3;
};

struct s2
{
    char f1;
    char f3;
    long long f2;
};

size_t compactify (void *ptr, size_t size)
{
    if (size == 0) {
        return 0;
    }
    int s1_size = sizeof(struct s1);
    int num = size / s1_size;
    int s2_size = sizeof(struct s2);
    struct s1 in;
    struct s2 out;
    long long int size2 = 0;
    long long int tmp_shift = 0;
    for (int i = 0; i < num; i++) {
        in = *(struct s1 *) ((char *)ptr + tmp_shift);
        out.f1 = in.f1;
        out.f2 = in.f2;
        out.f3 = in.f3;
        memset(ptr + i * s1_size, 0, s1_size);
        *(struct s2 *)((char *)ptr + tmp_shift) = out;
        size2 = size2 + s2_size;
        tmp_shift = tmp_shift + s2_size;
    }
    return size2;
}