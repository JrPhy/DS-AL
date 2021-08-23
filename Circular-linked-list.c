#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int data;
    struct _node *next;
}node;

node* newNode(int value)
{
    node *tmpNode = malloc(sizeof(node));
    if(tmpNode!=NULL)
    {
        tmpNode->data = value;
        tmpNode->next = NULL;
    }
    return tmpNode;
}

void printList(node *list)
{
    node *ptr = list;
    printf("%d->", list->data);
    list = list->next;
    while(list != ptr)
    {
        printf("%d->", list->data);
        list = list->next;
    }
    printf("\n");
}

void printListAddress(node *list)
{
    node *ptr = list;
    printf("%p->", list->next);
    list = list->next;
    while(list != ptr)
    {
        printf("%p->", list->next);
        list = list->next;
    }
    printf("\n");
}

int lenOfList(node *list)
{
    int length = 1;
    node *ptr = list;
    list = list->next;
    while(list != ptr)
    {
        ++length;
        list = list->next;
    }
    return length;
}

void insert(node **list, int value, int position)
{
    node *new_node = newNode(value);
    node *temp = *list;
    if(position < 1)
    {
        node *ptr = *list;
        while(temp->next != ptr) temp = temp->next;//此迴圈是移動到末節點

        temp->next = new_node; //將末節點與新的頭節點接上
        new_node->next = *list;//新的首節點接上原本的 list
        *list = new_node;
    }

    else
    {
        int length = lenOfList(*list);
        if(position >= length)position = position%length;
        for(int i = 0; i < position; i++) if(temp->next != NULL) temp = temp->next;
        new_node->next = temp->next;
        temp->next = new_node;
    }

}

void deleteNode(node **list, int position)
{
    node *temp = *list;
    if(position < 1)
    {
        node *ptr = *list;
        while(temp->next != *list) temp = temp->next;

        *list = ptr->next;
        temp->next = *list;
        free(ptr);
    }
    else
    {
        int length = lenOfList(*list);
        if(position >= length) position = position%length;
        for (int i = 0; i < position - 1; ++i) temp = temp->next;
        node *nodeToBeDel = temp->next;
        temp->next = nodeToBeDel->next;
        free(nodeToBeDel);
    }

}

void reverse(node **list)
{
    node *prevNode = *list, *current = *list, *nextNode = NULL, *ptr = *list;
    while (nextNode != ptr)
    {
        nextNode = current->next;
        current->next = prevNode;
        prevNode = current;
        current = nextNode;
    }
    current->next = prevNode;
    *list = prevNode;
}


int main()
{
    /* Initialize nodes */
    node *one = newNode(1);
    node *two = newNode(2);
    node *three = newNode(3);

    // connect the node
    one->next = two;
    two->next = three;
    three->next = one;

    printList(one);

    insert(&one, 4, 0);
    printList(one);

    // insert new node at the ending
    insert(&one, 5, 10);
    printList(one);

    // insert new node in the middle
    insert(&one, 7, 2);
    printList(one);

    deleteNode(&one, 10);
    printList(one);

    deleteNode(&one, 2);
    printList(one);

    deleteNode(&one, 0);
    printList(one);

    reverse(&one);
    printList(one);
    return 0;
}
