#include<iostream>
#define ERROR_OVER_RANGE 1
#define ERROR_NOT_EXIST 2
using namespace std;
template<class T>
struct Node
{
	T data;
	struct Node<T> *next;
};
template<class T>
class  LinkList
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
	Node<T> *front;
	Node<T> *GetNode(int pos);
};
template<class T>
LinkList<T>::LinkList()
{
	front=new Node<T>;
	front->next=NULL;
}
template<class T>
LinkList<T>::~LinkList()    //O(n)
{
	while(front)
	{
		Node<T> *p=front;
		front=front->next;
		delete p;
	}
}
template<class T>
void LinkList<T>::PrintList()    //O(n)
{
	Node<T> *p=front->next;
	while(p)
	{
		cout<<p->data<<" ";
		p=p->next;
	}
	cout<<endl;
}
template<class T>
int LinkList<T>::GetLength()    //O(n)
{
	Node<T> *p=front->next;
	int length=0;
	while(p)
	{
		p=p->next;
		length++;
	}
	return length;
}
template<class T>
Node<T> *LinkList<T>::GetNode(int pos)   //when pos == 0,return value of rear->next,O(n)
{
	Node<T> *p=front;
	while(p && pos!=0)
	{
		p=p->next;
		pos--;
	}
	if(p)
		return p;
	else
		throw ERROR_OVER_RANGE;
}
template<class T>
T LinkList<T>::Get(int pos)
{
	Node<T>* pNode=GetNode(pos);
	return pNode->data;
}
template<class T>
int LinkList<T>::Locate(T data)
{
	Node<T> *p=front->next;
	int pos=1;
	while(p && p->data != data)
	{
		p=p->next;
		pos++;
	}
	if(p)
		return pos;
	else
		throw ERROR_NOT_EXIST;
}
template<class T>
void LinkList<T>::Insert(int pos, T data)
{
	Node<T> *p=GetNode(pos-1),*s=new Node<T>;        //Function Get() will throw error when the value of pos is over-range
	s->data=data;
	s->next=p->next;
	p->next=s;
}
template<class T>
T LinkList<T>::Delete(int pos)
{
	Node<T> *p=GetNode(pos-1);
	Node<T> *s=p->next;
	if(s != NULL)
	{
		T data=s->data;
		p->next=s->next;
		delete s;
		return data;
	}else
		throw ERROR_OVER_RANGE;
	
}
int main()
{
	LinkList<int> array;
	array.Insert(1,1);
	array.Insert(1,2);
	cout<<array.Locate(2)<<endl;
	return 0;
}
