
```C
int* postorderTraversal(struct TreeNode* root, int* returnSize)
{
    (*returnSize) = 0;
    if(root==NULL) return NULL;
    struct TreeNode *current = newNode(-1);
    current->left = root;
    struct TreeNode *pre = NULL, *prev = NULL, *succ = NULL, *temp = NULL;
    //printf( "%d ", *returnSize);
    int *result = calloc(101, sizeof(int));
         
    while (current)
    {
        if (current->left == NULL) current = current->right;
        else
        {
            pre = current->left;
             
            // Inorder predecessor
            while (pre->right && pre->right != current) pre = pre->right;
             
            // The connection between current and
            // predecessor is made
            if (pre->right == NULL)
            {
                pre->right = current;
                current = current->left;
            }
            else
            {
                pre->right = NULL;
                succ = current;
                current = current->left;
                prev = NULL;
                while (current != NULL)
                {
                    temp = current->right;
                    current->right = prev;
                    prev = current;
                    current = temp;
                }
                while (prev != NULL)
                {
                    result[(*returnSize)++] = prev->val;
                    temp = prev->right;
                    prev->right = current;
                    current = prev;
                    prev = temp;
                }
                current = succ;
                current = current->right;
            }
        }
    }
    return result;
}
```
