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
	int color;
	Edge *firstEdge;
};
template< class T >
class Graph
{
public:
	Graph(T a[], int n);
	~Graph();
	void GetSCC();
private:
	void TopologicalSort(int *node);			//node大小为number+1,保存拓扑排序的结果
	void Transposition(Vertex<T> *v);			//v是元素数为number+1的数组，保存转置后的图
	void DFS(Vertex<T> *v, int *node, int *subgraph);	//按照node顺序进行深度优先搜索，subgraph大小为number+1,保存强连通子图
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
	Insert(1,2,1);Insert(2,5,1);Insert(5,1,1);Insert(5,6,1);Insert(2,6,1);
	Insert(2,3,1);Insert(6,7,1);Insert(7,6,1);Insert(3,7,1);Insert(7,8,1);
	Insert(8,8,1);Insert(3,4,1);Insert(4,3,1);Insert(4,8,1);
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
void Graph<T>::Transposition(Vertex<T> *v)
{
	int i;
	for(i = 1; i <= number; i++)
	{
		v[i].data = vertex[i].data;
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
void Graph<T>::DFS(Vertex<T> *v, int *node, int *subgraph)
{
	Edge **stack = new Edge*[number + 1];
	int *stacknode = new int[number + 1];
	int top = -1;
	int i;
	for(i = 1; i <= number; i++)
		subgraph[i] = i;
	for(i = 1; i <= number; i++)
	{
		if(v[node[i]].color == WHITE)
		{
			v[node[i]].color = GRAY;
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
				subgraph[stacknode[top]] = node[i];
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
void Graph<T>::GetSCC()
{
	int *node = new int[number + 1];
	Vertex<T> *v = new Vertex<T>[number + 1];
	int *subgraph = new int[number + 1];
	//call DFS(G) to compute finishing times f[u] for each vertex u
	TopologicalSort(node);
	//compute GT
	Transposition(v);
	//call DFS(GT), but in the main loop of DFS, consider the vertices in the order of decreasing f[u](as computed in step 1)
	DFS(v,node,subgraph);
	//output separate strongly connected components
	int i;
	for(i = 1; i <= number; i++)
		cout<<v[i].data<<"属于分支图"<<subgraph[i]<<endl;
	//deal with dynamic datas
	delete[] node;
	delete[] subgraph;
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
	char a[] = {'a','b','c','d','e','f','g','h'};
	Graph<char> graph(a,8);
	graph.GetSCC();
}
