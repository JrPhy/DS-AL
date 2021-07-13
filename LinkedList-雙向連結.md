與單向連結相比，雙向連結在結構上多了一個指標，每個會比單向多出 4 Byte/8 Byte，但在使用上會比單向更自由方便。

## 1. 雙向 Linked List 實作
在結構上比單向多了一個 * prev，且在串接上要將尾端的 * prev 往前指向前一個 node 的 prev。
```C
#include <stdio.h>
#include <stdlib.h>

struct _node
{
    int data;
    struct _node *next;
    struct _node *prev;
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
    node *head = one, *tail = three;
}
```
![image](pic/Double-linked-list.jpg)

## 2. 印出 list 中的資料
雙向連結因為多了一個 prev 所以從後面往前印。
```C
void printList(node *list)
{
    while(list != NULL)
    {
        printf("%d\n", list->data);
        list = list->prev;
    }
}
```
而由前往後印與計算 list 長度皆與單向相同，故在此不再贅述。

## 3. 增加串接資料於 list 中
一般來說要改變陣列大小需用 malloc 宣告新陣列的大小，然後在將舊陣列 free，但使用 list，我們只要找到想插入的位置就可以了。在此分三種情況

#### 1. 在首插入
與單向連結大致上相同，但要記得傳入的 list 中的 prev 要指向 newNode。
```C
void insertHead(node **list, int value)
{
    node *new_node = newNode(value);
    (*list)->prev = newNode;
    newNode->next = *list;
    *list = newNode;
}
```

#### 1. 在尾插入
與單向連結大致上相同，但要記得傳入的 list 中的 prev 要指向 newNode。
```C
void insertHead(node **list, int value)
{
    node *new_node = newNode(value);
    (*list)->prev = newNode;
    newNode->next = *list;
    *list = newNode;
}
```
