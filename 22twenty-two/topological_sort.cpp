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
	void TopologicalSort();
private:
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
	Insert(1,2,1);
	Insert(1,3,1);
	Insert(1,5,1);
	Insert(2,3,1);
	Insert(2,4,1);
	Insert(3,5,1);
	Insert(4,5,1);
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
void Graph<T>::TopologicalSort()
{
	Edge **stack = new Edge*[number + 1];
	int *stacknode = new int[number + 1];
	int top = -1;
	int *node = new int[number + 1];	//保存拓扑排序的结果
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
	cout<<"拓扑排序结果为：";
	for(i = 1; i <= number; i++)
		cout<<node[i]<<" ";
	cout<<endl;
	//恢复
	delete[] node;
	delete[] stack;
	delete[] stacknode;
	for(i = 1; i <= number; i++)
		vertex[i].color = WHITE;
}
int main()
{
	int a[] = {1,2,3,4,5};
	Graph<int> graph(a,5);
	graph.TopologicalSort();
}
