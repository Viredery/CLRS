#include<iostream>
#include<cstring>
#include<string>
#define ERROR_OVERFLOW 1
using namespace std;
const int MAXSIZE=10;
const int MAX_VALUE=0xffff;
struct VEdge{
	int fromV;
	int endV;
	int weight;
};
template<class T>
class MGraph
{
public:
	MGraph(T a[],int n,int e);
	void DFS(int v);
	void BFS(int v);
	void Prim(int v);
	void Kruskal();
	void Dijkstra(int v);
	void Floyd(int fromV,int endV);
private:
	int FindMinForDijk(int *disk,bool *added,int vNum);
	void GenSortEdgeForKru(VEdge EdgeList[]);
	int mininumForPrim(int *lowcost);
	void DSelect(int v,bool *visited);
	void BSelect(int v,int &f,int &r,bool *visited,int *queue);

	int vNum;
	int arcNum;
	T vertex[MAXSIZE];
	int arc[MAXSIZE][MAXSIZE];
};
template<class T>
MGraph<T>::MGraph(T a[],int n,int e):vNum(n),arcNum(e)
{
	int i,j,k,w;
	for(i=0;i!=vNum;i++)
	{
		vertex[i]=a[i];
		for(j=0;j!=vNum;j++)
			arc[i][j]=MAX_VALUE;
		arc[i][i]=0;
	}
	for(i=0;i!=arcNum;i++)
	{
		cin>>j>>k>>w;
		arc[j][k]=w;
		arc[k][j]=arc[j][k];
	}
}
template<class T>
void MGraph<T>::DSelect(int v,bool *visited)
{
	int i;
	cout<<vertex[v]<<" ";
	visited[v]=true;
	for(i=0;i!=vNum;i++)
		if(arc[v][i]==1 && visited[i]==false)
			DSelect(i,visited);
}
template<class T>
void MGraph<T>::DFS(int v)
{
	if(v<0 || v>vNum) throw ERROR_OVERFLOW;
	bool visited[vNum];
	memset(visited,false,vNum*sizeof(bool));
	DSelect(v,visited);
	cout<<endl;
}
template<class T>
void MGraph<T>::BSelect(int v,int &f,int &r,bool *visited,int *queue)
{
	if(f==r) return;
	f++;
	int i;
	for(i=0;i!=vNum;i++)
		if(arc[v][i]==1 && visited[i]==false)
		{
			cout<<vertex[i]<<" ";
			visited[i]=true;
			queue[r]=i;
			r++;
		}
	BSelect(queue[f],f,r,visited,queue);
}
template<class T>
void MGraph<T>::BFS(int v)
{
	if(v<0 || v>=vNum) throw ERROR_OVERFLOW;
	bool visited[vNum];
	memset(visited,false,vNum*sizeof(bool));
	int queue[MAXSIZE];
	int f=0,r=0;
	cout<<vertex[v]<<" ";
	queue[r++]=v;
	visited[v]=true;
	BSelect(queue[f],f,r,visited,queue);
	cout<<endl;
}
template<class T>
int MGraph<T>::mininumForPrim(int *lowcost)
{
	int node=-1,minValue=MAX_VALUE,i;
	for(i=0;i!=vNum;i++)
	{
		if(lowcost[i]!=0&&lowcost[i]<minValue)
		{
			minValue=lowcost[i];
			node=i;
		}	
	}
	return node;
}
template<class T>
void MGraph<T>::Prim(int v)
{
	int adjvex[MAXSIZE],lowcost[MAXSIZE];
	memset(lowcost,0,vNum*sizeof(int));
	int i;
	for(i=0;i!=vNum;i++)
	{
		lowcost[i]=arc[v][i];
		adjvex[i]=v;
	}
	adjvex[v]=-1;
	for(i=1;i!=vNum;i++)
	{
		int k=mininumForPrim(lowcost);
		lowcost[k]=0;
		int j;
		for(j=0;j!=vNum;j++)
			if(arc[k][j]<lowcost[j])
			{
				lowcost[j]=arc[k][j];
				adjvex[j]=k;
			}
	}
	for(i=0;i!=vNum;i++)
		cout<<"V"<<adjvex[i]<<"->V"<<i<<endl;
}
template<class T>
void MGraph<T>::GenSortEdgeForKru(VEdge EdgeList[])
{
	int k=0,i,j;
	for(i=0;i<vNum;i++)
		for(j=0;j<i;j++)
			if(arc[i][j]!=MAX_VALUE)
			{
				EdgeList[k].fromV=j;
				EdgeList[k].endV=i;
				EdgeList[k].weight=arc[i][j];
				k++;
			}
	for(i=0;i!=arcNum;i++)
		for(j=arcNum-1;j!=i;j--)
			if(EdgeList[j-1].weight>EdgeList[j].weight)
			{
				VEdge tmp=EdgeList[j-1];
				EdgeList[j-1]=EdgeList[j];
				EdgeList[j]=tmp;
			}
}
template<class T>
void MGraph<T>::Kruskal()
{
	VEdge EdgeList[arcNum];
	GenSortEdgeForKru(EdgeList);
	int vset[vNum];
	int i;
	for(i=0;i!=vNum;i++)
		vset[i]=i;
	int k=0;
	while(k!=vNum-1)
	{
		int m=EdgeList[k].fromV,n=EdgeList[k].endV;
		int mset=vset[m];
		int nset=vset[n];
		if(mset!=nset)
		{
			cout<<"V"<<m<<"->V"<<n<<endl;
			k++;
			for(i=0;i<vNum;i++)
				if(vset[i]==nset)
					vset[i]=mset;
		}
	}
}
template<class T>
int MGraph<T>::FindMinForDijk(int *disk,bool *added,int vNum)
{
	int i,min=-1,minValue=MAX_VALUE;
	for(i=0;i!=vNum;i++)
	{
		if(!added[i] && disk[i]<minValue)
		{
			minValue=disk[i];
			min=i;
		}
	}
	return min;
}
template<class T>
void MGraph<T>::Dijkstra(int v)
{
	bool added[vNum];
	int disk[vNum];
	char data[vNum];
	string path[vNum];
	int i;
	for(i=0;i!=vNum;i++)
	{
		added[i]=false;
		data[i]='0'+i;
		disk[i]=arc[v][i];
	}
	for(i=0;i!=vNum;i++)
		if(disk[i]!=MAX_VALUE)
		{
			path[i]=data[v];
			path[i]+=data[i];
		}
		else
			path[i]="";
	for(i=0;i!=vNum;i++)
	{
		if((v=FindMinForDijk(disk,added,vNum))==-1)
			break;
		added[v]=true;
		int j;
		for(j=0;j!=vNum;j++)
			if(!added[j] && disk[j]>arc[v][j]+disk[v])
			{
				disk[j]=arc[v][j]+disk[v];
				path[j]=path[v]+data[j];
			}
	}
	for(i=0;i!=vNum;i++)
		cout<<path[i]<<endl;
}
template<class T>
void MGraph<T>::Floyd(int fromV,int endV)
{
	if(fromV<0 || fromV>=vNum || endV<0 || endV>=vNum)
		throw ERROR_OVERFLOW;
	int dist[vNum][vNum];
	char data[vNum];
	string path[vNum][vNum];
	int i,j,k;
	for(i=0;i!=vNum;i++)
		data[i]='0'+i;
	for(i=0;i!=vNum;i++)
		for(j=0;j!=vNum;j++)
		{
			dist[i][j]=arc[i][j];
			if(dist[i][j]!=MAX_VALUE && dist[i][j]!=0)
			{
				path[i][j]=data[i];
				path[i][j]+=data[j];
			}
			else
				path[i][j]="";
		}
	for(k=0;k!=vNum;k++)
		for(i=0;i!=vNum;i++)
			for(j=0;j!=vNum;j++)
				if(dist[i][j]>dist[i][k]+dist[k][j])
				{
					dist[i][j]=dist[i][k]+dist[k][j];
					path[i][j]=path[i][k]+path[k][j];
				}
	cout<<path[fromV][endV]<<endl;
}
int main()
{
	int a[4]={0,1,2,3};
	MGraph<int> graph(a,4,4);
	graph.Dijkstra(0);
	graph.Floyd(0,3);
}
