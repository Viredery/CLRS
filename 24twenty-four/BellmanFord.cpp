#include<iostream>
#define ERROR_EXCESS_VERTEXNUM 1
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
	int d;			//指定的源点到该点的最短路径的上界
	int parent;		//在最短路径树中，该点的前趋顶点
	Edge *firstEdge;
};
template< class T >
class Graph
{
public:
	Graph(T a[], int n);
	~Graph();
	bool BellmanFord(int i);
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
	Insert(1,2,6);
	Insert(1,5,7);
	Insert(4,1,2);
	Insert(2,3,5);
	Insert(3,2,-2);
	Insert(2,4,-4);
	Insert(2,5,8);
	Insert(4,3,7);
	Insert(5,3,-3);
	Insert(4,5,9);
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
bool Graph<T>::BellmanFord(int s)
{
	InitializeSingleSource(s);
	int i,j;
	for(i = 1; i <= number - 1; i++)
		for(j = 1; j <= number; j++)	//遍历所有的边
		{
			Edge *e = vertex[j].firstEdge;
			while(e != NULL)
			{
				Relax(j,e->vertexTo,e->weight);
				e = e->next;
			}
		}
	for(j = 1; j <= number; j++)		//遍历所有的边
	{
		Edge *e = vertex[j].firstEdge;
		while(e != NULL)
		{	
			if(vertex[e->vertexTo].d > vertex[j].d + e->weight)
				return false;
			e = e->next;
		}
	}
	for(j = 1; j <= number; j++)
		if(j != s)
			cout<<vertex[vertex[j].parent].data<<"指向"<<vertex[j].data<<endl;
	return true;
}
int main()
{
	char a[] = {'s','t','x','z','y'};
	Graph<char> graph(a,5);
	graph.BellmanFord(1);
}
