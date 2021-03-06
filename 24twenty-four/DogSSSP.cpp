//dog图的单源最短路径
#include<iostream>
#define ERROR_EXCESS_VERTEXNUM 1
#define WHITE 1
#define GRAY 2
#define BLACK 3
const int MAX_VALUE = 0xffff;
using namespace std;
struct Edge
{
	int vertexTo;
	int weight;
	Edge *next;
};
template< class T >
struct Vertex
{
	T data;
	int color;
	int d;			//指定的源点到该点的最短路径的上界
	int parent;	//在最短路径树中，该点的前趋顶点
	Edge *firstEdge;
};
template< class T >
class Graph
{
public:
	Graph(T a[], int n);
	~Graph();
	void SingleSourceSP(int s);
private:
	void TopologicalSort(int *node);
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
	Insert(5,6,5);
	Insert(5,1,3);
	Insert(6,1,2);
	Insert(6,2,6);
	Insert(1,2,7);
	Insert(1,4,4);
	Insert(1,3,2);
	Insert(2,4,-1);
	Insert(2,3,1);
	Insert(4,3,-2);
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
template< class T >
void Graph<T>::TopologicalSort(int *node)
{
	Edge **stack = new Edge*[number + 1];
	int *stacknode = new int[number + 1];
	int top = -1;
	int pos = number;
	int i;
	for(i = 1; i <= number; i++)
		if(vertex[i].color == WHITE)
		{
			vertex[i].color = GRAY;
			stacknode[++top] = i;
			stack[top] = vertex[i].firstEdge;
			while(top != -1)
			{
				Edge *e = stack[top];
				while(e != NULL)
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
void Graph<T>::SingleSourceSP(int s)
{
	int *node = new int[number + 1];
	TopologicalSort(node);
	InitializeSingleSource(s);
	int start = 1;
	while(node[start] != s)
		start++;
	int j;
	for(j = start; j != number; j++)
	{
		Edge *e = vertex[node[j]].firstEdge;
		while(e != NULL)
		{
			Relax(node[j],e->vertexTo,e->weight);
			e = e->next;
		}
	}
	for(j = start + 1; j <= number; j++)
		cout<<vertex[vertex[node[j]].parent].data<<"指向"<<vertex[node[j]].data<<endl;
}
int main()
{
	char a[] = {'t','x','z','y','r','s'};
	Graph<char> graph(a,6);
	graph.SingleSourceSP(6);
}
