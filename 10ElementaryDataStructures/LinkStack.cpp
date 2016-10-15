#include<iostream>
#define ERROR_STACK_EMPTY 1
using namespace std;
template<class T>
struct Node
{
	T data;
	Node<T> *next;
};
template<class T>
class LinkStack
{
private:
	Node<T> *top;
public:
	LinkStack(){
		top=NULL;
	}
	~LinkStack();
	void Push(T x);
	T Pop();
	T GetTop();
	bool Empty();
};
template<class T>
LinkStack<T>::~LinkStack()
{
	Node<T> *p=top;
	while(p)
	{
		top=p;
		p=p->next;
		delete top;
	}
}
template<class T>
void LinkStack<T>::Push(T x)
{
	Node<T> *p=new Node<T>;
	p->data=x;
	p->next=top;
	top=p;
}
template<class T>
T LinkStack<T>::Pop()
{
	if(Empty()) throw ERROR_STACK_EMPTY;
	T x=top->data;
	Node<T> *p=top;
	top=top->next;
	delete p;
	return x;
}
template<class T>
T LinkStack<T>::GetTop()
{
	if(Empty()) throw ERROR_STACK_EMPTY;
	T x=top->data;
	return x;
}
template<class T>
bool LinkStack<T>::Empty()
{
	return top==NULL?true:false;
}
int main()
{
	try{
	LinkStack<int> stack;
	stack.Push(5);
	stack.Push(10);
	stack.Push(50);
	cout<<stack.Pop()<<endl;
	cout<<stack.GetTop()<<endl;
	cout<<stack.Pop()<<endl;
	cout<<stack.Pop()<<endl;
	cout<<stack.Pop()<<endl;
	}catch(int x){cout<<"empty"<<endl;}
}
