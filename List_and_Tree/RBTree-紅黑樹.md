雖然平衡二元樹可以嚴格保證在搜尋時的 TC 為 O(logn)，但是因為要嚴格地保持平衡，所以在插入與刪除時花了很多效能在修改樹上。而紅黑樹則是從平衡二元樹做修改，將高度改為顏色，是藉由將 node 上色來保持平衡，並有以下規則 [1]
1. 節點是紅色或黑色。
2. 根和所有葉子 (nil) 都是黑色。
3. 每個紅色節點的兩個子節點必須為黑色節點。
4. 從任一節點到其每個葉子的所有簡單路徑都包含相同數目的黑色節點。
下面是一個具體的紅黑樹的圖例：
![1 RB TREE](https://github.com/JrPhy/DS-AL/blob/master/pic/RBTREE.png)
```C
typedef struct _node
{
    int data;
    char color;
    struct _node *left;
    struct _node *right;
    struct _node *parent;
}node;
```
根據紅黑樹的定義，規則 3 和 4 保證了紅黑樹的最短路徑(全黑) <= 2*最長路徑(黑紅交錯)。
![1 RB TREE](https://github.com/JrPhy/DS-AL/blob/master/pic/RBTREE_max_length.jpg)

## 1. 旋轉與變色
根據紅黑樹的規則，跟必為黑色，所以往下插入後會遇到 BRR 的情況就需要旋轉，也就對應平衡二元樹的左旋與右旋，但是旋轉後要重新上色才能遵守紅黑樹的規則

