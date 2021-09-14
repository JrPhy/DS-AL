在排序算法種類若依照排序方式分類，可分成比較與非比較兩大類。若有 n 個元素要做排序，在比較算法中所需的時間複雜度目前最低就是 O(nlogn)，也就是將資料中兩個資料兩兩比較，最後就可以做排序。而非比較算法則非使用比較算法，有 n 個元素要做排序，數值為 0~k，時間複雜度可以是 O(n+k)。\
若是照穩定性，也就是兩個相同的元素位置會不會互換，可分成穩定與不穩定。穩定的算法對於相同值的元素不會改變其位置。例如有一陣列 a[6] = {9, 3, 4, 5, 5, 6}，在做排序時可能會將 a[3] 和 a[4] 交換位置，若是一組資料結構不只一個 key，則不穩定的演算法會增加排序開銷。例如有一資料結構有學生學號與學生分數，原本是依照學號依序排序，現想將分數由大到小排序，而在相同分數下希望依照學生學號排序，這時不穩定的算法就有可能將原本已排好的學號錯置。\
``` (101, 60)、(102, 50)、(103, 60)、(104, 66)、(105, 58)、(106, 40)``` --> 排序後 ---> ``` (104, 66)、(103, 60)、(101, 60)、(105, 58)、(102, 50)、(106, 40)```\
在維基百科中有將多數排序算法的時間複雜度、空間複雜度、穩定性做整理。較常見的排序算法有 Quick Sort、Merge Sort、Heap Sort，在此會介紹以上所提到的算法與 Bubble Sort。 https://en.wikipedia.org/wiki/Sorting_algorithm

## 1. 氣泡排序法 Bubble Sort
氣泡排序法是最直覺可以想到的排序方法，主要就是將兩元素拿來做比較，先用一個 index 從頭開始掃，再用另外一個 index 與**相鄰**元素比較，此種作法在升序排列中，第一步會將最大值擺到最後，所以共需要  n(n+1)/2 步，時間複雜度為 O(n<sup>2</sup>)。其過程像是泡泡依樣從下面跑上來，故稱氣泡排序法。而在算法中僅需要多一個變數即可完成，故空間複雜度為 O(1)。若兩元素相等，則不執行交換，故為穩定的算法。
```C
#include <stdio.h>

void bubbleSort(int a[], int length)
{
    int i, j, temp;
    for(i = 0; i < length; i++)
    {
        for(j = 0; j < length - 1 - i; j++)
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}
```
```
9  7  4  5  8  6  //一開始
7  4  5  8  6  9  
4  5  7  6  8  9  
4  5  6  7  8  9  
4  5  6  7  8  9  
4  5  6  7  8  9  
4  5  6  7  8  9  
4  5  6  7  8  9
```

## 2. 合併排序法 Merge Sort
1945 年由 John von Neumann 提出。從氣泡排序法可以看到，比較排序一定要將所有元素走訪一次，然後再讓元素倆倆比較，所以能改善的就是如何更有效率的比較兩元素。而合併排序法是將整個資料結構分成兩部分，一直分到每個部份僅有一個元素，然後倆倆比較後再合併，在比較過程中若兩元素相同則不會交換位置，固為穩定的排序算法。所以第一步是拆分，第二步是比較並合併。
因為每次合併都需要走訪 n 個元素，而合併需 log<sub>2</sub>n 步，要共需走訪 log<sub>2</sub>n 次，故共為 nlog<sub>2</sub>n 步，故時間複雜度為 O(nlog<sub>2</sub>n)，且因為是倆倆比較，所以不論是何種情況所需的時間複雜度為 O(nlog<sub>2</sub>n)。\
而在合併的過程中最多需要額外相同長度的記憶體空間，故空間複雜度為 O(n)。
```C
#include<stdio.h>
void merge(int arr[], int head, int mid, int tail) 
{
    int i, j, k;
    int n1 = mid - head + 1;
    int n2 = tail - mid;
    int L[n1], R[n2];         //左右子陣列
    for (i = 0; i < n1; i++) L[i] = arr[head + i];
    for (j = 0; j < n2; j++) R[j] = arr[mid + 1+ j];
    i = 0, j = 0, k = head;
    while (i < n1 && j < n2)  //此迴圈將兩子陣列的元素倆倆比較並合併進原始陣列
    {
        if (L[i] <= R[j]) 
        {
            arr[k] = L[i];
            i++;
        } 
        else 
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)           //若左陣列較長，則把多餘的元素放在原始陣列最末端
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)           //若右陣列較長，則把多餘的元素放在原始陣列最末端
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

int min(int x, int y) { return (x < y) ? x : y;}
 
void mergeSort(int arr[], int length)
{
    int curr_size;
    int head; 
    for (curr_size = 1; curr_size <= length - 1; curr_size = 2*curr_size)  //此迴圈用來合併子陣列用
    {
        for (head = 0; head < length - 1; head += 2*curr_size)  //此迴圈用來走訪陣列中的每個元素
        {
            int mid = min(head + curr_size - 1, length - 1);
            int tail = min(head + 2*curr_size - 1, length - 1);
            merge(arr, head, mid, tail);
        }
    }
}
```

## 3. 快速排序法 Quick Sort
不同於合併排序，快速排序法並不一定會將資料等分，而是在取陣列中的某個值當作二元樹的 root，接著若比 root 大就放右邊，反之放左邊。所以在最差的情況，也就是要將資料升序排列，但資料已經以降序的方式排列好了，需要 O(n<sup>2</sup>) 的時間複雜度。而一般情況下則是需要 O(nlog<sub>2</sub>n)。\

```C
#include <stdio.h>
void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
  
int partition(int arr[], int l, int h)
{
    int x = arr[h];
    int i = (l - 1);
  
    for (int j = l; j <= h - 1; j++) {
        if (arr[j] <= x) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[h]);
    return (i + 1);
}
  
/* A[] --> Array to be sorted, 
   l  --> Starting index, 
   h  --> Ending index */
void quickSortIterative(int arr[], int l, int h)
{
    // Create an auxiliary stack
    int stack[h - l + 1];
  
    // initialize top of stack
    int top = -1;
  
    // push initial values of l and h to stack
    stack[++top] = l;
    stack[++top] = h;
  
    // Keep popping from stack while is not empty
    while (top >= 0) {
        // Pop h and l
        h = stack[top--];
        l = stack[top--];
  
        // Set pivot element at its correct position
        // in sorted array
        int p = partition(arr, l, h);
  
        // If there are elements on left side of pivot,
        // then push left side to stack
        if (p - 1 > l) {
            stack[++top] = l;
            stack[++top] = p - 1;
        }
  
        // If there are elements on right side of pivot,
        // then push right side to stack
        if (p + 1 < h) {
            stack[++top] = p + 1;
            stack[++top] = h;
        }
    }
}
```

最後可產生一亂數來比較各排序算法所需的時間
```C
int main()
{
    int n = 20, a[20], b[20], i, x;
    srand( time(NULL) );
    for(i = 0; i < n; i++)
    {
        x = rand()%300;
        a[i] = x;
        b[i] = x;
    }

    clock_t start, end;
    start = clock();
    
    bubbleSort(a, n);
    
    end = clock();
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("bubbleSort %g\n", cpu_time_used);

    start = clock();
    
    mergeSort(b, n);
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("mergeSort  %g\n", cpu_time_used);
    
    for(i = 0; i < n; i++) printf("%d, ", a[i]);
    printf("\n");
    for(i = 0; i < n; i++) printf("%d, ", b[i]);
    return 0;
}
```
