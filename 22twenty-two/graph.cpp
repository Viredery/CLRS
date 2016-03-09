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
	void BFS(int u);
	void DFS();
private:
	void PrintPath(int a[]);
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
template< class T>
void Graph<T>::BFS(int u)	//广度优先遍历算法，时间复杂度O(E+V)
{
	int *parent = new int[number + 1];
	int i;
	for(i = 1; i <= number; i++)
		parent[i] = 0;
	parent[u] = -1;
	int *queue = new int[number + 1];
	int tail = 0, head = 0;
	queue[tail++] = u;	//入列
	while(tail != head)	//当队列为空时退出循环
	{
		int v = queue[head++];	//出列
		Edge *e = vertex[v].firstEdge;
		while(e != NULL)
		{
			if(vertex[e->vertexTo].color == WHITE)
			{
				vertex[e->vertexTo].color = GRAY;
				parent[e->vertexTo] = v;
				queue[tail++] = e->vertexTo;	//入列
			}
			e = e->next;
		}
		vertex[v].color = BLACK;
	}
	PrintPath(parent);
	//恢复
	delete[] parent;
	delete[] queue;
	for(i = 1; i <= number; i++)
		vertex[i].color = WHITE;
}
template< class T >
void Graph<T>::PrintPath(int a[])
{
	int i;
	for( i = 1; i <= number; i++)
		if(a[i] != 0 && a[i] != -1)
			cout<<vertex[i].data<<"的双亲为"<<vertex[a[i]].data<<endl;
}
/*DFS递归方法见P.331，此处为非递归方法，时间复杂度O(V+E)
算法中使用时间戳，并判断边的性质
算法保证每一个点都访问到，所以结束后得到的是一个森林（森林里可能只有一棵树）*/
template< class T >
void Graph<T>::DFS()
{
	int *parent = new int[number + 1];	//保存深度遍历森林
	int i;
	for(i = 1; i <= number; i++)
		parent[i] = 0;
	Edge **stack = new Edge*[number + 1];
	int *stacknode = new int[number + 1];
	int *start = new int[number + 1];	//start记录开始时间
	int *finish = new int[number + 1];	//finish记录结束时间
	int time = 0;
	int top = -1;
	for(i = 1; i <= number; i++)
		if(vertex[i].color == WHITE)
		{
			vertex[i].color = GRAY;
			parent[i] = -1;
			time = time + 1;
			start[i] = time;
			top++;
			stacknode[top] = i;
			stack[top] = vertex[i].firstEdge;
			while(top != -1)
			{
				Edge *e = stack[top];
				while(e != NULL)
				{
					if(vertex[e->vertexTo].color == WHITE)
					{
						cout<<"从"<<stacknode[top]<<"到"<<e->vertexTo<<"：树边"<<endl;
						time = time + 1;
						start[e->vertexTo] = time;
						vertex[e->vertexTo].color = GRAY;
						parent[e->vertexTo] = stacknode[top];
						top++;
						stacknode[top] = e->vertexTo;
						stack[top] = vertex[e->vertexTo].firstEdge;
						stack[top - 1] = e->next;
						e = stack[top];
					}else{
						if(vertex[e->vertexTo].color == BLACK)
							cout<<"从"<<stacknode[top]<<"到"<<e->vertexTo<<"：正向边或交叉边"<<endl;
						else
							cout<<"从"<<stacknode[top]<<"到"<<e->vertexTo<<"：反向边"<<endl;
						e = e->next;
					}
				}
				vertex[stacknode[top]].color = BLACK;
				time = time + 1;
				finish[stacknode[top]] = time;
				top--;
			}
		}
	for(i = 1; i <= number; i++)
		cout<<start[i]<<" "<<finish[i]<<endl;
	PrintPath(parent);
	//恢复
	delete[] parent;
	delete[] stack;
	delete[] stacknode;
	delete[] start;
	delete[] finish;
	for(i = 1; i <= number; i++)
		vertex[i].color = WHITE;
}
int main()
{
	int a[] = {1,2,3,4,5};
	Graph<int> graph(a,5);
	graph.BFS(1);
	graph.DFS();
}
