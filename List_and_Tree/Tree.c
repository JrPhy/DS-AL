#include<stdio.h>
#include<stdlib.h>

typedef struct _node
{
    int data;
    struct _node *left;
    struct _node *right;
}node;

node* newNode(int value)
{
    node *tmpNode = (node*) malloc(sizeof(node));
    if(tmpNode)
    {
        tmpNode->data = value;
        tmpNode->left = NULL;
        tmpNode->right = NULL;
    }
    return tmpNode;
}

void inorder(node *root)
{
    printf("%d, ", root->data);
    if (root->left)  //若其中一側的子樹非空則會讀取其子樹
        inorder(root->left);
    if (root->right) //另一側的子樹也做相同事
        inorder(root->right);

}

node *search(node *root, int key)
{
    node *current = root;
    while(current && key != current->data)
    {
        if(key > current->data) current = current->right; //若比較大則往右走
        else current = current->left;                 //否則往左走
    }
    if(current) return current;
    else return NULL;
}

void insert(node **root, int value)
{
    node *current = *root, *prevNode = NULL;
    while(current)
    {
        prevNode = current;
        if(prevNode->data > value && value > current->data) break;
        if(current->data > value && value > prevNode->data) break;
        //當要插入的值介於兩節點之間就跳脫迴圈
        if(value > current->data)  current = current->right; //若比較大則往右走
        else current  = current->left;                       //否則往左走
    }

    if(!prevNode) prevNode = newNode(value);
    else if (value < prevNode->data)
    {
        prevNode->left = newNode(value);
        prevNode = prevNode->left;
        prevNode->left = current;
    }
    else
    {
        prevNode->right = newNode(value);
        prevNode = prevNode->right;
        prevNode->right = current;
    }
}

void deleteNode(node **root, int value)
{
    node *current = *root, *prevNode = NULL;
    while(current->data != value)
    {
        prevNode = current;
        if(prevNode->data > value && value > current->data) break;
        if(current->data > value && value > prevNode->data) break;
        //當要插入的值介於兩節點之間就跳脫迴圈
        if(value > current->data)  current = current->right; //若比較大則往右走
        else current = current->left;                       //否則往左走
        if(!current) return;                          //表示此樹中沒有要刪除的值
    }
    printf("\n%d\n", current->data);

    if(!current->left && !current->right)
    {
        if (prevNode->left == current)  prevNode->left = NULL;
        else prevNode->right = NULL;
        free(current);
    }
    else if(current->left && current->right)
    {
        node *tempNode = current->right, *prevTemp = NULL;
        while(tempNode->left)
        {
            prevTemp = tempNode;
            tempNode = tempNode->left;
        }
        if (prevTemp) prevTemp->left = tempNode->right;
        else current->right = tempNode->right;
        current->data = tempNode->data;
        free(tempNode);
    }
    else
    {
        if (!prevNode)
        {
            if(current->right) 
            {
                (*root)->data = current->right->data;
                (*root)->right = NULL;
            }
            else 
            {
                (*root)->data = current->left->data;
                (*root)->left = NULL;
            }
        }
        else
        {
            if (prevNode->data > current->data)
            {
                if (current->left) prevNode->left = current->left;
                else prevNode->left = current->right;
            }
            else
            {
                if (current->left) prevNode->right = current->left;
                else prevNode->right = current->right;
            }
        }
        free(current);
    }
}

int main()
{
    /* Initialize nodes */
    node *root = newNode(11);
    insert(&root, 5);
    insert(&root, 15);
    insert(&root, 3);
    insert(&root, 9);
    insert(&root, 0);
    insert(&root, 4);
    insert(&root, 7);
    insert(&root, 13);
    insert(&root, 19);
    insert(&root, 17);
    insert(&root, 23);
    inorder(root);
    printf("\n");
    deleteNode(&root, 15);
    inorder(root);
    return 0;
}
