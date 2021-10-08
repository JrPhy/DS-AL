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
    node *tmpNode = malloc(sizeof(node));
    if(tmpNode!=NULL)
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
    if (root->left != NULL)  //若其中一側的子樹非空則會讀取其子樹
        inorder(root->left);
    if (root->right != NULL) //另一側的子樹也做相同事
        inorder(root->right);

}

node *search(node *root, int key)
{
    node *current = root;
    while(current != NULL && key != current->data)
    {
        if(key > root->data) current = current->right; //若比較大則往右走
        else current  = current->left;                 //否則往左走
    }
    if(current != NULL) return current;
    else return NULL;
}

void insert(node **root, int value)
{
    node *current = *root, *prevNode = NULL;
    while(current != NULL)
    {
        prevNode = current;
        if(prevNode->data > value && value > current->data) break;
        if(current->data > value && value > prevNode->data) break;
        //當要插入的值介於兩節點之間就跳脫迴圈
        if(value > current->data)  current = current->right; //若比較大則往右走
        else current  = current->left;                       //否則往左走
    }

    if(prevNode == NULL) prevNode = newNode(value);
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
        else current  = current->left;                       //否則往左走
    }
    printf("\n%d\n", current->data);

    if(current->left == NULL && current->right == NULL)
    {
        if (prevNode->left == current)  prevNode->left = NULL;
        else prevNode->right = NULL;
        free(current);
    }
    else if(current->left != NULL && current->right != NULL)
    {
        node *tempNode = current->right, *prevTemp;
        while(tempNode->left != NULL)
        {
            prevTemp = tempNode;
            tempNode = tempNode->left;
        }
        current->data = tempNode->data;
        prevTemp->left = NULL;
        free(tempNode);
    }
    else
    {
        if (prevNode->data > current->data)
        {
            if (current->left != NULL) prevNode->left = current->left;
            else prevNode->left = current->right;
        }
        else
        {
            if (current->left != NULL) prevNode->right = current->left;
            else prevNode->right = current->right;
        }
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
    /*
    node *root1_left = newNode(1);
    node *root1_right = newNode(5);
    node *root2_left = newNode(3);
    node *root2_right = newNode(2);

    root->left = root1_left;
    root->right = root1_right;
    root1_left->left = root2_left;
    root1_right->right = root2_right;
    */
    return 0;
}
