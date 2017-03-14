#include<iostream>
#define ERROR_NOT_EXIST 1
using namespace std;
template<class T>
struct Node
{
	T data;
	Node<T> *lchild;
	Node<T> *rchild;
};
template<class T>
class BiTree
{
public:
	BiTree(){root=NULL;}
	~BiTree();
	Node<T>* Search(T key);
	void Create(T *a,int n);
	void Insert(T data);
	void Delete(T data);
private:
	Node<T> *root;
	void Release(Node<T> *r);
	void InsertNode(Node<T>* &p,Node<T> *s);
	void DeleteNode(Node<T>* &r);
};
template<class T>
void BiTree<T>::Release(Node<T> *r)
{
	if(r!=NULL)
	{
		Release(r->lchild);
		Release(r->rchild);
		delete r;
	}
}
template<class T>
BiTree<T>::~BiTree()
{
	Release(root);
}
template<class T>
Node<T>* BiTree<T>::Search(T key)
{
	Node<T> *p=root;
	while(p!=NULL)
	{
		if(p->data==key)
			return p;
		else if(p->data > key)
			p=p->lchild;
		else
			p=p->rchild;
	}
	return p;
}
template<class T>
void BiTree<T>::Insert(T data)
{
	Node<T> *s=new Node<T>;
	s->data=data;
	s->depth=0;
	s->lchild=s->rchild=NULL;
	InsertNode(root,s);
}
template<class T>
void BiTree<T>::InsertNode(Node<T>* &p,Node<T> *s)
{
	if(p==NULL)
		p=s;
	else if(s->data > p->data)
		InsertNode(p->rchild,s);
	else
		InsertNode(p->lchild,s);
}
template<class T>
void BiTree<T>::Create(T *a,int n)
{
	int i;
	for(i=0;i!=n;i++)
		Insert(a[i]);
}
template<class T>
void BiTree<T>::Delete(T data)
{
	Node<T> *q=NULL,*p=root;
	while(p!=NULL && p->data!=data)
	{
		q=p;
		if(p->data < data)
			p=p->rchild;
		else
			p=p->lchild;
	}
	if(p==NULL)
		throw ERROR_NOT_EXIST;
	if(q==NULL)
		DeleteNode(root);
	else if(q->lchild==p)
		DeleteNode(q->lchild);
	else
		DeleteNode(q->rchild);
}
template<class T>
void BiTree<T>::DeleteNode(Node<T>* &p)
{
	Node<T> *q,*s;
	if(p->lchild==NULL)
	{
		q=p;
		p=p->rchild;
		delete q;
	}else if(p->rchild==NULL){
		q=p;
		p=p->lchild;
		delete q;
	}else{
		q=p;
		s=p->lchild;
		while(s->rchild!=NULL)
		{
			q=s;
			s=s->rchild;
		}
		p->data=s->data;
		if(q!=p)
			q->rchild=s->lchild;
		else
			p->lchild=s->lchild;
		delete s;
	}
}
int main()
{
	BiTree<int> tree;
	int a[5]={5,7,2,4,8};
	tree.Create(a,5);
	tree.Delete(5);
	tree.Insert(1);
	Node<int> *s=tree.Search(1);
	cout<<s->data<<endl;
	s=tree.Search(7);
	cout<<s->data<<endl;
	s=tree.Search(2);
	cout<<s->data<<endl;
	tree.Delete(4);
	tree.Delete(7);
	s=tree.Search(8);
	cout<<s->data<<endl;
}
