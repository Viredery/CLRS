//二叉链表实现可合并堆
#include<iostream>
using namespace std;
struct Node
{
	int data;
	Node *parent;
	Node *left;
	Node *right;
};
class Heap
{
public:
	Heap();
	Heap(int a[], int n);
	int Minimum();
	int ExtractMin();
	void Insert(int data);
	void Union(Heap &a);
	void LevelOrder();
private:
	Node *root;
	int length;
	void MinHeapify(Node *p);	//使p下降，直到以p为根的子树成为最小堆
	Node *GetNode(int pos);		//根据位置返回指针
};
Heap::Heap()			//O(1)
{
	root = NULL;
	length = 0;
}
Heap::Heap(int a[], int n)	//O(nlgn)
{
	root = NULL;
	length = 0;
	int i;
	for(i = 0; i != n; i++)
		Insert(a[i]);
}
void Heap::LevelOrder()		//O(n)
{
	Node **queue = new Node*[length+1];
	int f = 0, r = 0;
	if(root != NULL)
		queue[++r] = root;
	while(f != r)
	{
		Node *p = queue[++f];
		cout<<p->data<<" ";
		if(p->left != NULL)
			queue[++r] = p->left;
		if(p->right != NULL)
			queue[++r] = p->right;
	}
	cout<<endl;
	delete[] queue;
}
Node *Heap::GetNode(int pos)	//O(lgn)
{
	int *stack = new int[length];
	int top = -1;
	while(pos != 1)
	{
		stack[++top] = pos % 2;
		pos = pos / 2;
	}
	Node *p = root;
	while(top != -1)
		stack[top--] == 1 ? p = p->right : p = p->left;
	delete[] stack;
	return p;
}
void Heap::MinHeapify(Node *p)		//O(lgn)
{
	Node *minNode = p;
	Node *l = p->left;
	Node *r = p->right;
	if(l != NULL && l->data < p->data)
		minNode = l;
	if(r != NULL && r->data < minNode->data)
		minNode = r;
	if(minNode != p)
	{
		int temp = minNode->data;
		minNode->data = p->data;
		p->data = temp;
		MinHeapify(minNode);
	}
}
int Heap::Minimum()		//O(1)
{
	return root->data;
}
int Heap::ExtractMin()		//O(lgn)
{
	int min = root->data;
	//将最后一个结点的元素与第一个结点交换
	if(length == 1)
	{
		length--;
		delete root;
		root = NULL;
		return min;
	}
	Node *p = GetNode(length);
	int temp = p->data;
	p->data = root->data;
	root->data = temp;
	Node *parent = p->parent;
	//删除最后一个结点
	parent->right == NULL ? parent->left = NULL : parent->right = NULL;
	delete p;
	length--;
	//保持最小堆
	MinHeapify(root);
	return min;
}
void Heap::Insert(int data)	//O(lgn)
{
	//创建一个新结点
	Node *p = new Node;
	p->data = data;
	p->parent = p->left =p->right = NULL;
	//将结点插入堆的最后一个位置
	length++;
	if(root == NULL)
	{
		root = p;
		return;
	}
	Node *parent = GetNode(length / 2);
	parent->left == NULL ? parent->left = p : parent->right = p;
	p->parent = parent;
	//调整成为最小堆
	while(parent != NULL)
	{
		if(parent->data <= p->data)
			return;
		int temp = parent->data;
		parent->data = p->data;
		p->data = temp;
		p = parent;
		parent = p->parent;
	}
}
void Heap::Union(Heap &heap)
{
	int number;
	while(heap.root != NULL)
	{
		number = heap.ExtractMin();
		Insert(number);
	}
}
int main()
{
	int a[10] = {4,5,9,13,3,12,8,10,1,20};
	Heap heap(a,10);
	heap.Insert(2);
	heap.LevelOrder();
	int b[3]={7,6,21};
	Heap heap2(b,3);
	heap.Union(heap2);
	heap.LevelOrder();
}
