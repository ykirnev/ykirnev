tree * findBrother(tree *root, int key)
{
    if (root == NULL)
    {
        return 0;
    }
    if (root -> key == key)
    {
        return root;
    }
    if (root -> key == key)
    {
        root = root -> parent;
        if (root == NULL)
        {
            return 0;
        }
        if (root -> left == NULL || root -> right == NULL)
        {
            return 0;
        }
        if (root -> left -> key == key)
        {
            return root -> right;
        }
        else
        {
            return root -> left;
        }
    }
    else
    {
        if (root -> key < key)
        {
            findBrother(root -> right, key);
        }
        else
        {
            findBrother(root -> left, key);
        }
    }
}