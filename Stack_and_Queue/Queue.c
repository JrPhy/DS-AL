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
    if ((buffer->bottom + 1) % buffer->capacity == buffer->top)
    {printf("queue is full");}
    else
    {
        ++buffer->bottom;
        buffer->array[buffer->bottom] = data;
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
    else printf("queue is empty");
}

void printQueue(queue *buffer)
{
    for(int i = 0; i < buffer->bottom+1; i++) printf("%d  ", buffer->array[i]);
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
