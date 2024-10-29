#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

struct Elem
{
    struct Elem *next;
    char *str;
};

struct Elem *
push (struct Elem *succeeding, struct Elem *previous, int val)
{

    struct Elem *new = calloc (1, sizeof(*new));
    new->str = calloc(12, sizeof(char));
    sprintf (new->str, "%d", val);
    new->next = succeeding;
    if (previous == NULL) {
        return new;
    }
    previous->next = new;
    return previous;
}

struct Elem *
dup_elem (struct Elem *head)
{
    enum
    {
        INT_MAX = (~0u)>>(!0),
        INT_MIN = ~INT_MAX
    };
    long int str_value;
    char *new_str = "";
    if (head == NULL) {
        return head;
    }
    struct Elem *tmp = head;
    errno = 0;
    str_value = strtol(tmp->str, &new_str, 10);

    if ((errno == 0) && ((int) str_value == str_value) && (new_str != tmp->str) && (new_str[0] == '\0')){
        if (str_value < INT_MAX) {
            str_value = (int)str_value;
            head = push(tmp, NULL, str_value + 1);
        }
    }
    struct Elem *tmp_prev = tmp;
    tmp = tmp -> next;
    while (tmp != NULL) {
        str_value = strtol(tmp->str, &new_str, 10);
        errno = 0;
        if ((errno == 0) && ((int) str_value == str_value) && (new_str != tmp->str) && (new_str[0] == '\0')){
            if ((str_value < INT_MAX) && (str_value >= INT_MIN)){
                str_value = (int)str_value;
                push(tmp, tmp_prev, str_value + 1);
            }
        }
        tmp_prev = tmp;
        tmp = tmp->next;
    }
    return head;
}