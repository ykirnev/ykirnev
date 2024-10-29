void left(tree *root);
void right(tree *root);
void btUpView(tree *root);

void left(tree *root)
{
    if (root -> left == NULL)
    {
        printf("%d ", root-> key);
    }
    else{
        left(root -> left);
        printf("%d ", root-> key);
    }
}

void right(tree *root)
{
    if (root -> right == NULL)
    {
        printf("%d ", root-> key);
    }
    else{
        printf("%d ", root-> key);
        right(root -> right);
    }
}


void btUpView(tree *root)
{
    if (root != NULL)
    {
        if (root -> left != NULL)
        {
            left(root -> left);
        }
        printf("%d ", root -> key);
        if(root -> right != NULL)
        {
            right(root -> right);
        }
    }
}