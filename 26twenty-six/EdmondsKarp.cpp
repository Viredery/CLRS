#include<iostream>
#define ERROR_EXCESS_VERTEXNUM 1
#define WHITE 1
#define GRAY 2
#define BLACK 3
#define MAXIMUM 0xffff
using namespace std;
struct Edge
{
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
	Edge *firstEdge;
};
template< class T >
class Graph
{
public:
	Graph(T a[], int n);
	~Graph();
	void EdmondsKarp(int s, int t);
private:
	bool BFS(int s, int t, int *parent);
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
	Insert(1,2,16);
	Insert(1,3,13);
	Insert(2,3,14);
	Insert(2,4,12);
	Insert(4,3,9);
	Insert(3,5,14);
	Insert(5,4,7);
	Insert(4,6,20);
	Insert(5,6,4);
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
	edgeNew->vertexTo = b;
	edgeReverse->vertexTo = a;
	edgeNew->weight = w;
	edgeReverse->weight = 0;
	edgeNew->next = vertex[a].firstEdge;
	vertex[a].firstEdge = edgeNew;
	edgeReverse->next = vertex[b].firstEdge;
	vertex[b].firstEdge = edgeReverse;
	edgeNew->reverse = edgeReverse;
	edgeReverse->reverse = edgeNew;
}
template< class T>
bool Graph<T>::BFS(int s, int t, int *parent)	//广度优先遍历算法，时间复杂度O(E+V)
{
	int i;
	for(i = 1; i <= number; i++)
		parent[i] = 0;
	int *queue = new int[number + 1];
	int tail = 0, head = 0;
	queue[tail++] = s;	//入列
	while(tail != head)	//当队列为空时退出循环
	{
		int v = queue[head++];	//出列
		Edge *e = vertex[v].firstEdge;
		while(e != NULL)
		{
			if(e->weight - e->f > 0 && vertex[e->vertexTo].color == WHITE)	//e->weight - e->f等于残留容量
			{
				vertex[e->vertexTo].color = GRAY;
				parent[e->vertexTo] = v;
				queue[tail++] = e->vertexTo;	//入列
			}
			e = e->next;
		}
		vertex[v].color = BLACK;
	}
	delete[] queue;
	for(i = 1; i <= number; i++){
		vertex[i].color = WHITE;
cout<<parent[i]<<" ";
}cout<<endl;
	if(parent[t] != 0)
		return true;
	return false;
}
template< class T >
void Graph<T>::EdmondsKarp(int s, int t)
{
	int maxflow = 0;
	int i;
	for(i = 1; i <= number; i++)
	{
		Edge *e = vertex[i].firstEdge;
		while(e != NULL)
		{
			e->f = 0;
			e = e->next;
		}
	}
	int *parent = new int[number + 1];
	while(BFS(s,t,parent) == true)			//全部的迭代次数为O(VE),BFS算法的时间复杂度为O(E)
	{
		Edge **array = new Edge*[number + 1];
		int length = 0;
		int minf = MAXIMUM;
		int node = t;
		while(parent[node] != 0)
		{
			Edge *e = vertex[parent[node]].firstEdge;
			while(e != NULL)
			{
				if(e->vertexTo == node)
				{
					array[++length] = e;
					if(e->weight - e->f < minf)
					{ 
						minf = e->weight - e->f;
					}
					break;
				}
				e = e->next;
			}
			node = parent[node];
		}
		maxflow += minf;
		for(i = 1; i <= length; i++)
		{
			array[i]->f = array[i]->f + minf;
			array[i]->reverse->f = -array[i]->f;
		}
		delete[] array;
	}
	delete[] parent;
	for(i = 1; i <= number; i++)
	{
		Edge *e = vertex[i].firstEdge;
		while(e != NULL){
			if(e->f > 0)
				cout<<vertex[i].data<<"->"<<vertex[e->vertexTo].data<<": "<<e->f<<endl;
			e = e->next;
		}
	}
	cout<<"最大流为"<<maxflow<<endl;
}
int main()
{
	char a[] = {'s','a','b','c','d','t'};
	Graph<char> graph(a,6);
	graph.EdmondsKarp(1,6);
	
}
