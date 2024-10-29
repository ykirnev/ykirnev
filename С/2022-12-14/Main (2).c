#include <stdio.h>
#include <stdlib.h>


typedef struct L1
{
    long long int x;
    struct L1 * next;
} L1;

L1 *slianie(L1 *left, L1 *right)
{
    L1 *answer;
    answer = NULL;
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
    end = root->next;
    while (end != NULL)
    {
        end = end -> next;
        if (end!= NULL)
        {
            left=left->next;
            end = end -> next;
        }
    }
    L1 *a=root;
    L1 *b=left->next;
    left -> next = NULL;
    L1 *le=sort(a), *ri=sort(b);
    L1 *ll=slianie(le, ri);
    return ll;
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
        new -> next = (struct L1*)malloc(sizeof(L1));
        new = new -> next;
        new -> x = x;
        new -> next = NULL;
        size++;
    }
    L1 *l=NULL;
    root = root -> next;
    l = sort(root);
    while(l!= NULL)
    {
        fprintf(output, "%lld ", l -> x);
        l = l -> next;
    }
    fclose(input);
    fclose(output);
}