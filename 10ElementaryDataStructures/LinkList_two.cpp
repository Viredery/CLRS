#include<iostream>
#define ERROR_OVER_RANGE 1
#define ERROR_NOT_EXIST 2
using namespace std;
template<class T>
struct Node
{
	T data;
	Node<T> *next;
};
template<class T>
class LinkList
{
public:
	LinkList();
	~LinkList();
	void PrintList();
	int GetLength();
	T Get(int pos);
	int Locate(T data);
	void Insert(int pos, T data);
	T Delete(int pos);
private:
	Node<T> *rear;
	Node<T> *GetNode(int pos);
};
template<class T>
LinkList<T>::LinkList()
{
	rear=new Node<T>;
	rear->next=rear;
}
template<class T>
LinkList<T>::~LinkList()
{
	while(rear->next!=rear)
	{
		Node<T> *p=rear->next;
		rear->next=p->next;
		delete p;
	}
	delete rear;
}
template<class T>
void LinkList<T>::PrintList()
{
	Node<T> *p=rear->next;
	while(p!=rear)
	{
		cout<<p->data<<" ";
		p=p->next;
	}
	cout<<endl;
}
template<class T>
int LinkList<T>::GetLength()
{
	int length=0;
	Node<T> *p=rear->next;
	while(p!=rear)
	{
		length++;
		p=p->next;
	}
	return length;
}
template<class T>
Node<T>* LinkList<T>::GetNode(int pos)
{
	if(pos<0 || pos>GetLength()) throw ERROR_OVER_RANGE;
	int i=0;
	Node<T> *p=rear;
	while(i!=pos)
	{
		i++;
		p=p->next;
	}
	return p;
}
template<class T>
T LinkList<T>::Get(int pos)
{
	if(pos<1 || pos>GetLength()) throw ERROR_OVER_RANGE;
	Node<T> *p=GetNode(pos);
	return p->data;
}
template<class T>
int LinkList<T>::Locate(T data)
{
	int pos=1;
	Node<T> *p=rear->next;
	while(p!=rear && p->data!=data)
	{
		pos++;
		p=p->next;
	}
	if(p==rear)
		throw ERROR_NOT_EXIST;
	else
		return pos;
}
template<class T>
void LinkList<T>::Insert(int pos, T data)
{
	Node<T> *p=GetNode(pos-1);
	Node<T> *s=new Node<T>;
	s->data=data;
	s->next=p->next;
	p->next=s;
}
template<class T>
T LinkList<T>::Delete(int pos)
{
	if(pos<1 || pos>GetLength()) throw ERROR_OVER_RANGE;
	Node<T> *p=GetNode(pos-1);
	Node<T> *s=p->next;
	T x=s->data;
	p->next=s->next;
	delete s;
	return x;
}
int main()
{
	LinkList<int> list;
	list.Insert(1,2);
	list.Insert(1,1);
	list.Insert(3,3);
	list.PrintList();
	cout<<list.Get(3)<<endl;
	cout<<list.Locate(1)<<endl;
	cout<<list.Delete(3)<<endl;
}
