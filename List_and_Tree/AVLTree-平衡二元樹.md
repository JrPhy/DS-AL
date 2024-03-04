對於一棵二元數來說，有可能在插入或刪除的過程中，讓整棵樹退化成 [linked-list](https://github.com/JrPhy/DS-AL/blob/master/List_and_Tree/LinkedList-%E5%96%AE%E5%90%91%E9%80%A3%E7%B5%90.md)，做插入與搜尋時的 TC 就會到 O(n)，為了讓整體的效能更好，會希望根的左右兩邊節點數量差不多，所以就有平衡二元樹這個概念。
![圖一Bad Tree](https://github.com/JrPhy/DS-AL/blob/master/pic/bad_tree.jpg)

## 1. AVLTree-平衡二元樹
上圖的最上面兩個例子就是幾乎退化成 linked-list 的例子，為了把一些節點放到右邊，會對這棵樹做一些操作，稱為**旋轉**。首先我們會先需要計算樹的高度。
#### 1. 計算高度
在計算樹的高度時，會將節點為 null 的部分標為 -1，取同一層的節點最大的數值 +1，就是該節點的高度，如上圖所示。在此就可以計算樹的高度
如此一來就可以定義平衡因子 BF，並定義以下三種情況：
1. BF > 1 --> 節點幾乎都在右邊
2. 1 <= BF <= 1 --> 平衡
3. BF < -1 --> 節點幾乎都在左邊
也就是該節點的左子節點高度減去右子節點高度，以圖一的根為例子，左子節點高度為 3，右子節點高度 0，故此樹的平衡因子 = 3，故該棵樹為一個節點偏向左邊的樹，所以必須要在每個節點都存入當下的高度。
```C
typedef struct _node
{
    int data;
    int height;
    struct _node *left;
    struct _node *right;
}node;

node* newNode(int value)
{
    node *tmpNode = malloc(sizeof(node));
    if(tmpNode!=NULL) 
    {
        tmpNode->data = value;
        tmpNode->height = 1;
        tmpNode->left = NULL;
        tmpNode->right = NULL;
    }
    return tmpNode;
}

int get_bf(node *N)  
{  
    if (N == NULL)  
        return 0;  
    return height(N->left) - height(N->right);  
}  
```
#### 2. 平衡調整
實作時一般會先設定這棵樹為平衡二元樹，當資料插入樹之後會去做**動態**調整。做調整時會要求 in-order traversal 結果不變，此調整稱為**旋轉 rotation**，並且保持二元樹的性質，也就是右節點的數值 > 左節點
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
#### 3. 旋轉
若是原本有一棵樹高度為 1 且為左 node 如圖二，則插入 5 以後就會變成高度為 2 的樹，此時就不是平衡二元樹了。這時我們只要將原本的根放到右節點即可滿足平衡二元樹的定義，此稱為右旋，也就是把 root 的位置放到左子節點的右邊，此時左此節點就變成新的根，反之為左旋(圖三)。
![右旋](https://github.com/JrPhy/DS-AL/blob/master/pic/TREE_right_rotation.jpg.jpg)
![左旋](https://github.com/JrPhy/DS-AL/blob/master/pic/TREE_left_rotation.jpg.jpg)
```C
int max(int a, int b) { return (a > b)? a : b; } 

node *rightRotate(node *n)  
{  
    node *x = n->left; // 左子節點
    node *T2 = x->right; // 左子節點的右邊
  
    // Perform rotation  
    x->right = n; // 放到左子節點的右邊
    n->left = T2;  
  
    // Update heights  
    n->height = max(height(n->left), height(n->right)) + 1;  
    x->height = max(height(x->left), height(x->right)) + 1;  
    // Return new root  
    return x;  
}  
 
node *leftRotate(node *x)  
{  
    node *y = x->right;  
    node *T2 = y->left;  
  
    // Perform rotation  
    y->left = x;  
    x->right = T2;  
  
    // Update heights  
    x->height = max(height(x->left),     
                    height(x->right)) + 1;  
    y->height = max(height(y->left),  
                    height(y->right)) + 1;  
  
    // Return new root  
    return y;  
}  
```
