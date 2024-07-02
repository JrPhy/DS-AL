佇列是一種先進後出(First In Fast Out, FIFO)的資料結構，也就是有一個入口與一個出口，像水管就是佇列的一種，此以 dynamic array 做示範單端隊列，STL 中的為雙端隊列。

## 1. 使用 array
因為是有一進一出，所以會比 stack 多一個 flag。其中 capacity 代表容量，front 是告訴我們是被第一個放進去的位置，rear 則是最後一個，當 capacity == front + 1 時表示容器已滿。接著就可以來創造容器。因為是先進先出，所以在此是將 front + 1。在 queue 中主要有兩個函數，分別是放入 enqueue 與拿出 dequeue，然而在 dequeue 是從頭出去，所以要將每個資料往前移一格。 \
註：一般陣列或是動態陣列都可以，在此以動態陣列示範。
```C
#include <stdio.h>
#include <stdlib.h>
typedef struct _queue 
{
    int rear, front, size;
    int capacity;
    int *array;
}queue;

queue *newQueue(int capacity)
{
    queue *new_queue = malloc(sizeof(queue));
    if(new_queue != NULL)
    {
        new_queue->capacity = capacity;
        new_queue->rear = 0;
        new_queue->front = 0;
        new_queue->size = 0;
        new_queue->array = (int*)malloc(new_queue->capacity * sizeof(int));
    }
    if(new_queue->array == NULL) return NULL;
    else return new_queue;
}

void enqueue(queue *buffer, int data)
{
    if (buffer->front < buffer->capacity) 
    {
        buffer->array[buffer->front] = data;
        ++buffer->front;
    }
    else printf("queue is full");
}

int dequeue(queue *buffer)
{
    if (buffer->front > 0)
    {
        int _dequeue = buffer->array[0];
        --buffer->front;
        for(int i = 0; i < buffer->front+1; i++)
        {buffer->array[i] = buffer->array[i+1];}
        return _dequeue;
    }
    else printf("queue is empty");
}

void printQueue(queue *buffer)
{
    for(int i = 0; i < buffer->front; i++)
    {printf("%d  ", buffer->array[i]);}
    printf("\n");
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
    enqueue(buffer, 60);
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

## 2. 環狀佇列 Array 版
由上面可知，不論是 stack 或是 quene，若是使用 array 的方式，當放滿了勢必要將其他的元素拿出來或是重新開一陣列，在使用上彈性沒有很大。在此可以使用環狀佇列，也就是仿照環狀鏈結的方式將尾接到頭，但實際上 array 就是線性的，所以會利用 **餘數(mod)** 操作來達成 array 的環狀佇列。 \
例如一長度為 5 的陣列，及 index 分別為 0, 1, 2, 3, 4，當長度為 n，陣列的 index 為 0, 1, ..., n-1，所以在 enqueue 和 dequeue 就可以利用這性質實作。

#### enqueue
在環狀佇列中可以另外加上一個 size 來方便使用，如果佇列未滿，則可以直接放入新的元素。若佇列滿了，則需先執行 dequeue 再將新的元素放入佇列中。而判斷佇列是否滿不像線性佇列這麼單純，因為 rear 與 front 會經過任何一個 index，所以當 size == capacity 時表示佇列已經放滿了，反之當 size == 0 表示為空。
```C
void enqueue(queue *buffer, int data)
{
    if (buffer->size == buffer->capacity)
    {printf("queue is full");}
    else
    {
        ++buffer->size;
        buffer->array[buffer->front] = value;
        buffer->front = (buffer->front+1)%buffer->capacity;
    }
}
```
#### dequeue
同 enqueue，若環狀佇列放滿了，此時要先將頭元素移出，然後將 top 往後移一格，且 bottom 也往後移一格，這樣才能達到排隊的效果。而如果沒放滿要出隊，則直接將 top 往後移一格即可。
```C
void dequeue(queue *buffer)
{
    if (buffer->size != 0;)
    {
        --buffer->size;
        buffer->rear = (buffer->rear + 1) % buffer->capacity;
    }
    else printf("queue is empty");
}
```

## 3. Priority Queue
在工作中事情會一直來，且有些急迫性高的事情會在較晚的時間近來，若急迫性一樣則會依照先來後到的順序解決，但是若有優先序更高的就會將該任務移到最前面解決，這就是 Priority Queue，也就是對樹狀結構進行排序。而此排序算法通常會使用 [Heap Sort](https://github.com/JrPhy/DS-AL/blob/master/Sorting_for_array_O(nlogn)-%E6%8E%92%E5%BA%8F.md#3-%E5%A0%86%E7%A9%8D%E6%8E%92%E5%BA%8F%E6%B3%95-heap-sort)，
