佇列是一種先進後出(First In Fast Out, FIFO)的資料結構，也就是有一個入口與一個出口，像水管就是佇列的一種，在此會以 linked-list 與 dynamic array 做示範。

## 1. 使用 array
因為是有一進一出，所以會比 stack 多一個 flag。其中 capacity 代表容量，top 是告訴我們是被第一個放進去的位置，bottom 則是最後一個，當 capacity == bottom + 1 時表示容器已滿。接著就可以來創造容器。因為是先進先出，所以在此是將 bottom + 1。在 queue 中主要有兩個函數，分別是放入 enqueue 與拿出 dequeue，然而在 dequeue 是從頭出去，所以要將每個資料往前移一格。 \
註：一般陣列或是動態陣列都可以，在此以動態陣列示範。
```C
#include <stdio.h>
#include <stdlib.h>
typedef struct _queue 
{
    int top, bottom;
    unsigned int capacity;
    int *array;
}queue;

queue *newQueue(unsigned int capacity)
{
    queue *new_queue = malloc(sizeof(queue));
    if(new_queue != NULL)
    {
        new_queue->capacity = capacity;
        new_queue->top = 0;
        new_queue->bottom = 0;
        new_queue->array = (int*)malloc(new_queue->capacity * sizeof(int));
    }
    if(new_queue->array == NULL) return NULL;
    else return new_queue;
}

void enqueue(queue *buffer, int data)
{
    if (buffer->bottom < buffer->capacity) 
    {
        buffer->array[buffer->bottom] = data;
        ++buffer->bottom;
    }
    else
    {
        printf("queue is full");
        exit(0);
    }
}

int dequeue(queue *buffer)
{
    if (buffer->bottom > 0)
    {
        int _dequeue = buffer->array[0];
        --buffer->bottom;
        for(int i = 0; i < buffer->bottom+1; i++) buffer->array[i] = buffer->array[i+1];
        return _dequeue;
    }
    else
    {
        printf("queue is expty");
        exit(0);
    }
}

void printQueue(queue *buffer)
{
    for(int i = 0; i < buffer->bottom; i++) printf("%d  ", buffer->array[i]);
}

void delQueue(queue *buffer)
{
    free(buffer->array);
    free(buffer);
}

int main()
{
    queue *buffer = newQueue(5);
    
    enqueue(buffer, 10);
    enqueue(buffer, 20);
    enqueue(buffer, 30);
    enqueue(buffer, 40);
    enqueue(buffer, 50);
    enqueue(buffer, 60); //會 exit
    printQueue(buffer);
    dequeue(buffer);
    printQueue(buffer);
    dequeue(buffer);
    printQueue(buffer);
    dequeue(buffer);
    printQueue(buffer);
    dequeue(buffer);
    printQueue(buffer);
    dequeue(buffer);
    printQueue(buffer);
    dequeue(buffer);
    
    return 0;
}
```

## 環狀佇列 Array 版
由上面可知，不論是 stack 或是 quene，若是使用 array 的方式，當放滿了勢必要將其他的元素拿出來或是重新開一陣列，在使用上彈性沒有很大。在此可以使用環狀佇列，也就是仿照環狀鏈結的方式將尾接到頭，但實際上 array 就是線性的，所以會利用 **餘數(mod)** 操作來達成 array 的環狀佇列。 \
例如一長度為 5 的陣列，及 index 分別為 0, 1, 2, 3, 4，當長度為 n，陣列的 index 為 0, 1, ..., n-1，所以在 enquene 和 dequene 就可以利用這性質實作。

#### enquene
在環狀佇列中，如果佇列未滿，則可以直接放入新的元素。若佇列滿了，則需先執行 dequene 再將新的元素放入佇列中。而判斷佇列是否滿不像線性佇列這麼單純，因為 top 與 bottom 會經過任何一個 index，所以當 (bottom + 1) % capacity == top 時表示佇列已經放滿了。
```C
void enqueue(queue *buffer, int data)
{

}
```
同 enqueue，若環狀佇列放滿了，此時要先將頭元素移出，然後將 top 往後移一格，且 bottom 也往後移一格，這樣才能達到排隊的效果。而如果沒放滿要出隊，則直接將 top 往後移一格即可。
```C
int dequeue(queue *buffer)
{

}
```
