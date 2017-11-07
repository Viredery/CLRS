#include<iostream>
using namespace std;
template<class T>
struct BiNode
{
	T data;
	BiNode<T> *lchild;
	BiNode<T> *rchild;
};
template<class T>
class BiTree
{
public:
	BiNode<T> *root;
	BiTree(T data[],int n);
	~BiTree();
	void PreOrder(BiNode<T> *R);
	void InOrder(BiNode<T> *R);
	void PostOrder(BiNode<T> *R);
	void LevelOrder(BiNode<T> *R);
	int Count(BiNode<T> *R);
	int Depth(BiNode<T> *R);
	//void FindRoute(T data);
private:
	void Create(BiNode<T>* &R,T data[],int n,int i);
	void Release(BiNode<T> *R);
};
template<class T>
void BiTree<T>::Create(BiNode<T>* &R,T data[],int n,int i)
{
	if(data[i-1]!=0 && i<n+1)
	{
		R=new BiNode<T>;
		R->data=data[i-1];
		R->lchild=R->rchild=NULL;
		Create(R->lchild,data,n,2*i);
		Create(R->rchild,data,n,2*i+1);
	}
}
template<class T>
BiTree<T>::BiTree(T data[],int n)
{
	Create(root,data,n,1);
}
template<class T>
void BiTree<T>::PreOrder(BiNode<T> *R)
{
	BiNode<T>* stack[100];
	int top=-1;
	while((top!=-1)||(R!=NULL))
	{
		if(R!=NULL)
		{
			cout<<R->data<<" ";
			stack[++top]=R;
			R=R->lchild;
		}else{
			R=stack[top--];
			R=R->rchild;
		}
	}
	cout<<endl;
}
template<class T>
void BiTree<T>::InOrder(BiNode<T> *R)
{
	BiNode<T>* stack[100];
	int top=-1;
	while(top!=-1 || R!=NULL)
	{
		if(R!=NULL)
		{
			stack[++top]=R;
			R=R->lchild;
		}else{
			R=stack[top--];
			cout<<R->data<<" ";
			R=R->rchild;	
		}
	}
	cout<<endl;
}
template<class T>
void BiTree<T>::PostOrder(BiNode<T> *R)
{
	BiNode<T>* stack[100];
	int top=-1;
	BiNode<T>* node=R, preNode=NULL;
	while(node!=NULL)
	{
		stack[++top]=node;
		node=node->lchild;
	}
	while(top!=-1)
	{
		node=stack[top--];
		if(node->rchild!=NULL||node->rchild!=preNode)
		{
			cout<<node->data<<" ";
			preNode=node;
		}
		else
		{
			stack[++top]=node;
			node=node->rchild;
			while(node)
			{
				stack[++top]=node;
				node=node->lchild;
			}
		}
	}
	cout<<endl;
}
template<class T>
void BiTree<T>::LevelOrder(BiNode<T> *R)
{
	BiNode<T>* queue[100];
	int f=0,r=0;
	if(R!=NULL)
		queue[++r]=R;
	while(f!=r)
	{
		BiNode<T> *p=queue[++f];
		cout<<p->data<<" ";
		if(p->lchild!=NULL)
			queue[++r]=p->lchild;
		if(p->rchild!=NULL)
			queue[++r]=p->rchild;
	}
	cout<<endl;
}
template<class T>
int BiTree<T>::Count(BiNode<T> *R)
{
	if(R == NULL)
		return 0;
	else{
		int m = Count(R->lchild);
		int n = Count(R->rchild);
		return m + n + 1;
	}
}
//引自考研大纲解析38页：树的深度是从根节点开始（其深度为1）自顶向下逐层累加的，而高度是从叶节点开始（其高度为1）自底向上逐层累加的。
//虽然树的深度和高度一样，但是具体到树的某个节点，其深度和高度是不一样的。我的理解是：非根非叶结点的深度是从根节点数到它的，高度是从叶节点数到它的。
template<class T>
int BiTree<T>::Depth(BiNode<T> *R)	//将所有高度为1的结点进行统计，便得到叶子结点总数
{
	if(R == NULL)
		return 0;
	else{
		int m = Depth(R->lchild);
		int n = Depth(R->rchild);
		return m > n ? m + 1: n + 1;
	}
}
template<class T>
void BiTree<T>::Release(BiNode<T> *R)
{
	if(R!=NULL)
	{
		Release(R->lchild);
		Release(R->rchild);
		delete R;
	}
}
template<class T>
BiTree<T>::~BiTree()
{
	Release(root);
}
int main()
{
	int a[]={1,2,3,4,5,6,7,8};
	BiTree<int> tree(a,8);
	tree.PreOrder(tree.root);
	tree.InOrder(tree.root);
	tree.PostOrder(tree.root);
	tree.LevelOrder(tree.root);
	cout<<tree.Count(tree.root)<<endl;
	cout<<tree.Depth(tree.root)<<endl;
}
