#include <queue>
#include <iostream>
 
struct Node {
    int data;
    struct Node *left, *right;
};
 
void printLevelOrder(Node* root)
{
    // Base Case
    if (root == nullptr) return;
    std::queue<Node*> q;
    // 先把要印的節點放進隊列中
    q.push(root);
 
    while (q.empty()) {
        Node* node = q.front();
        std::cout << node->data << " ";
        q.pop();
        // 印完之後把節點丟出來
        if (node->left != nullptr) q.push(node->left);
        if (node->right != nullptr) q.push(node->right);
        // 分別把左右節點放入隊列中
    }
}

Node* newNode(int data)
{
    Node* temp = new Node;
    temp->data = data;
    temp->left = temp->right = nullptr;
    return temp;
}
 
// Driver program to test above functions
int main()
{
    // Let us create binary tree shown in above diagram
    Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
 
    std::cout << "Level Order traversal of binary tree is \n";
    printLevelOrder(root);
    return 0;
}
