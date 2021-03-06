#include<iostream>
#include<cmath>
#define ERROR_EXCESS_VERTEXNUM 1
#define ERROR_EMPTY 2
#define ERROR_HEAP_EMPTY -1
#define ERROR_KEY_LARGE -2
const int MAX_VALUE = 0xffff;
using namespace std;
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
template< class T >
struct Vertex
{
	T data;
	Node *n;
	int d;			//指定的源点到该点的最短路径的上界
	int parent;		//在最短路径树中，该点的前趋顶点
	Edge *firstEdge;
};
class FibHeap
{
public:
	FibHeap();
	Node *Insert(int x,int id);
	Node *ExtractMin();
	int DecreaseKey(Node *x, int key);
	bool Empty();
private:
	Node *min;
	int number;
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
bool FibHeap::Empty()
{
	if(min == NULL)
		return true;
	return false;
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
class Graph
{
public:
	Graph(T a[], int n);
	~Graph();
	void Dijkstra(int i);
private:
	void InitializeSingleSource(int s);
	void Relax(int u, int v, int w);
	void Insert(int a, int b, int w);
	Vertex<T> *vertex;
	int number;
};
template< class T >
Graph<T>::Graph(T a[], int n)		//有向图的构造
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
	}*/
	Insert(1,2,10);
	Insert(1,5,5);
	Insert(4,1,7);
	Insert(2,5,2);
	Insert(5,2,3);
	Insert(2,3,1);
	Insert(3,4,4);
	Insert(4,3,6);
	Insert(5,3,9);
	Insert(5,4,2);
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
void Graph<T>::InitializeSingleSource(int s)
{
	int i;
	for(i = 0; i <= number; i++)
	{
		vertex[i].d = MAX_VALUE;
		vertex[i].parent = 0;
	}
	vertex[s].d = 0;
}
template< class T >
void Graph<T>::Relax(int u, int v, int w)	//边(u,v)
{
	if(vertex[u].d != MAX_VALUE && vertex[v].d > vertex[u].d + w)
	{
		vertex[v].d = vertex[u].d + w;
		vertex[v].parent = u;
	}
}
template< class T>
void Graph<T>::Dijkstra(int s)
{
	InitializeSingleSource(s);
	FibHeap heap;
	int i;
	for(i = 1; i <= number; i++)
		vertex[i].n = heap.Insert(vertex[i].d,i);
	while(!heap.Empty())
	{
		Node *node = heap.ExtractMin();
		Edge *e = vertex[node->identifier].firstEdge;
		while(e != NULL)
		{
			Relax(node->identifier,e->vertexTo,e->weight);
			if(vertex[e->vertexTo].n->data > vertex[e->vertexTo].d)
				heap.DecreaseKey(vertex[e->vertexTo].n,vertex[e->vertexTo].d);
			e = e->next;
		}
	}
	for(i = 1; i <= number; i++)
		if(i != s)
			cout<<vertex[vertex[i].parent].data<<"指向"<<vertex[i].data<<endl;
}
int main()
{
	char a[] = {'s','t','x','z','y'};
	Graph<char> graph(a,5);
	graph.Dijkstra(1);
}
