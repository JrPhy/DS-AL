雖然 AVL (平衡二元樹) 可以嚴格保證在搜尋時的 TC 為 O(logn)，但是因為要嚴格地保持平衡，所以在插入與刪除時花了很多效能在修改樹上。而紅黑樹則是從 AVL 做修改，將高度改為顏色，是藉由將 node 上色來保持平衡，並有以下規則 

## 1. 規則
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

## 2. 插入
在插入的時候會預設 node 為紅色，根據紅黑樹的規則，根必為黑色，所以往下插入後會遇到 BRR 的情況就需要旋轉，也就對應 AVL 的左旋與右旋，但是旋轉後要重新上色才能遵守紅黑樹的規則
#### 1. LL 與 RR 的情況
除了跟 AVL 一樣旋轉外，還需要做變色
![1 RB TREE](https://github.com/JrPhy/DS-AL/blob/master/pic/RBTREE_LLRR.jpg)
#### 2. 兩個子節點皆為紅色
此時不論在哪邊插入皆會違反規則 3，固可先將原本的節點顏色交換，但這時又會違反規則 2 (根為紅色)，此時可以將整個樹做左旋轉符合規則。
![1 RBTREE_RBRR](https://github.com/JrPhy/DS-AL/blob/master/pic/RBTREE_RBRR.jpg)
若是插入的節點在左節點的右邊或是右節點的左邊，可先做左旋或右旋來轉成上述情況再重複上述步驟。實作時需要每種狀況都分開寫才行



