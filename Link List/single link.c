#include <stdio.h> 
#include <stdlib.h> 

typedef struct node
{
	int data;
	node *next;//the pointer points to the next pointer
}Node;
Node *list;

void CreateList(int arr[], int num)
{
	int i;
	Node *newNode, *temp;
	list = (Node *) malloc(sizeof(Node));
	list->data=arr[0];
	list->next=NULL;
	temp = list;
	for(i=1; i<num; i++)
	{
		newNode = (Node *) malloc(sizeof(Node));
		newNode->data = arr[i];
		newNode->next = NULL;
		temp->next = newNode;
		temp = temp->next;
	}
}

void PrintList()
{
	Node *temp;
	if(list==NULL) printf("List is empty!\n");
	else
	{
		temp = list;
		while(temp!=NULL)
		{
			printf("%3d",temp->data);
			temp=temp->next;
		}
		printf("\n");
	}
} 

Node *SearchNode(int item)
{
	Node *node=list;
	while(node!=NULL)
	{
		if(node->data ==item) return node;
		else node=node->next;
	}
	return NULL;
}

void PushBack(Node *node, int item)
{
	Node *newNode;
	newNode=(Node *) malloc(sizeof(Node));
	newNode->data=item;
	newNode->next=node->next;
	node->next=newNode;
}

Node *AddFirst(Node *list,int item)
{
	Node *newNode;
	newNode=(Node *) malloc(sizeof(Node));
	newNode->data=item;
	newNode->next=list;
	return newNode;
}

int CountList()
{
	int n = 0;
	Node *CurrentNode = list;
    while (CurrentNode != NULL) 
	{
		n++;
		CurrentNode = CurrentNode->next;
	}
	return n ;
}

void Clear()
{
	Node *temp;
	while(list != NULL)
	{
		temp = list;
		list = list->next;
		free(temp);
	}
	printf("All nodes are delete\n");
}

void Reverse()
{
	if (list == NULL || list->next == NULL) exit(0);
	else
	{
		Node* previous, *current;
		previous = list;
		current = list->next;
		list = list->next;
		previous->next = NULL;
		while (list != NULL)
		{
			list = list->next;
			current->next = previous;
			previous = current;
			current = list;
		}
		list = previous;
	}
}

int main()
{
	Node *node;
	int arr[]={14,27,32,46};
	CreateList(arr,4);
	PrintList();
	node = SearchNode(14);
	PushBack(node, 48);
	PrintList();
	Delete(node);
	PrintList();
	list = AddFirst(list, 5);
	PrintList(list);
	Clear();
	return 0;
}
