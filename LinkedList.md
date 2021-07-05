在 C 語言中內建的組合型別有陣列、結構、聯合、枚舉、函數等，陣列只能夠裝相同型別的物件，結構可裝不同型別的成員，而結構陣列只能裝相同類別的成員，若要自由的增減陣列內的成員，可搭配 malloc 與 free，但都不如 python 中的 list 方便。故在 C 語言中若要像 python 的 list 一樣就必須自己實作，在此稱為Linked List。

## 1. Linked List 實作
Linked List 的結構為許多的成員與勾環，此鉤環是與其他 list 串接的成員
```C
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
};

int main()
{
    /* Initialize nodes */
    struct node *one = NULL, *two = NULL, *three = NULL; //指標用 NULL 初始化是好習慣

    /* Allocate memory */
    one = malloc(sizeof(struct node));
    two = malloc(sizeof(struct node));
    three = malloc(sizeof(struct node));

    /* Assign data values */
    one->data   = 1;
    two->data   = 2;
    three->data = 3;

    // connect the node
    one->next = two;
    two->next = three;
    three->next = NULL;
}
```
上面宣告了一個結構，裡面有一個整數變數的成員，與一個指標結構成員 * next，* next 即為用來與其他資料連結的鉤環。在此我們先宣告三個型別為 node 的指標並先指向 NULL，接著分別要了 node 大小的記憶體給三個指標。接著將裡面的資料賦值然後將其串起來，如此一來就完成了 Linked list 的串接。

## 2. 印出 list 中的資料
因為 list 的最後一個是指向 NULL，故當傳入一個 node 的結構指標，只要指標不為 NULL，就都印出來，印出來後指向下一個。
```C
void printLinkedList(struct node *p)
{
    while(p != NULL)
    {
        printf("%d\n", p->data);
        p = p->next;
    }
}
```

## 3. 增加串接資料於 list 中
一般來說要改變陣列大小需用 malloc 宣告新陣列的大小，然後在將舊陣列 free，但使用 list，我們只要找到想插入的位置就可以了。在此分三種情況
#### 1. 在首插入
若有一個資料想放在 list 首，就先在裡面開一個新的 node 指標 newNode，將 data 放進去後，newNode 裡面的 next 指向原本的頭，最後再將 list 指向 newNode 即可。
```C
void insertHead(struct node **list, int value)
{
    struct node *newNode;
    newNode = malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = *list;
    *list = newNode;
}
```
在此傳入一個指標的指標，是因為要改變原本的指標。
#### 2. 在尾插入
大部分的步驟一樣，只不過 newNode 最後要指向 NULL，然後另外開一個指標 temp 指向 list，找到目前存在 list 中最後一項物件，再把 temp 指向 newNode 即可。
```C
void insertMiddle(struct node **list, int value)
{
    struct node *newNode;
    newNode = malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;
    struct node *temp = *list;  //因為是一個指標的指標，所以我們要先開一個新的 node 指標只向 list
    while(temp->next != NULL) temp = temp->next;
    temp->next = newNode;
}
```
#### 3. 在其他地方插入
大部分的步驟一樣，只不過要將第 n 個 node 指向 newNode，newNode 指向第 n+1 個 node，這樣就完成串接了。
```C
void insertMiddle(struct node **list, int value, int n)
{
    struct node *newNode;
    newNode = malloc(sizeof(struct node));
    newNode->data = value;
    struct node *temp = *list;
    for(int i = 1; i < n; i++) if(temp->next != NULL) temp = temp->next;
    newNode->next = temp->next;
    temp->next = newNode;
}
```
