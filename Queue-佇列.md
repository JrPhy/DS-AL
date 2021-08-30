佇列是一種先進後出(First In Fast Out, FIFO)的資料結構，也就是有一個入口與一個出口，像水管就是佇列的一種，在此會以 linked-list 與 dynamic array 做示範。

## 1. 使用 dynamic array
因為是有一進一出，所以會比 stack 多一個 flag。其中 capacity 代表容量，top 是告訴我們是被第一個放進去的位置，bottom 則是最後一個，當 capacity == bottom + 1 時表示容器已滿。接著就可以來創造容器
```C
typedef struct _queue {
    int top, bottom;
    unsigned int capacity;
    int *array;
}queue;

stack *newQueue(unsigned int capacity)
{
    stack *new_queue = malloc(sizeof(queue));
    if(new_queue != NULL)
    {
        new_queue->capacity = capacity;
        new_queue->top = 0;
        new_queue->bottom = -1;
        new_queue->array = (int*)malloc(new_stack->capacity * sizeof(int));
    }
    if(new_queue->array == NULL) return NULL;
    else return new_queue;
}
```
因為是先進先出，所以在此是將 bottom + 1。在 queue 中主要有兩個函數，分別是放入 enqueue 與拿出 dequeue，
```C
void enqueue(queue *buffer, int data)
{
    if (buffer->bottom != buffer->capacity - 1) buffer->array[++buffer->bottom] = data;
}
int dequeue(queue *buffer)
{
    if (buffer->bottom != - 1) return buffer->array[buffer->bottom--];
}
void printQueue(queue *buffer)
{
    for(int i = top; i < buffer->bottom+1; i++) printf("%d  ", buffer->array[i]);
}

void delQueue(queue *buffer)
{
    free(buffer->array);
    free(buffer);
}
```
