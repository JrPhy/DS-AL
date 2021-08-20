在單向或雙向鏈結中，最後一個指標會指向 NULL，但是環狀鏈結最後一個會指向頭節點，在此以單向環狀鏈結為例。

## 1. 環狀 Linked List 實作
```C
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
}
```
![image](pic/Circle-linked-list.jpg) \
除了最後要將最末端的節點指回頭，其他都與單向鏈結一樣。

## 2. 印出 list 中的資料
因為 list 的最後一個是指向 head，所以結束條件就是 list != head，但是因為一開始是從 head 進入，所以我們可以選擇先將第一個節點印出並讓 list 指向第二個，最後當 lise == head 即結束迴圈。
```C
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
```

## 3. 計算 list 長度
使用方式與印出 list 中所有元素並無不同。
```C
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
```
## 4. 增加串接資料於 list 中
由於是環狀鏈結，所以可以當作沒有頭尾，所以只要實做在中間插入即可，如果想要在定義的頭前面插入，其實就是在最尾端插入一個節點的意思。
```C
void insert(node **list, int value, int position)
{
    node *new_node = newNode(value);
    int length = lenOfList(*list)
    if(position >= length)position = position%length;
    node *temp = *list;
    for(int i = 0; i < position; i++) if(temp->next != NULL) temp = temp->next;
    new_node->next = temp->next;
    temp->next = new_node;
}
```

## 5. 刪除 list 中某位置資料
同增加資料，只要實做刪除任意點資料即可
```C
void deleteNode(node **list, int position)
{
    int length = lenOfList(*list);
    node *temp = *list;
    if(position >= length) position = position%length;
    //在此先計算 list 長度，若欲刪除之位置 > 長度，則直接刪除最後一個
    for (int i = 0; temp != NULL && i < position - 1; ++i) temp = temp->next;
    //找到要刪除的位置的前一個
    if (temp == NULL || temp->next == NULL) return;
    //如果在第二個位置就已經是 NULL 了則直接回傳，代表 list 長度為 1。
    node *nodeToBeDel = temp->next;
    //將找到的位置的前一個另外開一個指標存下來
    temp->next = nodeToBeDel->next;
    //指向要被刪除的位置的下一個。
    free(nodeToBeDel);
}
```

## 6. list 反轉
list 反轉需要另外開三個 node 才能完成，current 是要做移動，next 則是要存取移動中下一個指標，prev 則是指向前一個 node。
* 1. 將 current 指向 prve
* 2. 再將 prev 往後走一個 node
* 3. 接著將 current 往後移動一個 node
* 4. 接著重複以上三步驟直到最後一個為止
結束以上步驟後將 list 分配給 prev 即可。
```C
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
```
