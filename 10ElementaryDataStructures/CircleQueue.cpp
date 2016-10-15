#include<iostream>
#define MAX 100
#define ERROR_QUEUE_EMPTY 1
#define ERROR_QUEUE_FULL 2
using namespace std;
template<class T>
class CircleQueue
{
public:
	CircleQueue():front(0),rear(0){}
	~CircleQueue(){}
	void EnQueue(T data);
	T DeQueue();
	T GetFront();
	int GetLength();
	bool Empty(){
		return front == rear? true: false;
	}
private:
	T data[MAX];
	int front;
	int rear;
};
template<class T>
void CircleQueue<T>::EnQueue(T x)
{
	if((rear+1)%MAX == front)
		throw ERROR_QUEUE_FULL;
	rear=(rear+1)%MAX;
	data[rear]=x;
}
template<class T>
T CircleQueue<T>::DeQueue()
{
	if(Empty())
		throw ERROR_QUEUE_EMPTY;
	front=(front+1)%MAX;
	return data[front];
}
template<class T>
T CircleQueue<T>::GetFront()
{
	if(Empty())
		throw ERROR_QUEUE_EMPTY;
	return data[(front+1)%MAX];
}
template<class T>
int CircleQueue<T>::GetLength()
{
	return (rear-front+MAX)%MAX;
}
int main()
{
	CircleQueue<int> queue;
	return 0;
}
