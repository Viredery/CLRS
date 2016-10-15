#include<iostream>
using namespace std;
struct Node
{
	int ivex;
	int jvex;
	int weight;
};
template<class T>
class ESGraph
{
public:
	ESGraph(T a[],int n,int e);
	~ESGraph();
private:
	int vNum;
	int arcNum;
	T *vertex;
	Node *arc;
};
template<class T>
ESGraph<T>::ESGraph(T a[],int n,int e)
{
	vNum=n;
	arcNum=e;
	vertex=new T[vNum];
	int k;
	for(k=0;k!=vNum;k++)
		vertex[k]=a[k];
	arc=new Node[arcNum];
	for(k=0;k!=arcNum;k++)
	{
		int i,j,w;
		cin>>i>>j>>w;
		arc[k].ivex=i;
		arc[k].jvex=j;
		arc[k].weight=w;
	}
}
template<class T>
ESGraph<T>::~ESGraph()
{
	delete[] vertex;
	delete[] arc;
}
int main()
{
}
