#include<iostream>
using namespace std;
template<class T>
struct Node
{
	T data;
	Node<T> *prior;
	Node<T> *next;
};
template<class T>
class LinkList
{
public:
	LinkList();
	~LinkList();
	int GetLength();
	void Insert(int pos,T x);
	T Delete(int pos);
private:
	Node<T> *front;
	Node<T> *GetNode(int pos);
};
template<class T>
LinkList<T>::LinkList()
{
	front=new Node<T>;
	front->next=front;
	front->prior=front;
}
template<class T>
LinkList<T>::~LinkList()
{
	while(front->next!=front)
	{
		Node<T> *p=front->next;
		front->next=p->next;
		delete p;
	}
	delete front;
}
template<class T>
int LinkList<T>::GetLength()
{
	int length=0;
	Node<T> *p=front;
	while(p->next!=front)
	{
		length++;
		p=p->next;
	}
	return length;
}
template<class T>
Node<T>* LinkList<T>::GetNode(int pos)
{
	if(pos<0 || pos>GetLength()) throw "over range\n";
	Node<T> *p=front;
	while(pos)
	{
		p=p->next;
		pos--;
	}
	return p;
}
template<class T>
void LinkList<T>::Insert(int pos,T x)
{
	Node<T> *p=GetNode(pos-1),*s=new Node<T>;
	s->data=x;
	s->next=p->next;
	s->prior=p;
	s->next->prior=s;
	p->next=s;
}
template<class T>
T LinkList<T>::Delete(int pos)
{
	Node<T> *p=GetNode(pos-1),*s=p->next;
	T x=s->data;
	s->next->prior=p;
	p->next=s->next;
	delete s;
	return x;
}
int main()
{
	LinkList<int> list;
	list.Insert(1,22);
	list.Insert(1,11);
	list.Insert(3,33);
	cout<<list.Delete(2)<<endl;
	cout<<list.Delete(2)<<endl;
	cout<<list.Delete(1)<<endl;
}
