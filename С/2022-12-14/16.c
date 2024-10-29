#include <stdio.h>
#include <stdlib.h>

struct L2
{
    long long int x;
    struct L2 * next;
};

int med(int x)
{
    return x / 2 + x % 2;
}

struct L2 *slianie(struct L2 *left, struct L2 *right)
{
    struct L2 *answer = NULL;
    if (left == NULL) return right;
    if (right == NULL) return left;
    if (left -> x < right -> x)
    {
        answer = left;
        answer -> next = slianie(left -> next, right);
    }
    else{
        answer = right;
        answer -> next = slianie(right -> next, left);
    }
    return answer;
}

struct L2* sort(struct L2 **root, int size)
{
    if (size <= 1)
    {
        return *root;
    }
    struct L2 *left, *right, *tmp;
    left = (struct L2*)malloc(sizeof(struct L2));
    left = *root;
    tmp = (struct L2*)malloc(sizeof(struct L2));
    right = (struct L2*)malloc(sizeof(struct L2));
    tmp = left;
    int m = med(size);
    for (int i = 0; i < m - 1; i++)
    {
        if (tmp -> next != NULL) tmp = tmp -> next;
    }
    right = tmp;
    return slianie(sort(&left, m), sort(&right, size - m));
}

int main(void)
{
    FILE *input, *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    int size = 0;
    long long int x;
    struct L2 *new, *end;
    struct L2**root;
    root = (struct L2**)malloc(sizeof(struct L2*));
    new = (struct L2*)malloc(sizeof(struct L2));
    root = &new;
    while (fscanf(input, "%lld", &x) > 0)
    {
        new -> x = x;
        new -> next = malloc(sizeof(struct L2));
        new = new -> next;
        new -> next = NULL;
        size++;
    }
    *root = sort(root, size);
    new = *root;
    for (int i = 0; i < size; i++)
    {
        fprintf(output, "%lld ", new -> x);
        new = new -> next;
    }
    fclose(input);
    fclose(output);
}