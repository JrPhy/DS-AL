#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) 
{
    int temp = *b;
    *b = *a;
    *a = temp;
}

int min(int x, int y) { return (x < y) ? x : y;}

void bubbleSort(int a[], int length)
{
    int i, j, temp;
    for(i = 0; i < length; i++) for(j = 0; j < length - 1 - i; j++) if(a[j] > a[j+1]) swap(&a[j], &a[j+1]);
}

void selectionSort(int a[], int len) 
{
    int i, j, temp;
    for (i = 0 ; i < len - 1 ; i++)
    {
        int min = i;
        for (j = i + 1; j < len; j++) if (a[j] < a[min])  min = j;  //走訪未排序的元素，找到並紀錄最小值
        if(min != i) swap(&a[min], &a[i]);
    }
}

void insertionSort(int a[], int n)
{
    int i, j, temp;
    for(i = 1; i < n; i++)
    {
        temp = a[i];
        j = i-1;
        while(j >= 0 && a[j] > temp)
        {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = temp;
    }
}

void shellSort(int a[], int n)
{
    int i, j, temp, gap;
    for (gap = n/2; gap > 0; gap /= 2)
    {
        for (i = gap; i < n; i += 1)
        {
            temp = a[i];           
            for (j = i; j >= gap && a[j - gap] > temp; j -= gap) a[j] = a[j - gap];
            a[j] = temp;
        }
    }
}

void heapify(int a[], int head, int tail)   //建立堆用
{
    int dad = head;
    int son = dad * 2 + 1;
    while (son <= tail)          // 若子節點指標在範圍內才做比較
    { 
        if (son + 1 <= tail && a[son] < a[son + 1]) son++; // 先比較兩個子節點大小，選擇最大的
        if (a[dad] > a[son]) return;                       // 如果父節點大於子節點代表調整完畢，直接跳出函數
        else                                                   // 否則交換父子內容再繼續子節點和孫節點比較
        {
            swap(&a[dad], &a[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

void heapSort(int a[], int len) 
{
    int i;
    for (i = len / 2 - 1; i >= 0; i--) heapify(a, i, len - 1);  // 建立 heap
    for (i = len - 1; i > 0; i--) 
    {
        swap(&a[0], &a[i]);  // 先將第一個元素和已排好元素前一位做交換
        heapify(a, 0, i - 1);  // 再重新調整，直到排序完畢
    }
}

int partition(int arr[], int head, int tail)
{
    int i = (head - 1);
    for (int j = head; j <= tail - 1; j++)  if (arr[j] < arr[tail]) swap(&arr[++i], &arr[j]);  
    //在此選定 arr[tail] 為 pivot，小於 pivot 放左邊，其餘放右邊
    swap(&arr[i + 1], &arr[tail]); //最後將 pivot 放到正確的位置，然後將 pivot 位置傳出來
    return (i + 1);
}
  
void quickSort(int arr[], int length)
{
    int head = 0, tail = length - 1, top = -1;
    int stack[length];
    //先將整段陣列複製出來，隨後任選一個值當作陣列 pivot 並做分段排序
    stack[++top] = head;
    stack[++top] = tail;
    while (top >= 0) 
    {
        tail = stack[top--];
        head = stack[top--];
  
        //將陣列分段後在選出下一個子陣列的 pivot 重複做，直到排序完成為止。
        int p = partition(arr, head, tail);
  
        //將 pivot 左邊的元素從左邊放入 stack
        if (p - 1 > head) 
        {
            stack[++top] = head;
            stack[++top] = p - 1;
        }
  
        //將 pivot 左邊的元素從右邊放入 stack
        if (p + 1 < tail) 
        {
            stack[++top] = p + 1;
            stack[++top] = tail;
        }
    }
}

void merge(int a[], int head, int mid, int tail) 
{
    int i, j, k;
    int n1 = mid - head + 1;
    int n2 = tail - mid;
    int L[n1], R[n2];         //左右子陣列
    for (i = 0; i < n1; i++) L[i] = a[head + i];
    for (j = 0; j < n2; j++) R[j] = a[mid + 1+ j];
    i = 0, j = 0, k = head;
    while (i < n1 && j < n2)  //此迴圈將兩子陣列的元素倆倆比較並合併進原始陣列
    {
        if (L[i] <= R[j]) a[k] = L[i++];
        else a[k] = R[j++];
        k++;
    }
    while (i < n1) a[k++] = L[i++];//若左陣列較長，則把多餘的元素放在原始陣列最末端
    while (j < n2) a[k++] = R[j++];//若右陣列較長，則把多餘的元素放在原始陣列最末端
}
 
void mergeSort(int a[], int length)
{
    int curr_size;
    int head; 
    for (curr_size = 1; curr_size <= length - 1; curr_size = 2*curr_size)  //此迴圈用來合併子陣列用
    {
        for (head = 0; head < length - 1; head += 2*curr_size)  //此迴圈用來走訪陣列中的每個元素
        {
            int mid = min(head + curr_size - 1, length - 1);
            int tail = min(head + 2*curr_size - 1, length - 1);
            merge(a, head, mid, tail);
        }
    }
}

double sortTime(int a[], int length, void (*sort)(int a[], int length))
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    sort(a, length);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    return cpu_time_used;
}
  

int main()
{
    int n = 200, a[200], b[200], c[200], d[200], e[200], f[200], g[200], i, x;
    double timeUsage;
    srand( time(NULL) );
    for(i = 0; i < n; i++)
    {
        x = rand()%300;
        a[i] = x;
        b[i] = x;
        c[i] = x;
        d[i] = x;
        e[i] = x;
        f[i] = x;
        g[i] = x;
    }
    
    timeUsage = sortTime(a, n, bubbleSort);
    printf("bubbleSort %g\n", timeUsage);
    timeUsage = sortTime(b, n, selectionSort);
    printf("selectionSort %g\n", timeUsage);
    timeUsage = sortTime(c, n, insertionSort);
    printf("insertionSortn %g\n", timeUsage);
    timeUsage = sortTime(d, n, shellSort);
    printf("shellSort %g\n", timeUsage);
    timeUsage = sortTime(e, n, mergeSort);
    printf("mergeSort %g\n", timeUsage);
    timeUsage = sortTime(f, n, quickSort);
    printf("quickSort %g\n", timeUsage);
    timeUsage = sortTime(g, n, heapSort);
    printf("heapSort %g\n", timeUsage);

    return 0;
}
