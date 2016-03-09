#include<iostream>
#define ERROR_EXCESS_VERTEXNUM 1
#define WHITE 1
#define GRAY 2
#define BLACK 3
#define MAXIMUM 0xffff
using namespace std;
struct Edge
{
	int vertexFrom;
	int vertexTo;
	int weight;
	int f;			//流
	Edge *next;
	Edge *reverse;
};
template< class T >
struct Vertex
{
	T data;
	int color;
	int h;			//顶点的高度
	int e;			//顶点的余流
	Edge *firstEdge;
	Edge *current;		//目前被考察的顶点
	Vertex<T> *pre;
	Vertex<T> *next;
};
template< class T >
class Graph
{
public:
	Graph(T a[], int n);
	~Graph();
	void RelabelToFront(int s, int t);
private:
	void TopologicalSort(int *node);	//拓扑排序
	void Push(int u, Edge *e);			//从u到v的压入，e为从u到v的边
	void Relabel(int u);			//对u进行重标记操作
	void InitializePreflow(int s);		//在流网络中建立一个初始前置流
	void Discharge(Vertex<T> *p);		//排除溢出顶点
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
		vertex[i].color = WHITE;
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
	Insert(2,1,12);
	Insert(2,5,14);
	Insert(1,5,5);
	Insert(4,1,7);
	Insert(1,3,16);
	Insert(5,4,8);
	Insert(4,3,10);
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
	Edge *edgeReverse = new Edge;
	edgeNew->vertexFrom = a;	//边的两个端点
	edgeNew->vertexTo = b;
	edgeReverse->vertexFrom = b;
	edgeReverse->vertexTo = a;
	edgeNew->weight = w;		//边的权重
	edgeReverse->weight = 0;

	edgeNew->next = vertex[a].firstEdge;
	vertex[a].firstEdge = edgeNew;
	edgeReverse->next = vertex[b].firstEdge;
	vertex[b].firstEdge = edgeReverse;
	edgeNew->reverse = edgeReverse;
	edgeReverse->reverse = edgeNew;
}
template< class T >
void Graph<T>::TopologicalSort(int *node)
{
	Edge **stack = new Edge*[number + 1];
	int *stacknode = new int[number + 1];
	int top = -1;
	int pos = number;
	int i;
	for(i = 1; i <= number; i++)
		node[i] = 0;
	for(i = 1; i <= number; i++)
		if(vertex[i].color == WHITE)
		{
			vertex[i].color = GRAY;
			stacknode[++top] = i;
			stack[top] = vertex[i].firstEdge;
			while(top != -1)
			{
				Edge *e = stack[top];
				while(e != NULL && e->weight - e->f > 0)
				{
					if(vertex[e->vertexTo].color == WHITE)
					{
						vertex[e->vertexTo].color = GRAY;
						stacknode[++top] = e->vertexTo;
						stack[top] = vertex[e->vertexTo].firstEdge;
						stack[top - 1] = e->next;
						e = stack[top];
					}else
						e = e->next;
				}
				vertex[stacknode[top]].color = BLACK;
				node[pos] = stacknode[top];
				top--;pos--;
			}
		}
	//恢复
	delete[] stack;
	delete[] stacknode;
	for(i = 1; i <= number; i++)
		vertex[i].color = WHITE;
}
template< class T >
void Graph<T>::Push(int u, Edge *e)
{
	int min = vertex[u].e > (e->weight - e->f) ? e->weight - e->f : vertex[u].e;
	e->f += min;
	e->reverse->f = -e->f;
	vertex[u].e -= min;
	vertex[e->vertexTo].e += min;
}
template< class T >
void Graph<T>::Relabel(int u)
{
	int min = MAXIMUM;
	Edge *e = vertex[u].firstEdge;
	while(e != NULL)
	{
		if(e->weight - e->f > 0 && min > vertex[e->vertexTo].h)
			min = vertex[e->vertexTo].h;
		e = e->next;
	}
	vertex[u].h = min + 1;
}
template< class T >
void Graph<T>::InitializePreflow(int s)
{
	int i;
	for(i = 1; i <= number; i++)
		vertex[i].h = vertex[i].e = 0;
	for(i = 1; i <= number; i++)
	{
		Edge *e = vertex[i].firstEdge;
		while(e != NULL)
		{
			e->f = 0;
			e = e->next;
		}
	}
	vertex[s].h = number;
	Edge *edge = vertex[s].firstEdge;
	while(edge != NULL)
	{
		edge->f = edge->weight;
		edge->reverse->f = -edge->f;
		vertex[edge->vertexTo].e = edge->weight;
		vertex[s].e = vertex[s].e - edge->weight;
		edge = edge->next;
	}
}
template< class T >
void Graph<T>::Discharge(Vertex<T> *p)
{
	while(p->e > 0)
	{
		Edge *e = p->current;
		if(e == NULL)
		{
			Relabel(p->firstEdge->vertexFrom);
			p->current = p->firstEdge;
		}else if(e->weight - e->f > 0 && p->h == vertex[p->current->vertexTo].h + 1)
			Push(p->firstEdge->vertexFrom,e);
		else
			p->current = p->current->next;
	}
}
template< class T >
void Graph<T>::RelabelToFront(int s, int t)
{
	int i;
	int node[number + 1];	//保存拓扑排序的结果
	InitializePreflow(s);
	TopologicalSort(node);
	//建立V[G]-{s,t}的链表，其元素顺序为拓扑排序的序列
	Vertex<T> *head = new Vertex<T>;
	Vertex<T> *present = head;
	head->pre = head->next = NULL;
	for(i = 1; i <= number; i++)
		if(node[i] != s && node[i] != t)
		{
			vertex[node[i]].next = present->next;
			vertex[node[i]].pre = present;
			present->next = &vertex[node[i]];
			present = present->next;
		}
	for(i = 1; i <= number; i++)
		vertex[i].current = vertex[i].firstEdge;
	present = head->next;
	while(present != NULL)
	{
		int oldHeight = present->h;
		Discharge(present);
		if(present->h > oldHeight)
		{
			//将元素移动到链表的前面
			present->pre->next = present->next;
			if(present->next != NULL)
				present->next->pre = present->pre;
			present->pre = head;
			present->next = head->next;
			present->pre->next = present;
			if(present->next != NULL)
				present->next->pre = present;
		}
		present = present->next;
	}
	cout<<"最大流为："<<vertex[t].e<<endl;
	delete[] head;
}
int main()
{
	char a[] = {'x','s','t','z','y'};
	Graph<char> graph(a,5);
	graph.RelabelToFront(2,3);
}
