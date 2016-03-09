/*Let G = (V, E) be a directed graph in which each vertex u∈V is labeled with a uniqueinteger L(u) fromthe set {1, 2, ..., |V|}. For each vertex u∈V, let R(u) = {v∈V|∃a path from u to v in G}. Define min(u) to be the vertex in R(u) whose label is minimum,i.e.,min(u) is the vertex v such that L(v) = min{L(w)|w∈R(u)}. Give an O(V+E)-time algorithmthat computes min(u) for all vertices u∈v.*/
#include<iostream>
#define ERROR_EXCESS_VERTEXNUM 1
#define WHITE 1
#define GRAY 2
#define BLACK 3
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
	int sign;
	int color;
	Edge *firstEdge;
};
template< class T >
class Graph
{
public:
	Graph(T a[], int b[], int n);
	~Graph();
	void Reachability();
private:
	void DFS(Vertex<T> *v, int *node, int *min);		//按照node顺序进行深度优先搜索
	void Transposition(Vertex<T> *v);			//v是元素数为number+1的数组，保存转置后的图
	void Sort(int *node);					//将L(u)排序
	void Insert(int a, int b, int w);
	Vertex<T> *vertex;
	int number;
};
template< class T >
Graph<T>::Graph(T a[], int b[], int n)		//有向图的构造
{
	number = n;
	vertex = new Vertex<T>[number + 1];
	int i;
	for(i = 1; i <= number; i++)
	{
		vertex[i].data = a[i - 1];
		vertex[i].sign = b[i - 1];
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
	Insert(1,3,1);Insert(3,4,1);Insert(4,5,1);Insert(2,5,1);Insert(6,3,1);
	Insert(6,4,1);Insert(4,6,1);Insert(5,7,1);Insert(6,7,1);Insert(3,8,1);
	Insert(7,9,1);Insert(9,8,1);
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
void Graph<T>::Transposition(Vertex<T> *v)
{
	int i;
	for(i = 1; i <= number; i++)
	{
		v[i].data = vertex[i].data;
		v[i].sign = vertex[i].sign;
		v[i].color = WHITE;
		Edge *e = vertex[i].firstEdge;
		while(e != NULL)
		{
			Edge *edgeNew = new Edge;
			edgeNew->vertexTo = i;
			edgeNew->weight = e->weight;
			edgeNew->next = v[e->vertexTo].firstEdge;
			v[e->vertexTo].firstEdge = edgeNew;
			e = e->next;
		}
	}
}
template< class T >
void Graph<T>::DFS(Vertex<T> *v, int *node, int *min)
{
	Edge **stack = new Edge*[number + 1];
	int *stacknode = new int[number + 1];
	int top = -1;
	int i;
	for(i = 1; i <= number; i++)
	{
		if(v[node[i]].color == WHITE)
		{
			v[node[i]].color = GRAY;
			min[node[i]] = i;
			stacknode[++top] = node[i];
			stack[top] = v[node[i]].firstEdge;
			while(top != -1)
			{
				Edge *e = stack[top];
				while(e != NULL)
				{
					if(v[e->vertexTo].color == WHITE)
					{
						v[e->vertexTo].color = GRAY;
						stacknode[++top] = e->vertexTo;
						stack[top] = v[e->vertexTo].firstEdge;
						stack[top - 1] = e->next;
						e = stack[top];
					}else
						e = e->next;
				}
				v[stacknode[top]].color = BLACK;
				min[stacknode[top]] = i;
				top--;
			}
		}
	}
	//恢复
	delete[] stack;
	delete[] stacknode;
	for(i = 1; i <= number; i++)
		v[i].color = WHITE;
}
template< class T >
void Graph<T>::Sort(int *node)
{
	int *array = new int[number + 1];
	int i;
	for(i = 1; i <= number; i++)
		array[i] = vertex[i].sign;
	for(i = 1; i <= number; i++)
		node[array[i]] = i;	
}
template< class T >
void Graph<T>::Reachability()	//O(E+V)
{
	int *node = new int[number + 1];
	Sort(node);
	Vertex<T> *v = new Vertex<T>[number + 1];
	Transposition(v);
	int *min = new int[number + 1];
	DFS(v,node,min);
	int i;
	for(i = 1; i <= number; i++)
		cout<<vertex[i].data<<"的min值为"<<min[i]<<endl;

	delete[] node;
	delete[] min;
	for(i = 1; i <= number; i++)
	{
		Edge *eDelete = v[i].firstEdge;
		while(eDelete != NULL)
		{
			Edge *eNext = eDelete->next;
			delete eDelete;
			eDelete = eNext;
		}
	}
	delete[] v;
}
int main()
{
	char a[] = {'a','b','c','d','e','f','g','h','i'};
	int b[] = {2,4,7,8,3,1,9,6,5};
	Graph<char> graph(a,b,9);
	graph.Reachability();
}
