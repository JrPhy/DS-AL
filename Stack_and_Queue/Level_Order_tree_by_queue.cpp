#include <iostream>
#include <queue>
// A Binary Tree Node
typedef struct _node {
    struct _node* left;
    int data;
    struct _node* right;
}node;

// Iterative method to do level order traversal
// line by line
void printLevelOrder(node* root){
    std::queue<node*> q;
    q.push(root);
    while (!q.empty()){
        node *current = q.front();      // 取出先進入queue的node
        q.pop();                          
        std::cout << current->data << ", ";   // 走訪
        if (current->left != NULL){    // 若 left 有資料則放進queue
            q.push(current->left);
        }
        if (current->right != NULL){  // 若 right 有資料則放進queue
            q.push(current->right);
        }
    }
}

// Utility function to create a new tree node
node* newNode(int data)
{
	node* temp = new node;
	temp->data = data;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

// Driver program to test above functions
int main()
{
	// Let us create binary tree shown above
	node* root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);

	printLevelOrder(root);
	return 0;
}
