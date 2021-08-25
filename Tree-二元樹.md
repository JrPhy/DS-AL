## 介紹

樹是一種資料結構，如現實生活中一樣，由根往上長出許多樹枝與葉子。在樹狀結構中，有一個**最上面**的節點，稱為根結點，所以資料結構中的樹與現實生活中的樹剛好相反。根結點往下會長出子節點，每個子節點不互相連結，長出子節點的節點又稱作父節點，長出的子節點可追溯到同一個父節點，而最後一個子節點稱為葉，如圖所示。
![image](pic/Tree1.jpg)
https://udn.com/news/story/7327/5064320 \
而樹有很多種，在此以二元樹為主繼續往下介紹

## 二元樹
二元樹是一種**至多**只有兩個子節點的樹狀資料結構，如同雙向鍊結一樣可以往左或往右，但是左右不串接。也可以使用陣列實作，但是在此以結構的方式實作，並有以下性質：
1. 第 i 層的節點個數最多有 2<sup>i</sup>−1 個。
2. 高度 h 的二元樹節點個數最多有 2<sup>h</sup>−1 個。 
3. 非空二元樹，若葉個數為 n<sub>0</sub> 個，degree 為 2 的節點個數為 n<sub>2</sub> 個，則 n<sub>0</sub> = n<sub>2</sub>+1。  
```C
typedef struct _node
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
    node *root1_left = newNode(2);
    node *root1_right = newNode(3);
    node *root2_left = newNode(4);
    node *root2_right = newNode(5);
    
    root->left = root1_left;
    root->right = root1_right;
    root1_left->left = root2_left;
    root1_right->right = root2_right;
}
```

## 印出數中所有資料
從根進入後可以分左右進入，所以印出所有元素共有四種組合
#### 1. Preorder Traversal 前序遍歷
從根進入後先印出資料，並先將根左邊的所有子節點印出，再走到根的右邊印出，當走到最後一個節點時就會到 NULL。
```C
void preorder(node *root) 
{
    printf("%d", root->data);
    if (root->left != NULL)  //若其中一側的子樹非空則會讀取其子樹
        preorder(root->left);
    if (root->right != NULL) //另一側的子樹也做相同事
        preorder(root->right);
}
```
此程式碼使用遞迴寫法，先印出資料後，當 root->left 不為空指標再執行此函數，因為呼叫此函數是會先印出該節點的資料，所以是先由上往下，直到左邊節點全部印完再換右邊。
#### 2. Inorder Traversal 中序遍歷
從最左邊的節點開始，由左至右，由下而上(葉子到根)印出，根的左邊節點全部走訪後再到右邊節點。
```C
void inorder(node *root) 
{
    if (root->left != NULL)  //若其中一側的子樹非空則會讀取其子樹
        inorder(root->left);
    printf("%d", root->data);
    if (root->right != NULL) //另一側的子樹也做相同事
        inorder(root->right);
}
```
#### 3. Postorder Traversal 後序遍歷
從最左邊的節點開始，每一層的節點由左至右印出，最後才會印到根。
```C
void postorder(node *root) 
{
    if (root->left != NULL)  //若其中一側的子樹非空則會讀取其子樹
        postorder(root->left);
    if (root->right != NULL) //另一側的子樹也做相同事
        postorder(root->right);
    printf("%d", root->data);
}
```
可發現此三個函數幾乎一樣，只差在印出資料的程式碼位置不同。

## 二元搜尋樹
若樹中的資料都是同一種類，且按序排放，則稱為二元搜尋樹，其定義如下
1. 在"根"節點左邊的所有值皆小於根
2. 在"根"節點右邊的所有值皆大於根
3. 所有子樹皆為二元搜尋樹
4. 不存在任何鍵值 ( key/value ) 相等的節點。
因為順序排放，故在空間與算法時間上有以下結果

|  | 搜尋 | 插入 | 刪除 | 空間 | 
| --- | --- | --- | --- | --- |
| 平均 | O(logn) | O(logn) | O(logn) | O(n) |
| 最差 | O(n) | O(n) | O(n) | O(n) |

```C
typedef struct _node
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
    node *root = newNode(4);
    node *root1_left = newNode(1);
    node *root1_right = newNode(5);
    node *root2_left = newNode(3);
    node *root2_right = newNode(2);
    
    root->left = root1_left;
    root->right = root1_right;
    root1_left->left = root2_left;
    root1_right->right = root2_right;
}
```

#### 1. 搜尋
根據二元搜尋樹的元素順序，只要是比節點小的就往走，比節點大的就往右，若是 key 不在數裡面則回傳 NULL。
```C
node *search(node *root, int key) 
{
    node *current = root;
    while(current != NULL && key != current->data)
    {
        if(key > root->data) current = current->right; //若比較大則往右走
        else current  = current->left;                 //否則往左走
    }
    if(current != NULL) return current;
    else return NULL;
}
```
