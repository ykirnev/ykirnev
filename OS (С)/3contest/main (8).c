#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

enum
{
    MAX_LEN = 13,
    MY_INT_MAX = INT32_MAX,
};

struct Elem
{
    struct Elem *next;
    char *str;
};

struct Elem *
push_between(struct Elem *behind, struct Elem *after, int value)
{
    struct Elem *new_elem = (struct Elem *) calloc(1, sizeof(struct Elem));
    new_elem->str = calloc(MAX_LEN, sizeof(char));
    new_elem->next = after;

    snprintf(new_elem->str, MAX_LEN, "%d", value);

    if (!behind) {
        return new_elem;
    }

    behind->next = new_elem;
    return behind;
}

int
isnum(char *str, int *val)
{
    char *end = "";
    errno = 0;
    long int value = strtol(str, &end, 10);
    *val = (int) value;

    if (!(*end || errno || end == str || (int) value != value) && value != MY_INT_MAX) {
        return 0;
    }
    return 1;
}

struct Elem *
dup_elem(struct Elem *head)
{
    if (!head) {
        return NULL;
    }
    struct Elem *cur1 = head;
    struct Elem *cur2 = head->next;
    int val;
    struct Elem *new_head = head;
    if (!isnum(cur1->str, &val)) {
        new_head = push_between(NULL, cur1, (int) val + 1);
    }
    while (cur2) {
        if (!isnum(cur2->str, &val)) {
            push_between(cur1, cur2, (int) val + 1);
        }
        cur1 = cur2;
        cur2 = cur2->next;
    }
    return new_head;
}

void
print_l(struct Elem *head)
{
    struct Elem *cur = head;
    while (cur) {
        printf("%s ", cur->str);
        cur = cur->next;
    }
    printf("\n");
}

int
main(void)
{
    struct Elem *head = (struct Elem *) calloc(1, sizeof(struct Elem));
    head->str = "10";
    struct Elem *cur = (struct Elem *) calloc(1, sizeof(struct Elem));
    head->next = cur;
    cur->str = "5x";
    cur->next = (struct Elem *) calloc(1, sizeof(struct Elem));
    cur = cur->next;
    cur->str = "+1";
    cur->next = (struct Elem *) calloc(1, sizeof(struct Elem));
    cur = cur->next;
    cur->str = " -03";
    print_l(head);
    head = dup_elem(head);
    print_l(head);
    return 0;
}
