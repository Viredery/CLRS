#include<iostream>
#include<cstring>
#define ERROR_STACK_EMPTY 1
using namespace std;
template<class T>
class SeqStack
{
public:
	SeqStack();
	~SeqStack();
	void Push(T data);
	T Pop();
	T GetTop();
	bool Empty();
private:
	T *pData;
	int size;
	int step;
	int top;
};
template<class T>
SeqStack<T>::SeqStack():size(50),step(10),top(0)
{
	pData=new T[size+1];
}
template<class T>
SeqStack<T>::~SeqStack()
{
	delete[] pData;
	pData=NULL;
}
template<class T>
void SeqStack<T>::Push(T data)
{
	if(top == size)
	{
		T *pTemp=new T[size+step+1];
		memcpy(pTemp,pData,sizeof(T)*(size+1));
		delete[] pData;
		pData=pTemp;
		size=size+step;
	}
	top++;
	pData[top]=data;
}
template<class T>
T SeqStack<T>::Pop()
{
	if(Empty())
		throw ERROR_STACK_EMPTY;
	T data=pData[top];
	top--;
	return data;
}
template<class T>
T SeqStack<T>::GetTop()
{
	if(Empty())
		throw ERROR_STACK_EMPTY;
	return pData[top];
}
template<class T>
bool SeqStack<T>::Empty()
{
	if(top==0)
		return true;
	else
		return false;
}
int main()
{
	SeqStack<int> stack;
	return 0;
}
