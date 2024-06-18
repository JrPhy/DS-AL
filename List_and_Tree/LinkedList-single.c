#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
    int data;
    struct _node *next;
}node;

node* newNode(int value)
{
    node *tmpNode = (node *) malloc(sizeof(node));
    if(tmpNode!=NULL) {
        tmpNode->data = value;
        tmpNode->next = NULL;
    }
    return tmpNode;
}

void printList(node *list)
{
    while(list != NULL)
    {
        printf("%d->", list->data);
        list = list->next;
    }
     printf("\n");
}

int lenOfList(node *list)
{
    int length = 0;
    while(list != NULL)
    {
        ++length;
        list = list->next;
    }
    return length;
}

void insertNode(node **list, int value, int position)
{
    node *temp = *list;
    int length = lenOfList(temp);
    
    /* insert at the beginning*/
    node *new_node = newNode(value);
    if(position < 1) {
        new_node->next = *list;
        *list = new_node;
    }
    /* insert at the beginning*/
    /* insert at the ending*/
    else if (position > length) {
        node *temp = *list;
        while(temp->next != NULL) temp = temp->next;
        temp->next = new_node;
    }
    /* insert at the ending*/
    /* insert at the middle*/
    else {
        node *temp = *list;
        for (int i = 1; i < position; i++) 
            {if (temp->next != NULL) temp = temp->next;}
        new_node->next = temp->next;
        temp->next = new_node;
    }
    /* insert at the middle*/
}

void deleteNode(node **list, int position) 
{
    int length = lenOfList(*list);
    node *temp = *list;
    if (position <= 0) {
        node *toBeDel = *list;
        *list = toBeDel->next;
        free(toBeDel);
        return;
    }
    else if (position >= length) position = length - 1;
    
    for (int i = 0; temp != NULL && i < position - 1; ++i) temp = temp->next;
    if (temp == NULL || temp->next == NULL) return;
    node *nodeToBeDel = temp->next;
    temp->next = nodeToBeDel->next;
    free(nodeToBeDel);
}

void reverse(node **list)
{
    node *prevNode = NULL, *current = *list, *nextNode = NULL;
    while (current != NULL) 
    {
        nextNode = current->next;
        current->next = prevNode;
        prevNode = current;
        current = nextNode;
    }
    *list = prevNode;
}

int main()
{
    /* Initialize nodes */
    node *one = newNode(1);
    node *two = newNode(2);
    node *three = newNode(3);
    
    one->next = two;
    two->next = three;
    three->next = NULL;
    // insert new node at the beginning
    printList(one);
    insertNode(&one, 4, 0);
    printList(one);
    // insert new node at the ending
    insertNode(&one, 5, 10);
    printList(one);
    // insert new node in the middle
    insertNode(&one, 7, 2);
    printList(one);

    deleteNode(&one, 10);
    printList(one);

    deleteNode(&one, 3);
    printList(one);
    
    reverse(&one);
    printList(one);
    
    return 0;
}
