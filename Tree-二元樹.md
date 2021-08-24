## 介紹

樹是一種資料結構，如現實生活中一樣，由根往上長出許多樹枝與葉子。在樹狀結構中，有一個**最上面**的節點，稱為根結點，所以資料結構中的樹與現實生活中的樹剛好相反。根結點往下會長出子節點，每個子節點不互相連結，長出子節點的節點又稱作父節點，長出的子節點可追溯到同一個父節點，如圖所示。
![image](pic/Tree.jpg)
https://udn.com/news/story/7327/5064320 \
而樹有很多種，在此以二元樹為主繼續往下介紹

## 二元樹
二元樹是一種**至多**只有兩個子節點的樹狀資料結構，如同雙向鍊結一樣可以往左或往右，但是左右不串接。也可以使用陣列實作，但是在此以結構的方式實作，並有以下性質：
1. 第 i 個 level 的節點個數最多有 2<sup>i</sup>−1 個。
2. 高度 h 的二元樹節點個數最多有 2<sup>h</sup>−1 個。 
3. 非空二元樹若 leaf 個數為 n<sub>0</sub> 個，degree 為 2 的節點個數為 n<sub>2</sub> 個，則 n<sub>0</sub> = n<sub>2</sub>+1。  
```C
struct _node
{
    int data;
    struct _node *left;
    struct _node *right;
}node;

node* newNode(int value)
{
    node *tmpNode = malloc(sizeof(node));
    if(tmpNode!=NULL) 
    {
        tmpNode->data = value;
        tmpNode->left = NULL;
        tmpNode->right = NULL;
    }
    return tmpNode;
}

int main()
{
    /* Initialize nodes */
    node *root = newNode(1);
    node *root_left = newNode(2);
    node *root_right = newNode(3);
    
    root->left = root_left;
    root->right = root_right;
}
```
