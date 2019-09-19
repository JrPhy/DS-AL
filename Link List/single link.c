#include <stdio.h> 
#include <stdlib.h> 

typedef struct node//use typedef for convenient
{
	int data;
	struct node *next;//the pointer is for linking other nodes
}Node;


Node *CreateList(int arr[], int num)
{
	int i;
	Node *list, *current, *previous;
	for(i=0; i<num; i++)
	{
		current = (Node *) malloc(sizeof(Node));
		current->data=arr[i];//current->data means *current.data
		if(i == 0) list = current;
		else previous->next = current;
		current->next = NULL;//the last pointer points to NULL
		previous=current;
	}
	current=list;
	return list;
}

void FreeList(Node *list)
{
	Node *current, *tmp;
	current=list;
	while(current!=NULL)
	{
		tmp=current;
		current=current->next;
		free(tmp);
	}
}

void PrintList(Node *list)
{
	Node *node=list;
	if(list==NULL) printf("List is empty!\n");
	else
	{
		while(node!=NULL)
		{
			printf("%3d",node->data);
			node=node->next;//points to next data after printing.
		}
		printf("\n");
	}
} 

Node *SearchNode(Node *list,int item)
{
	Node *node = list;
	while(node != NULL)
	{
		if(node->data == item) return node;
		else node=node->next;
	}
	return NULL;
}

void PushBack(Node *node,int item)
{
	Node *newNode;
	newNode=(Node *) malloc(sizeof(Node));
	newNode->data=item;
	newNode->next=node->next;
	node->next=newNode;
}
//this function adds item after some node.
//please use Search the data before PushBack.

Node *AddFirst(Node *list,int item)
{
	Node *newNode;
	newNode=(Node *) malloc(sizeof(Node));
	newNode->data=item;
	newNode->next=list;
	return newNode;
}

int CountList(Node *list)
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

Node *Delete(Node *list,int item) 
{
	Node *CurrentNode = list;
	Node *PreviousNode;
	while (CurrentNode != NULL) 
	{
		if (CurrentNode->data == item) 
		{
			if (CurrentNode == list) list = CurrentNode->next;
			else PreviousNode->next = CurrentNode->next;
		} 
		PreviousNode = CurrentNode;
		CurrentNode = CurrentNode->next;
	}
	return list;
}

int main()
{
	Node *list,*node;
	int arr[]={14,27,32,46};
	list = CreateList(arr,4);
	PrintList(list);
	node = SearchNode(list, 46);
	PushBack(node, 48);
	list = AddFirst(list, 5);
	PrintList(list);
	list = Delete(list, 46);
	PrintList(list);
	printf("%d\n",CountList(list));
	FreeList(list);
	PrintList(list);
	return 0;
}
