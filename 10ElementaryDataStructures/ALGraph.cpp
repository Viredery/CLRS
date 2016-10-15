#include<iostream>
#include<cstring>
#define ERROR_OVERFLOW 1
using namespace std;
const int MAXSIZE=10;
struct ArcNode
{
	int adjvex;
	int weight;
	ArcNode *nextarc;
};
template<class T>
struct VertexNode
{
	T vertex;
	ArcNode *firstarc;
};
template<class T>
class ALGraph
{
public:
	ALGraph(T a[],int n,int e);
	~ALGraph();
	void DFS(int v);
	void BFS(int v);
private:
	void DSelect(int v,bool *visited);
	void BSelect(int v,int &f,int &r,bool *visited,int *queue);
	VertexNode<T> adjlist[MAXSIZE];
	int vNum;
	int arcNum;
};
template<class T>
ALGraph<T>::ALGraph(T a[],int n,int e)
{
	vNum=n;
	arcNum=e;
	int i;
	for(i=0;i!=vNum;i++)
	{
		adjlist[i].vertex=a[i];
		adjlist[i].firstarc=NULL;
	}
	int j,k,w;
	for(i=0;i!=arcNum;i++)
	{
		cin>>j>>k>>w;
		ArcNode *p=new ArcNode;
		p->adjvex=k;
		p->weight=w;
		p->nextarc=adjlist[j].firstarc;
		adjlist[j].firstarc=p;
	}
}
template<class T>
ALGraph<T>::~ALGraph()
{
	int i;
	for(i=0;i!=vNum;i++)
	{
		while(adjlist[i].firstarc!=NULL)
		{
			ArcNode *s=adjlist[i].firstarc;
			adjlist[i].firstarc=s->nextarc;
			delete s;
		}
	}
}
template<class T>
void ALGraph<T>::DSelect(int v,bool *visited)
{
	ArcNode *p=adjlist[v].firstarc;
	while(p!=NULL)
	{
		if(visited[p->adjvex]==false)
		{
			cout<<adjlist[p->adjvex].vertex<<" ";
			visited[p->adjvex]=true;
			DSelect(p->adjvex,visited);
		}
		p=p->nextarc;
	}
}
template<class T>
void ALGraph<T>::DFS(int v)
{
	if(v<0 || v>=vNum) throw ERROR_OVERFLOW;
	bool visited[vNum];
	memset(visited,false,vNum*sizeof(bool));
	cout<<adjlist[v].vertex<<" ";
	visited[v]=true;
	DSelect(v,visited);
	cout<<endl;
}
template<class T>
void ALGraph<T>::BSelect(int v,int &f,int &r,bool *visited,int *queue)
{
	if(f==r) return;
	f++;
	ArcNode *p=adjlist[v].firstarc;
	while(p!=NULL)
	{
		if(visited[p->adjvex]==false)
		{
			queue[r++]=p->adjvex;
			cout<<adjlist[p->adjvex].vertex<<" ";
			visited[p->adjvex]=true;
		}
		p=p->nextarc;
	}
	BSelect(queue[f],f,r,visited,queue);
}
template<class T>
void ALGraph<T>::BFS(int v)
{
	if(v<0 || v>=vNum) throw ERROR_OVERFLOW;
	bool visited[vNum];
	memset(visited,false,vNum*sizeof(bool));
	int queue[MAXSIZE];
	int f=0,r=0;
	queue[r]=v;
	r++;
	cout<<adjlist[v].vertex<<" ";
	visited[v]=true;
	BSelect(queue[f],f,r,visited,queue);
	cout<<endl;
}
int main()
{
	int a[5]={0,1,2,3,4};
	ALGraph<int> graph(a,5,5);
	graph.DFS(0);
	graph.BFS(0);
}
