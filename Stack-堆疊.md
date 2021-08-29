此堆疊與記憶體中的 stack 不同，堆疊是一種先進後出的資料結構，也就是出入口都是同一個，像打包裝箱就是堆疊的一種，在此會以 linked-list 與 dynamic array 做示範。

## 1. 使用 dynamic array 
在此我們需要知道 stack 的容量和是否放滿，以及一個指標來指向動態陣列。其中 capacity 代表容量，top 是告訴我們是否還可以放東西進去，當 capacity == top 時表示容器已滿。接著就可以來創造容器
```C
typedef struct _stack {
    char top;
    unsigned int capacity;
    int *array;
}stack;

stack *createStack(unsigned int capacity)
{
    stack *new_stack = (stack*)malloc(sizeof(stack));
    if(new_stack->array != NULL)
    {
        new_stack->capacity = capacity;
        new_stack->top = -1;
        new_stack->array = (int*)malloc(new_stack->capacity * sizeof(int));
    }
    if(new_stack->array == NULL) return NULL;
    else return stack;
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
```
注意到這邊使用了 ++ 與 -- 操作。a[i++] 表示先執行 a[i]，執行完後 i 再 +1。a[++i] 表示先執行 +1，執行完後 i 再執行 a[i]。所以在 push 中是先將 buffer->top = buffer->top+1，再將 data 放入 buffer->array 中。而 pop 則是先將 buffer->array[buffer->top] 回傳，再將 buffer->top = buffer->top - 1。
