雖然 recursive 的寫法很簡潔，但是若太多層，則可能會造成 stack overflow，所以來改寫成 iterative 的寫法，可以利用 stack 跟 queue 的資料結構，在此直接使用 c++ 中的 stl。[stack](https://github.com/JrPhy/DS-AL/blob/master/Stack_and_Queue/Stack-%E5%A0%86%E7%96%8A.md) 是一種 FILO 的資料結構，[queue](https://github.com/JrPhy/DS-AL/blob/master/Stack_and_Queue/Queue-%E4%BD%87%E5%88%97.md) 則是 FIFO，兩者主要靠 push 跟 pop 來將資料放入跟移出。
## 1. preorder
```cpp
void preorder(node *root) 
{
    if (!root) return;
    std::vector<int> res;
    
    std::stack<node*> s;
    s.push(root);  // 放入 root
    node *n = root;  // node 指向最上面的節點
    while (!s.empty()) {
        n = s.top();
        s.pop();  // 移除最上面的節點
        res.push_back(n->data);  // 放入 vector 中
        if (n->right) s.push(n->right);
        if (n->left) s.push(n->left);
    }
    for(const auto &i : res) std::cout << i << ", ";
}
```
preorder 是從上到下，然後先印左邊再印右邊。因為是先放右節點再放左節點進 stack，所以在 top() 時會先拿到左節點的子節點，就會先把左邊的印完再印右邊的。
## 2. inorder
```cpp
void inorder(node *root) 
{
    if (!root) return;
    std::vector<int> res;
    
    std::stack<node*> s;
    node *n = root;  // node 指向最上面的節點
    while (n || !s.empty()) {
        while (n) {
            s.push(n);
            n = n->left;
        }
        n = s.top();
        s.pop();
        res.push_back(n->data);
        n = n->right;
    }
    for(const auto &i : res) std::cout << i << ", ";
}
```
inorder 是從下到上，從左到右印出。所以會先走到樹的最左邊，印出最左邊最下層的左右節點，然後移到上一個節點，再走到右節點，重複此步驟。
## 3. postorder
```cpp
void postorder(node *root) 
{
    if (!root) return;
    std::vector<int> res;
    
    std::stack<node*> s;
    node *last = root;  // node 指向最上面的節點
    node *n = root;
    while (root || !s.empty()) {
        if (root) {
            s.push(root);
            root = root->left;
        } else {
            n = s.top();
            if (n->right && last != n->right) {
                root = n->right;
            } else {
                res.push_back(n->data);
                last = n;
                s.pop();
            }
        }
    }
    for(const auto &i : res) std::cout << i << ", ";
}
```
postorder 也是從下到上，從左到右印出。但印出左節點後，會先到上一個節點然後印出來，再走到右節點印出，重複此步驟。
## 4. levelorder
```cpp
void printLevelOrder(node* root){
    std::queue<node*> q;
    q.push(root);
    while (!q.empty()){
        node *current = q.front(); q.pop();      
        // 取出先進 queue 的node
        std::cout << current->data << ", ";
        if (current->left) q.push(current->left);
        // 若 left 有資料則放進 queue
        if (current->right) q.push(current->right);
        // 若 right 有資料則放進 queue
    }
}
```
雖然 levelorder 也是從上到下再從左到右，但是 preorder 是先把從上到下左邊印完再印右邊，levelorder 則是先把該層的資料印完，所以要先進先出。
