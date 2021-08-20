#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
    int data;
    struct _node *next, *prev;
}node;

node* newNode(int value)
{
    node *tmpNode = malloc(sizeof(node));
    if(tmpNode!=NULL)
    {
        tmpNode->data = value;
        tmpNode->next = NULL;
        tmpNode->prev = NULL;
    }
    return tmpNode;
}

void printList(node *list)
{
    node *address = list;
    while(list->next != NULL)
    {
        printf("%d->", list->data);
        list = list->next;
    }
    printf("%d\n", list->data);

    while(list->prev != NULL)
    {
        printf("%d->", list->data);
        list = list->prev;
    }
    printf("%d\n", list->data);
    printf("\n");

}

void printListAddress(node *list)
{
    while(list != NULL)
    {
        printf("%p->", list->prev);
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
    int length = 0;
    while(temp != NULL)
    {
        length += 1;
        temp = temp->next;
    }
    /* insert at the beginning*/
    node *new_node = newNode(value);
    if(position < 1)
    {
        (*list)->prev = new_node;
        new_node->next = *list;
        *list = new_node;
    }
    /* insert at the beginning*/
    /* insert at the ending*/
    else if (position >= length + 1)
    {
        node *temp = *list;
        while(temp->next != NULL) temp = temp->next;
        temp->next = new_node;
        new_node->prev = temp;
    }
    /* insert at the ending*/
    /* insert at the middle*/
    else
    {
        node *temp = *list;
        for(int i = 1; i < position; i++) if(temp->next != NULL) temp = temp->next;

        new_node->next = temp->next;
        temp->next = new_node;
        new_node->prev = temp;
        new_node->next->prev = new_node;
    }
    /* insert at the middle*/
}

void deleteNode(node **list, int position)
{

    if (*list == NULL) return;

    node *temp = *list;
    int length;
    if (position <= 0)
    {
        *list = temp->next;
        temp->next->prev = NULL;
        free(temp);
        return;
    }
    else
    {
        length = lenOfList(*list);
        if (position >= length) position = length - 1;
    }

    for (int i = 0; temp != NULL && i < position - 1; ++i) temp = temp->next;

    if (temp == NULL || temp->next == NULL) return;

    node *nodeToBeDel = temp->next, *temp2;
    if(nodeToBeDel->next == NULL)
    {
        temp->next = nodeToBeDel->next;
    }
    else
    {
        temp2 = nodeToBeDel->next;
        temp->next = temp2;
        temp2->prev = temp;
    }
    free(nodeToBeDel);
}

void reverse(node **list)
{
    node *temp = NULL, *current = *list;
    while(current != NULL)
    {
        current->prev = current->next;
        current->next = temp;
        temp = current;
        current = current->prev;
    }
    *list = temp;
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
    three->next = NULL;

    one->prev = NULL;
    two->prev = one;
    three->prev = two;
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

    deleteNode(&one, 2);
    printList(one);

    reverse(&one);
    printList(one);
    reverse(&one);
    printList(one);

    return 0;
}
