對於一棵二元樹來說，有可能在插入或刪除的過程中，讓整棵樹退化成 [linked-list](https://github.com/JrPhy/DS-AL/blob/master/List_and_Tree/LinkedList-%E5%96%AE%E5%90%91%E9%80%A3%E7%B5%90.md)，做插入與搜尋時的 TC 就會到 O(n)，為了讓整體的效能更好，會希望根的左右兩邊節點數量差不多，所以就有平衡二元樹這個概念。
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
#### 2. 插入
實作時一般會先設定這棵樹為平衡二元樹，當資料插入樹之後會去做**動態**調整，稱此調整稱為**旋轉 rotation**，並且保持二元樹的性質，也就是右節點的數值 > 左節點。若是原本有一棵樹高度為 1 且為左 node 如圖二，則插入 5 以後就會變成高度為 2 的樹，此時就不是平衡二元樹了。這時我們只要將原本的根放到右節點即可滿足平衡二元樹的定義，此稱為右旋 (LL，偏左邊)，也就是把 root 的位置放到左子節點的右邊，此時左此節點就變成新的根，反之為左旋 (RR，偏右邊)(圖三)。
![右旋 LL，偏左邊](https://github.com/JrPhy/DS-AL/blob/master/pic/AVL_TREE_R_rotation.jpg)
![左旋 RR，偏右邊](https://github.com/JrPhy/DS-AL/blob/master/pic/AVL_TREE_L_rotation.jpg)
```C
int max(int a, int b) { return (a > b)? a : b; } 
/*
      10 (y)                           8  (new y)
     /                               /   \ x->right
    8 *x = y->left                  5    10 (old y)
   / \                    -->
  5   *T2 = x->right
*/

node *rightRotate(node *y) 
{ 
    node *x = y->left; // 左子節點 8
    node *T2 = x->right; // 左子節點的右邊
  
    x->right = y; // 左子節點的放原本的 y
    y->left = T2; // y 的左邊放原本 x 的右邊
    // x 的左邊都沒動到
    // Update heights 
    y->height = max(height(y->left), height(y->right)) + 1; 
    x->height = max(height(x->left), height(x->right)) + 1; 
    return x; 
}
 
node *leftRotate(node *x)  
{
    // 反過來想即可
    node *y = x->right;  
    node *T2 = y->left;  
    y->left = x;  
    x->right = T2;  
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;  
}  
```
而另外兩種狀況是 LR 跟 RL，LR 可以先將左子節點當作 RR 做左旋轉成 LL，然後做 LL 的操作，RL 則是反過來
![右旋 LL，偏左邊](https://github.com/JrPhy/DS-AL/blob/master/pic/AVL_TREE_LR.jpg)
![左旋 RR，偏右邊](https://github.com/JrPhy/DS-AL/blob/master/pic/AVL_TREE_RL.jpg)
```C
node* insert(node *n, int key)
{
    if (n == NULL) return(newNode(key)); 
    if (key < n->key) n->left = insert(n->left, key); 
    else if (key > node->key) n->right = insert(n->right, key); 
    else return n; // 已存在於樹中

    // 計算插入後的高度
    n->height = 1 + max(height(n->left), height(n->right)); 
  
    // 檢查是否平衡
    int balance = getBalance(n);
  
    // LL
    if (balance > 1 && key < n->left->key) return rightRotate(n); 
  
    // RR
    if (balance < -1 && key > n->right->key) return leftRotate(n); 
  
    // LR
    if (balance > 1 && key > n->left->key) 
    { 
        node->left =  leftRotate(n->left); 
        return rightRotate(n); 
    } 
  
    // RL
    if (balance < -1 && key < n->right->key) 
    { 
        n->right = rightRotate(n->right); 
        return leftRotate(n); 
    } 
    return node;
}
```
#### 3. 尋找
與二元樹尋找無差異，不再贅述

#### 4. 刪除
刪除的情況會比插入在複雜一點，除了上述的情況外還多了兩種，也就是被刪除的兩個節點下面都還有非葉子的節點，在此就只多討論這兩種情況，其餘情況都只要照著插入的情況處理即可。而在[二元樹刪除](https://github.com/JrPhy/DS-AL/blob/master/List_and_Tree/Tree-%E4%BA%8C%E5%85%83%E6%A8%B9.md#3-%E5%88%AA%E9%99%A4)的情況，如果被刪除的節點的左右節點都有值，那會造成新的樹不唯一，在此為了讓樹還是唯一的，故會照著 **in-order traversal** 的順序擺放，之後就看是哪種情況在做操作即可。
![AVL_Tree_delete](https://github.com/JrPhy/DS-AL/blob/master/pic/AVL_TREE_delete.jpg)
在上述例子中，刪除 12 後 in-order 為 15，故將 15 換上去，此時就不滿足 AVL 的平衡條件，所以就需要最該棵子樹做平衡。該棵子樹同時滿足 LL 與 LR 的情況，但是因為 LR 也是轉成 LL 後操作，所以這邊就直接做 LL 操作，操作後發現 9 會完全斷開，此時再藉由二元樹的定義接回去即可。
```C
/* Given a non-empty binary search tree, 
return the node with minimum key value 
found in that tree. Note that the entire 
tree does not need to be searched. */
Node * minValueNode(Node* node) 
{ 
    Node* current = node; 
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL) 
        current = current->left; 
 
    return current; 
} 
 
// Recursive function to delete a node 
// with given key from subtree with 
// given root. It returns root of the 
// modified subtree. 
Node* deleteNode(Node* root, int key) 
{ 
     
    // STEP 1: PERFORM STANDARD BST DELETE 
    if (root == NULL) 
        return root; 
 
    // If the key to be deleted is smaller 
    // than the root's key, then it lies
    // in left subtree 
    if ( key < root->key ) 
        root->left = deleteNode(root->left, key); 
 
    // If the key to be deleted is greater 
    // than the root's key, then it lies 
    // in right subtree 
    else if( key > root->key ) 
        root->right = deleteNode(root->right, key); 
 
    // if key is same as root's key, then 
    // This is the node to be deleted 
    else
    { 
        // node with only one child or no child 
        if( (root->left == NULL) ||
            (root->right == NULL) ) 
        { 
            Node *temp = root->left ? 
                         root->left : 
                         root->right; 
 
            // No child case 
            if (temp == NULL) 
            { 
                temp = root; 
                root = NULL; 
            } 
            else // One child case 
            *root = *temp; // Copy the contents of 
                           // the non-empty child 
            free(temp); 
        } 
        else
        { 
            // node with two children: Get the inorder 
            // successor (smallest in the right subtree) 
            Node* temp = minValueNode(root->right); 
 
            // Copy the inorder successor's 
            // data to this node 
            root->key = temp->key; 
 
            // Delete the inorder successor 
            root->right = deleteNode(root->right, 
                                     temp->key); 
        } 
    } 
 
    // If the tree had only one node
    // then return 
    if (root == NULL) 
    return root; 
 
    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
    root->height = 1 + max(height(root->left), 
                           height(root->right)); 
 
    // STEP 3: GET THE BALANCE FACTOR OF 
    // THIS NODE (to check whether this 
    // node became unbalanced) 
    int balance = getBalance(root); 
 
    // If this node becomes unbalanced, 
    // then there are 4 cases 
 
    // Left Left Case 
    if (balance > 1 && 
        getBalance(root->left) >= 0) 
        return rightRotate(root); 
 
    // Left Right Case 
    if (balance > 1 && 
        getBalance(root->left) < 0) 
    { 
        root->left = leftRotate(root->left); 
        return rightRotate(root); 
    } 
 
    // Right Right Case 
    if (balance < -1 && 
        getBalance(root->right) <= 0) 
        return leftRotate(root); 
 
    // Right Left Case 
    if (balance < -1 && 
        getBalance(root->right) > 0) 
    { 
        root->right = rightRotate(root->right); 
        return leftRotate(root); 
    } 
 
    return root; 
} 
```
