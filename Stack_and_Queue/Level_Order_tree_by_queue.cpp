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
void printLevelOrder(node* root)
{
	if (root == NULL) return;

	// Create an empty queue for level order traversal
	std::queue<node*> q;

	// Enqueue Root and initialize height
	q.push(root);

	while (q.empty() == false) {
		// nodeCount (queue size) indicates number
		// of nodes at current level.
		int nodeCount = q.size();

		// Dequeue all nodes of current level and
		// Enqueue all nodes of next level
		while (nodeCount > 0) {
			node* node = q.front();
			std::cout << node->data << " ";
			q.pop();
			if (node->left != NULL)
				q.push(node->left);
			if (node->right != NULL)
				q.push(node->right);
			nodeCount--;
		}
		std::cout << std::endl;
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
