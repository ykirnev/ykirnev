#include <stdio.h>
#include <stdlib.h>


typedef struct L1
{
    long long int x;
    struct L1 * next;
} L1;

struct L1 *slianie(L1 *left, L1 *right)
{
    L1 *answer;
    answer = NULL;
    if (left == NULL) return right;
    if (right == NULL) return left;
    if (left -> x < right -> x)
    {
        answer = (L1*)malloc(sizeof(L1));
        answer = left;
        answer -> next = slianie(left -> next, right);
    }
    else{
        answer = (L1*)malloc(sizeof(L1));
        answer = right;
        answer -> next = slianie(right -> next, left);
    }
    return answer;
}



L1 *sort(L1 *root)
{
    L1 *left = NULL;
    L1 *prev = NULL;
    L1 *right = NULL;
    L1 *end = NULL;
    if (root == NULL || root -> next == NULL)
    {
        return root;
    }
    left = root;
    end = root;
    while (root -> next != NULL && end != NULL && end -> next != NULL)
    {
        prev = root;
        root = root -> next;
        end = end -> next;
        if (end -> next != NULL)
        {
            end = end -> next;
        }
    }
    if (root -> next != NULL)
    {
        right = root;
    }
    prev -> next = NULL;
    return slianie(sort(left), sort(right));
}

int main(void)
{
    FILE *input, *output;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    int size = 0;
    long long int x;
    L1 *root, *new;
    root =(struct L1*) malloc(sizeof(L1));
    new = root;
    while (fscanf(input, "%lld", &x) > 0)
    {
        new -> next = malloc(sizeof(L1));
        new = new -> next;
        new -> x = x;
        new -> next = NULL;
        size++;
    }
    root = root -> next;
    root = sort(root);
    while(root -> next != NULL)
    {
        fprintf(output, "%lld", root -> x);
        root = root -> next;
    }
    fclose(input);
    fclose(output);
}