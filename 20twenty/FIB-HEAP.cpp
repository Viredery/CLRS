#include<iostream>
#include<cmath>
#define ERROR_HEAP_EMPTY -1
#define ERROR_KEY_LARGE -2
#define MINVALUE -0x7fffffff
using namespace std;
struct Node
{
	int data;
	int degree;
	bool mark;
	Node *parent;
	Node *left;
	Node *right;
	Node *child;
};
class FibHeap
{
public:
	FibHeap();
	void Insert(int x);
	Node *FindNode(Node *node, int x);
	Node *Find(int x);	//没找到时返回NULL
	int Minimum();
	void Union(FibHeap &heap);
	Node *ExtractMin();
	int DecreaseKey(Node *x, int key);
	void Delete(Node *x);
	Node *min;
	int number;
private:
	void Consolidate();
	void Link(Node *y, Node *x);
	void Cut(Node *x, Node *y);
	void CascadingCut(Node *y);
};
FibHeap::FibHeap()
{
	min = NULL;
	number = 0;
}
void FibHeap::Insert(int x)
{
	Node *NodeInserted = new Node;
	NodeInserted->data = x;
	NodeInserted->degree = 0;
	NodeInserted->parent = NodeInserted->child = NULL;
	NodeInserted->left = NodeInserted->right = NodeInserted;
	NodeInserted->mark = false;	
	if(min == NULL)
		min = NodeInserted;
	else{
		NodeInserted->left = min->left;
		NodeInserted->right = min;
		min->left->right = NodeInserted;
		min->left = NodeInserted;
	}
	if(min->data > x)
		min = NodeInserted;
	number = number + 1;
}
int FibHeap::Minimum()
{
	if(min == NULL)
		throw ERROR_HEAP_EMPTY;
	return min->data;
}
void FibHeap::Union(FibHeap &heap)
{
	if(heap.min == NULL)
		return;
	if(min == NULL)
		min = heap.min;
	else{				//concatenate the root List of H2 with the root of H1
		Node *p = heap.min->right;
		p->left = min->left;
		heap.min->right = min;
		min->left->right = p;
		min->left = heap.min;
		if(min->data > heap.min->data)
			min = heap.min;
	}
	number = number + heap.number;
	heap.number = 0;
	heap.min = NULL;
}
Node *FibHeap::FindNode(Node *node, int x)
{
	if(node == NULL || node->data == x)
		return node;
	int i = 0;
	Node *child = node->child;
	while(i != node->degree)
	{
		Node *result = FindNode(child,x);
		if(result != NULL)
			return result;
		child = child->left;
	}
	return NULL;
}
Node *FibHeap::Find(int x)
{
	if(min == NULL)
		return NULL;
	Node *result = FindNode(min,x);
	if(result != NULL)
		return result;
	Node *node = min->left;
	while(node != min)
	{
		result = FindNode(node,x);
		if(result != NULL)
			return result;
		node = node->left;
	}
	return NULL;
}
Node *FibHeap::ExtractMin()
{
	Node *z = min;
	if(z != NULL)
	{
		Node *child = z->child;
		if(child != NULL)
		{
			int i;
			for(i = 0; i != z->degree; i++)
			{
				child->parent = NULL;
				child = child->left;
			}
			Node *p = z->child->right;			//add x to the root list of H
			p->left = z->left;
			z->child->right = z;
			z->left->right = p;
			z->left = z->child;
		}
		z->right->left = z->left;	//remove z from the root list of H
		z->left->right = z->right;
		if(z == z->right)
			min = NULL;
		else{
			min = z->left;
			Consolidate();
		}
		number = number - 1;
	}
	return z;
}
void FibHeap::Consolidate()
{
	int maxDegree = (int)log2(number);
	Node **indicator = new Node*[maxDegree + 1];
	int i;
	for(i = 0; i <= maxDegree; i++)
		indicator[i] = NULL;
	Node *pCurrent = min->left;
	int numList = 1;
	while(pCurrent != min)
	{
		numList++;
		pCurrent = pCurrent->left;
	}
	Node **list = new Node*[numList];
	for(i = 0; i != numList; i++)
	{
		list[i] = pCurrent;
		pCurrent = pCurrent->left;
	}
	for(i = 0; i != numList; i++)
	{
		Node *x = list[i];
		int d = x->degree;
		while(indicator[d] != NULL)
		{
			Node *y = indicator[d];
			if(x->data > y->data)
			{
				Node *tmp = x;
				x = y;
				y = tmp;
			}
			Link(y,x);	//the data of x is smaller
			indicator[d] = NULL;
			d = d + 1;
		}
		indicator[d] = x;
	}
	min = NULL;
	for(i = 0; i <= maxDegree; i++)
		if(indicator[i] != NULL)
			if(min == NULL)
			{
				indicator[i]->left = indicator[i]->right = indicator[i];
				min = indicator[i];
			}else{
				indicator[i]->right = min;
				indicator[i]->left = min->left;
				min->left->right = indicator[i];
				min->left = indicator[i];
				if(min->data > indicator[i]->data)
					min = indicator[i];
			}
	delete[] list;
	delete[] indicator;
}
void FibHeap::Link(Node *y, Node *x)
{
	y->left->right = y->right;	//remove y from the root list of H
	y->right->left = y->left;
	y->parent = x;
	if(x->child == NULL)		//make y a child of x
	{
		x->child = y;
		y->left = y->right = y;
	}else{
		y->right = x->child;
		y->left = x->child->left;
		x->child->left->right = y;
		x->child->left = y;
	}
	x->degree += 1;
	y->mark = false;
}
int FibHeap::DecreaseKey(Node *x, int key)
{
	if(key > x->data)
		throw ERROR_KEY_LARGE;
	x->data = key;
	Node *y = x->parent;
	if(y != NULL && x->data < y->data)
	{
		Cut(x,y);
		CascadingCut(y);
	}
	if(min->data > key)
		min = x;
}
void FibHeap::Cut(Node *x, Node *y)
{
	if(y->degree == 1)		//remove x from the child list of y
		y->child = NULL;
	else{
		if(y->child == x)
			y->child = x->right;
		x->left->right = x->right;
		x->right->left = x->left;
	}
	y->degree = y->degree - 1;
	x->parent = NULL;
	x->mark = false;
	x->right = min;			//add x to the root list of H
	x->left = min->left;
	min->left->right = x;
	min->left = x;	
}
void FibHeap::CascadingCut(Node *y)
{
	Node *z = y->parent;
	if(z != NULL)
	{
		if(y->mark == false)
			y->mark = true;
		else{
			Cut(y,z);
			CascadingCut(z);
		}
	}
}
void FibHeap::Delete(Node *x)
{
	DecreaseKey(x,MINVALUE);
	ExtractMin();
}
/*
int main()
{
	FibHeap heap;
	int i;
	for(i = 1; i != 10; i++)
		heap.Insert(i);
	FibHeap heap2;
	for(i = 10; i != 20 ; i++)
		heap2.Insert(i);
	heap.Union(heap2);
	Node *result = heap.ExtractMin();
	cout<<result->data<<endl;
	Node *h = heap.min->left->child->left->child->left->left;
	Node *d = heap.min->left->child->left->child->left->child->left;
	Node *f = heap.min->left->child->left->child;
	cout<<h->data<<endl;
	cout<<f->data<<endl;
	cout<<d->data<<endl;
	heap.DecreaseKey(f,1);
	heap.DecreaseKey(d,0);
}
*/
