list 雖然在新增與刪除給予了很大的彈性，但是必須要先走訪到正確的位置才能動作，需要 O(n) 的時間複雜度。而在性質較好的二元樹結構，如 [AVL 樹](https://zh.wikipedia.org/wiki/AVL%E6%A0%91)、[紅黑樹](https://zh.wikipedia.org/wiki/%E7%BA%A2%E9%BB%91%E6%A0%91)等，則不需要每個元素都走訪，其複雜度僅有 O(logn)。但是對於此種樹在實作上較為複雜，所以有另一個資料結構來取兩個的優點：跳躍連結 Skip list。\
Skip list 是基於**排序過的** list 加以改善，所以在插入或刪除時不會改變元素的順序，並利用樹中**層**的概念來實現。通常會先訂一個最高的層數，而哪一個資料有幾層完全是亂數決定，用此來達到更快速的找查。而因為多了一個成員，故記憶體空間會多使用。\
此種資料結構在資料庫中會使用到，如[Redis](https://zh.wikipedia.org/wiki/Redis)。而在資料庫中通常會多一個 key 來增加尋找效率，在此並未多加入此成員。\
http://www2.ee.unsw.edu.au/~vijay/research/smallbuffersCode/skiplist/skiplist.c
https://github.com/ustcdane/skiplist/blob/master/skiplist.cpp
## 1. 結構
在跳躍連結中引入了層的概念，也就是一個元素有多一個層的元素，最底層才存放資料，如同城市中高矮不一的房子一樣，可參考[維基百科的圖](https://en.wikipedia.org/wiki/File:Skip_list_add_element-en.gif)。元素也是照順序放，但是最頂層並不會連接到所有元素，而是只會連結部分元素，越底層連結的元素越多，所以在尋找的時候可以降低複雜度，但是會增加記憶體使用量。
```C
#include <stdio.h>
#include <stdlib.h>
#define MAX_L 4

typedef struct _node
{
    int data;
    struct _node *next;
}node;

typedef struct _skiplist  
{
    int level;  
    node *header;  
}skipList;  

node *newNode(int n, int value)
{
    //這邊注意到多申請了 level*sizeof(node*)，表示這個 node 有 n 層，且每個都是 node* 要指向下一個節點
    node *tmpNode = malloc(sizeof(node) + n*sizeof(node*));
    if(tmpNode!=NULL) 
    {
        tmpNode->data = value;
        tmpNode->next = NULL;
    }
    return tmpNode;
}

skipList *newSkipList()
{
    skipList *tmpList = (skipList*)malloc(sizeof(skipList));
    if(NULL == tmpList) return NULL;

    skipList->level = 0;

    Node *tmpNode = newNode(MAX_L-1, 0, 0);//建立頭節點
    if(tmpNode == NULL)
    {
        free(skipList);
        return NULL;
    }
    skipList->head = tmpNode; //將頭節點的都先指向 NULL
    for(int i=0; i<MAX_L; ++i) tmpNode->next[i] = NULL;
    return skipList;
}
```
