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
	bool visited;
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
	void EulerianCircuit();
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
	Insert(3,4,1);
	Insert(1,2,1);
	Insert(2,3,1);
	Insert(3,1,1);
	Insert(4,5,1);
	Insert(5,3,1);
	Insert(1,3,1);
	Insert(3,6,1);
	Insert(6,1,1);
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
	edgeNew->visited = false;
	edgeNew->next = vertex[a].firstEdge;
	vertex[a].firstEdge = edgeNew;
}
template< class T >
void Graph<T>::EulerianCircuit()
{
	Edge **stack = new Edge*[number * (number - 1) + 1];
	int *stacknode = new int[number * (number - 1) + 1];
	int *edge = new int[number * (number - 1) + 1];
	int length = 0;
	int top = 0;
	int i;
	for(i = 1; i <= number; i++)
	{
		Edge *ePresent = vertex[i].firstEdge;
		stacknode[++top] = i;
		while(ePresent != NULL)
		{
			Edge *e = ePresent;
			while(e != NULL)
			{
				if(e->visited == false)
				{
					e->visited = true;
					stacknode[++top] = e->vertexTo;
					e = vertex[e->vertexTo].firstEdge;
				}else
					e = e->next;
			}
			if(top > 1)
			{
				int j = length;
				while(j != 0 && edge[j] != stacknode[1])
				{
					edge[j + top - 1] = edge[j];
					j--;
				}
				if(length == 0)
				{
					length++;
					j++;
					edge[length] = stacknode[1];
				}
				int k;
				for(k = 1; k < top; k++)
					edge[j + k] = stacknode[k + 1];
				length = length + top - 1;
			}
			top = 0;
			ePresent = ePresent->next;
		}
	}
	for(i = 1; i <= length; i++)
		cout<<edge[i]<<" ";
	cout<<endl;
	//恢复
	delete[] stack;
	delete[] stacknode;
}
int main()
{
	char a[] = {'a','b','c','d','e','f'};
	Graph<char> graph(a,6);
	graph.EulerianCircuit();
}
