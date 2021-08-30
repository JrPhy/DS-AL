此堆疊與記憶體中的 stack 不同，堆疊是一種先進後出(First In Last Out, FILO)的資料結構，也就是出入口都是同一個，像打包裝箱就是堆疊的一種，在此會以 linked-list 與 dynamic array 做示範。

## 1. 使用 dynamic array 
在此我們需要知道 stack 的容量和是否放滿，以及一個指標來指向動態陣列。其中 capacity 代表容量，top 是告訴我們是否還可以放東西進去，當 capacity == top 時表示容器已滿。接著就可以來創造容器
```C
typedef struct _stack {
    int top;
    unsigned int capacity;
    int *array;
}stack;

stack *newStack(unsigned int capacity)
{
    stack *new_stack = malloc(sizeof(stack));
    if(new_stack != NULL)
    {
        new_stack->capacity = capacity;
        new_stack->top = -1;
        new_stack->array = (int*)malloc(new_stack->capacity * sizeof(int));
    }
    if(new_stack->array == NULL) return NULL;
    else return new_stack;
}
```
在 stack 中有兩個函數，分別是放入 push 與拿出 pop，
```C
void push(stack *buffer, int data)
{
    if (buffer->top != buffer->capacity - 1) buffer->array[++buffer->top] = data;
}

int pop(stack *buffer)
{
    if (buffer->top != - 1) return buffer->array[buffer->top--];
}

void printStack(stack *buffer)
{
    for(int i = 0; i < buffer->top+1; i++) printf("%d  ", buffer->array[i]);
}

void delStack(stack *buffer)
{
    free(buffer->array);
    free(buffer);
}

```
注意到這邊使用了 ++ 與 -- 操作。a[i++] 表示先執行 a[i]，執行完後 i 再 +1。a[++i] 表示先執行 +1，執行完後 i 再執行 a[i]。所以在 push 中是先將 buffer->top = buffer->top+1，再將 data 放入 buffer->array 中。而 pop 則是先將 buffer->array[buffer->top] 回傳，再將 buffer->top = buffer->top - 1。
```C
#include <stdio.h>
#include <stdlib.h>
int main()
{
    stack *buffer = newStack(100);
    
    push(buffer, 10);
    push(buffer, 20);
    push(buffer, 30);
    printStack(buffer);
 
    printf("%d popped from stack\n", pop(buffer));
 
    return 0;
}
```

## 2. 使用 linked-list
Linked-list 的好處就是不用管陣列大小，不須像陣列一樣要先把所有空間開好，造成記憶體的浪費。因為 stack 是先進後出，所以可以使用在頭插入與刪除頭節點兩函數來時做 push 跟 pop，並使用計算 list 長度來看目前有多少元素。
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

void push(node **list, int value, int position) //insertNode
{
    node *new_node = newNode(value);
    new_node->next = *list;
    *list = new_node;
}

void pop(node **list, int position) //deleteNode
{
    node *temp = *list;
    *list = temp->next;
    free(temp);
}

void printStack(node *list)
{
    while(list != NULL)
    {
        printf("%d ", list->data);
        list = list->next;
    }
    printf("\n");
}

int main()
{
    node *top = newNode(-1);
    
    push(&top, 10, 0);
    push(&top, 20, 0);
    push(&top, 30, 0);
    printStack(top);
    pop(&top, 0);
    printStack(top);
 
    return 0;
}
```
