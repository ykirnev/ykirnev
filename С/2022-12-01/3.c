#include <stdio.h>
#include <stdlib.h>

struct L1
{
    int x;
    struct L1 *next;
};

int main(void)
{
    FILE *output, *input;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    struct L1 *root;
    struct L1 *new;
    int n = 1;
    int a;
    root = (struct L1*)malloc(sizeof(struct L1));
    new = (struct L1*)malloc(sizeof(struct L1));
    fscanf(input, "%lld ", &x);
    root-> x = a;
    root->next = new; 
    while (fscanf(input, "%d", &a) == 1)
    {
        new -> x = a;
        new -> next = (struct L1*)malloc(sizeof(struct L1));
        new = new -> next;
        new -> next = NULL;
        n++;
    }
    new = root;
    for (int i = 0; i < n - 1; i++)
    {
        new = root;
        for(int j = 0; j < n - 1; j++)
        {
            if ((new->x) > (new->next->x))
            {
                int swap = new->x;
                new->x = new->next->x;
                new->next->x = swap;
            }
            new = new->next;
        }
    }
    while(root->next != NULL)
    {
        fprintf(output, "%d ", root->x);
        root = root->next;
    } 
    
    return 0;
}
