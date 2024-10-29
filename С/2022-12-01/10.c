#include <stdio.h>
#include <stdlib.h>

struct L2
{
    int x;
    struct L2 *prev;
    struct L2 *next;
};



int main(void)
{
    FILE *output, *input;
    input = fopen("input.txt", "r");
    output = fopen("output.txt", "w");
    struct L2 *root;
    struct L2 *root_pointer;
    struct L2 *nw;
    root = (struct L2*)malloc(sizeof(struct L2));
    root_pointer = (struct L2*)malloc(sizeof(struct L2));
    root_pointer -> prev = NULL;
    root_pointer -> next = root;
    root->x = 1;
    root->prev = root_pointer;
    nw = (struct L2*)malloc(sizeof(struct L2));
    root->next = nw;
    nw->prev = root;
    int n, m, par1, par2;
    fscanf(input, "%d %d", &n, &m);
    struct L2 *Mas_pointers[n + 1];
    Mas_pointers[0] = root;
    if (n == 0)
    {
        return 0;
    }
    for (int i = 1; i < n; i++)
    {
        nw -> x = i + 1; 
        Mas_pointers[i] = nw;
        nw -> next = (struct L2*)malloc(sizeof(struct L2));
        nw -> next -> prev = nw;
        nw = nw-> next;
        nw -> x = 0;
        nw -> next = NULL;
    }
    struct L2 *before;
    struct L2 *after;
    struct L2 *start;
    struct L2 *end;
    struct L2 *tmp;
    printf ("%d", Mas_pointers[1]->x);
    for (int i = 0; i < m; i++)
    {
        fscanf(input, "%d %d", &par1, &par2);
        tmp = Mas_pointers[par1 - 1];
        if (tmp -> next != NULL)
        {
            start = tmp;
            before = tmp -> prev;
            tmp = Mas_pointers[par2 - 1];  
            if (tmp -> next != NULL)
            {
                end = tmp;
                after = tmp -> next;
                if (before == root_pointer)
                {
                    continue;
                }
                start -> prev = root_pointer;
                root_pointer -> next = start;
                end -> next = root;
                root -> prev = end;
                before -> next = after;
                after -> prev = before;
                root = root_pointer -> next;
            }
        }
    }
    root = root_pointer->next;
    while(root->x != 0)
    {
        fprintf(output, "%d ", root -> x);
        root = root -> next;
    }
    fclose(output);
    fclose(input);
}  