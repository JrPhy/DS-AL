對於一棵二元數來說，有可能在插入或刪除的過程中，讓整棵樹退化成 [linked-list](https://github.com/JrPhy/DS-AL/blob/master/List_and_Tree/LinkedList-%E5%96%AE%E5%90%91%E9%80%A3%E7%B5%90.md)，做插入與搜尋時的 TC 就會到 O(n)，為了讓整體的效能更好，會希望根的左右兩邊節點數量差不多，所以就有平衡二元樹這個概念。
![圖一Bad Tree](https://github.com/JrPhy/DS-AL/blob/master/pic/bad_tree.jpg)

## 1. AVLTree-平衡二元樹
上圖的最上面兩個例子就是幾乎退化成 linked-list 的例子，為了把一些節點放到右邊，會對這棵樹做一些操作，稱為**旋轉**。首先我們會先需要計算樹的高度。
#### 1. 計算高度
在計算樹的高度時，會將節點為 null 的部分標為 -1，取同一層的節點最大的數值 +1，就是該節點的高度，如上圖所示。在此就可以計算樹的高度
```C
int height(struct TreeNode* node) {
    if (node == NULL) {
        return -1;
    }
    int left_height = height(node->left);
    int right_height = height(node->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}
```
如此一來就可以定義平衡因子 BF，並定義以下三種情況：
1. BF > 1 --> 節點幾乎都在右邊
2. 1 <= BF <= 1 --> 平衡
3. BF < -1 --> 節點幾乎都在左邊
也就是該節點的左子節點高度減去右子節點高度，以圖一的根為例子，左子節點高度為 3，右子節點高度 0，故此樹的平衡因子 = 3，故該棵樹為一個節點偏向左邊的樹

#### 2. 平衡調整
再做調整時，會要求 in-order traversal 結果不變，此調整稱為**旋轉 rotation**，並且保持二元樹的性質，也就是右節點的數值 > 左節點
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
以圖一為例，
