雖然使用遞迴(Recursive)寫法能讓 code 看起來非常簡潔，且能明確地看出以上三種寫法的差異，但是在空間與時間效率上皆不如迭代法，且太深層時容易造成 stack overflow，故實務上較少會使用遞迴法，此也為 [leetcode 的一題](https://leetcode.com/problems/binary-tree-inorder-traversal/)。在此先以 preorder 為例，不論是哪一種寫法都是先走到左子樹的 NULL 再往右走。

## 1. Preorder Traversal
此方法利用一個多的節點 current 來當作 recursive 的 stack，記錄當下節點的左子節點，當左邊的節點走到 NULL 後再跳回 root 節點，並先往右節點走，然後再重複前一步，也就是當 root != NULL 時
1. 若 root->left == NULL 則印出資料，並往 root->right 走。
2. 若 root->left != NULL，利用 current 節點往 root 左子樹的最大值，並將該葉子的 right 指向 root，然後 root 再往走向左子節點。
3. 若 current->right == root，表示 root 也走到葉子了，此時將 current->right 還原為 NULL，root 再往回走像上一層節點。

因為 preorder 是先將 root 左子樹整個走訪後再往 root 右子樹走，所以利用葉子的 right 指向上層的 root，如此一來只須用到多一個 node 即可走訪整個二元樹。以此樹為例，第一次會將 root 左子樹的葉子 9 的右節點指向 11，然後 root 往左走向左節點，再來將 root 左子樹的左子樹的葉子 4 的右節點指向 5，以此類推。
![image](../pic/morrisTraversalPreorder.jpg)
```C
void morrisTraversalPreorder(node* root)
{
    node *current;
    while (root)
    {
        if (root->left == NULL)
        {
            printf( "%d ", root->data );
            root = root->right;
        }
        else
        {
            current = root->left;
            while (current->right && current->right != root) current = current->right;

            if (current->right == root)
            {
                root = root->right;
                current->right = NULL;
            }
            else
            {
                printf("%d ", root->data);
                current->right = root;
                root = root->left;
            }
        }
    }
}
```

## 2. Inorder Traversal
Inorder 則是從最左邊開始往右走，與 Preorder 的差異在於會先走到最小的資料 (以 Binary Search Tree 為例)，然後依序由小到大印出。當走到 leave 的 right (原為指向 NULL，當將此節點指向其父節點) 時就印出資料。
```C
void morrisTraversalInorder(node* root)
{
    node *current;
    while (root)
    {
        if (root->left == NULL)
        {
            printf( "%d ", root->data );
            root = root->right;
        }
        else
        {
            current = root->left;
            while (current->right && current->right != root) current = current->right;

            if (current->right == root)
            {
                printf("%d ", root->data);
                root = root->right;
                current->right = NULL;
            }
            else
            {
                current->right = root;
                root = root->left;
            }
        }
    }
}
```

## 3. Postorder Traversal
```C
void morrisTraversalPostorder(node* root)
{
    node* current = newNode(-1);
    current->left = root;
    node *pre = NULL, *prev = NULL, *succ = NULL, *temp = NULL;
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
                    printf("%d ", prev->data);
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
}
```
