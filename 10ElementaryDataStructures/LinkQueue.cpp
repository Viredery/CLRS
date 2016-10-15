#include<iostream>
#define ERROR_QUEUE_EMPTY 1
using namespace std;
template<class T>
struct Node
{
	T data;
	Node<T> *next;
};
template<class T>
class LinkQueue
{
public:
	LinkQueue(){
		front=rear=new Node<T>;
		front->next=NULL;
	}
	~LinkQueue();
	void EnQueue(T x);
	T DeQueue();
	T GetFront();
	bool Empty(){
		return front==rear?true:false;
	}
private:
	Node<T> *front;
	Node<T> *rear;
};
template<class T>
LinkQueue<T>::~LinkQueue()
{
	while(front)
	{
		rear=front;
		front=front->next;
		delete rear;
	}
}
template<class T>
void LinkQueue<T>::EnQueue(T x)
{
	Node<T> *p=new Node<T>;
	p->data=x;
	p->next=NULL;
	rear->next=p;
	rear=p;
}
template<class T>
T LinkQueue<T>::DeQueue()
{
	if(Empty()) throw ERROR_QUEUE_EMPTY;
	Node<T> *p=front->next;
	T x=p->data;
	front->next=p->next;
	delete p;
	if(!(front->next))
		rear=front;
	return x;
}
template<class T>
T LinkQueue<T>::GetFront()
{
	if(Empty()) throw ERROR_QUEUE_EMPTY;
	T x=front->next->data;
	return x;
}
int main()
{
	LinkQueue<int> queue;
	queue.EnQueue(10);
	queue.EnQueue(20);
	queue.EnQueue(30);
	cout<<queue.DeQueue()<<endl;
	cout<<queue.DeQueue()<<endl;
	cout<<queue.GetFront()<<endl;
	cout<<queue.DeQueue()<<endl;
	cout<<queue.DeQueue()<<endl;
}
