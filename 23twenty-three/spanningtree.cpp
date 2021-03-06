#include<iostream>
#include<cmath>
#define ERROR_EXCESS_VERTEXNUM 1
#define ERROR_EMPTY 2
#define ERROR_HEAP_EMPTY -1
#define ERROR_KEY_LARGE -2
#define MINVALUE -0x7fffffff
using namespace std;
const int MAX_VALUE = 0xffff;
struct Element
{
	int rank;
	Element *parent;
};
struct Edge
{
	int vertexTo;
	int weight;
	Edge *next;
};
struct Node
{
	int data;
	int degree;
	int identifier;
	bool exist;
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
	Node *Insert(int x,int id);
	int Minimum();
	void Union(FibHeap &heap);
	Node *ExtractMin();
	int DecreaseKey(Node *x, int key);
	bool Empty();
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
Node *FibHeap::Insert(int x,int id)
{
	Node *NodeInserted = new Node;
	NodeInserted->data = x;
	NodeInserted->identifier = id;
	NodeInserted->degree = 0;
	NodeInserted->parent = NodeInserted->child = NULL;
	NodeInserted->left = NodeInserted->right = NodeInserted;
	NodeInserted->mark = false;
	NodeInserted->exist = true;
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
	return NodeInserted;
}
int FibHeap::Minimum()
{
	if(min == NULL)
		throw ERROR_HEAP_EMPTY;
	return min->data;
}
bool FibHeap::Empty()
{
	if(min == NULL)
		return true;
	return false;
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
	z->exist = false;
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
template< class T >
struct Vertex
{
	T data;
	int color;
	Element *node;
	Node *n;
	Edge *firstEdge;
};
template< class T >
class Graph
{
public:
	Graph(T a[], int n);
	~Graph();
	void Kruskal();
	void Prim(int r);
private:
	void Insert(int a, int b, int w);
	Vertex<T> *vertex;
	int number;

	void MakeSet();
	Element *FindSet(Element *x);
	void Link(Element *x, Element *y);
	void Union(Element *x, Element *y);
	void Swap(int *num, int *a, int *b, int posone, int postwo);
	void MaxHeap(int *num, int *a, int *b, int pos, int total);
	void BuildMaxHeap(int *num, int *a, int *b, int total);
	void HeapSort(int *num, int *a, int *b, int total);
};
template< class T >
Graph<T>::Graph(T a[], int n)		//无向图的构造
{
	number = n;
	vertex = new Vertex<T>[number + 1];
	int i;
	for(i = 1; i <= number; i++)
	{
		vertex[i].data = a[i - 1];
		vertex[i].firstEdge = NULL;
	}
/*	cout<<"请输入图的边数："<<endl;
	int numE;
	cin>>numE;
	for(i = 1; i <= numE; i++)
	{
		cout<<"分别输入第"<<i<<"条边的两个端点和权重："<<endl;
		int vertexone,vertextwo,weight;
		cin>>vertexone>>vertextwo>>weight;
		if(vertexone > number || vertextwo > number || vertexone <= 0 || vertextwo <= 0)
			throw ERROR_EXCESS_VERTEXNUM;
		Insert(vertexone,vertextwo,weight);
		Insert(vertextwo,vertexone,weight);
	}*/
	Insert(1,2,4);
	Insert(2,3,8);
	Insert(3,4,7);
	Insert(4,5,9);
	Insert(5,6,10);
	Insert(4,6,14);
	Insert(3,6,4);
	Insert(6,7,2);
	Insert(7,8,1);
	Insert(1,8,8);
	Insert(2,8,11);
	Insert(3,9,2);
	Insert(7,9,6);
	Insert(8,9,7);

	Insert(2,1,4);
	Insert(3,2,8);
	Insert(4,3,7);
	Insert(5,4,9);
	Insert(6,5,10);
	Insert(6,4,14);
	Insert(6,3,4);
	Insert(7,6,2);
	Insert(8,7,1);
	Insert(8,1,8);
	Insert(8,2,11);
	Insert(9,3,2);
	Insert(9,7,6);
	Insert(9,8,7);
}
template< class T >
Graph<T>::~Graph()
{
	int i;
	for(i = 1; i <= number; i++)
	{
		Edge *eDelete = vertex[i].firstEdge;
		while(eDelete != NULL)
		{
			Edge *eNext = eDelete->next;
			delete eDelete;
			eDelete = eNext;
		}
	}
	delete[] vertex;
}
template< class T >
void Graph<T>::Insert(int a, int b, int w)
{
	Edge *edgeNew = new Edge;
	edgeNew->vertexTo = b;
	edgeNew->weight = w;
	edgeNew->next = vertex[a].firstEdge;
	vertex[a].firstEdge = edgeNew;
}
template< class T >
void Graph<T>::MakeSet()
{
	int i;
	for(i = 1; i <= number; i++)
	{
		Element *node = new Element;
		node->parent = node;
		node->rank = 0;
		vertex[i].node = node;
	}
}
template< class T >
Element *Graph<T>::FindSet(Element *x)		//两趟方法：一趟沿路径上升，直至找到根；第二趟是沿查找路径下降，以便更新每个结点，使之直接指向根
{
	if(x != x->parent)
		x->parent = FindSet(x->parent);
	return x->parent;
}
template< class T>
void Graph<T>::Link(Element *x, Element *y)
{
	if(x->rank > y->rank)
		y->parent = x;
	else{
		x->parent = y;
		if(x->rank == y->rank)
			y->rank = y->rank + 1;
	}
}
template< class T >
void Graph<T>::Union(Element *x, Element *y)
{
	Link(FindSet(x),FindSet(y));
}
template< class T>
void Graph<T>::Kruskal()
{
	int *vertexone = new int[number * (number - 1) + 1];
	int *vertextwo = new int[number * (number - 1) + 1];
	int *weight = new int[number * (number - 1) + 1];
	int length = 0;
	int i;
	for(i = 1; i <= number; i++)
	{
		Edge *e = vertex[i].firstEdge;
		while(e != NULL)
		{
			if(i < e->vertexTo)		//因为是无向图，所以(u,v)和(v,u)是一个边，保存其中一个即可
			{
				length++;
				vertexone[length] = i;
				vertextwo[length] = e->vertexTo;
				weight[length] = e->weight;
			}
			e = e->next;
		}
	}
	HeapSort(weight,vertexone,vertextwo,length);
	MakeSet();
	cout<<"最小生成树:"<<endl;
	for(i = 1; i <= length; i++)
		if( FindSet(vertex[vertexone[i]].node) != FindSet(vertex[vertextwo[i]].node) )
		{
			Union(vertex[vertexone[i]].node,vertex[vertextwo[i]].node);
			cout<<vertex[vertexone[i]].data<<" "<<vertex[vertextwo[i]].data<<endl;
		}
}
template< class T >
void Graph<T>::Swap(int *num,int *a,int *b,int posone,int postwo)
{
	int temp[3] = {num[posone],a[posone],b[posone]};
	num[posone] = num[postwo];
	a[posone] = a[postwo];
	b[posone] = b[postwo];
	num[postwo] = temp[0];
	a[postwo] = temp[1];
	b[postwo] = temp[2];
}
template< class T>
void Graph<T>::HeapSort(int *num,int *a,int *b,int total)
{
	if(total < 1)
		throw ERROR_EMPTY;
	BuildMaxHeap(num,a,b,total);
	int i,heapSize = total;
	for(i = heapSize; i != 1; i--)
	{
		Swap(num,a,b,1,i);
		heapSize--;
		MaxHeap(num,a,b,1,heapSize);
	}
}
template< class T>
void Graph<T>::BuildMaxHeap(int *num,int *a,int *b,int total)
{
	int i;
	for(i = total / 2; i != 0; i--)
		MaxHeap(num,a,b,i,total);
}
template< class T>
void Graph<T>::MaxHeap(int *num,int *a,int *b,int pos,int total)
{
	int largest = pos;
	while(true)
	{
		if(pos*2 <= total && num[pos*2] > num[largest])
			largest = pos * 2;
		if(pos*2+1 <= total && num[pos*2+1] > num[largest])
			largest = pos *2 + 1;
		if(largest != pos)
		{
			Swap(num,a,b,largest,pos);
			pos = largest;
		}else
			break;
	}
}
template< class T >
void Graph<T>::Prim(int r)
{
	int key[number + 1];
	int parent[number + 1];
	int i;
	for(i = 1; i <= number; i++)
	{
		key[i] = MAX_VALUE;
		parent[i] = 0;
	}
	key[r] = 0;
	FibHeap heap;
	for(i = 1; i <= number; i++)
	{
		Node * n = heap.Insert(key[i],i);
		vertex[i].n = n;
	}
	while(!heap.Empty())
	{
		Node *node = heap.ExtractMin();
		Edge *e = vertex[node->identifier].firstEdge;
		while(e != NULL)
		{
			if(vertex[e->vertexTo].n->exist == true && e->weight < vertex[e->vertexTo].n->data)
			{
				heap.DecreaseKey(vertex[e->vertexTo].n,e->weight);
				parent[e->vertexTo] = node->identifier;
			}
			e = e->next;
		}
	}
	cout<<"最小生成树:"<<endl;
	for(i = 1; i <= number; i++)
		if(parent[i] != 0)
			cout<<vertex[i].data<<" "<<vertex[parent[i]].data<<endl;
}
int main()
{
	char a[] = {'a','b','c','d','e','f','g','h','i'};
	Graph<char> graph(a,9);
	graph.Kruskal();
	graph.Prim(1);
}
