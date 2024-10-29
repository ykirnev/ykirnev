void * findMaxBlock(list *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    int *max_address;
    size_t max = 0;
    while(head != NULL)
    {
        if (max < head -> size)
        {
            max = head -> size;
            max_address = head -> address;
        }
        head = head -> next;
    }
    return max_address;
}