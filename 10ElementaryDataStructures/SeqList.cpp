#include<iostream>
#include<cstring>
#define ERROR_OVERFLOW_UP 1
#define ERROR_OVERFLOW_DOWN 2
#define ERROR_OVER_RANGE 3
#define ERROR_INPUT 4
using namespace std;
template<class T>
class SeqList
{
public:
	SeqList():size(100),step(10),length(0){
		pData = new T[size+1];
	}
	~SeqList(){
		delete[] pData;
		pData = NULL;
	}
	int GetLength();
	void PrintList();
	void Insert(int pos, T data);
	T Delete(int pos);
	T Get(int pos);
	int Locate(T data, int strat);
private:
	T *pData;
	int size;
	int length;
	int step;
};

template<class T>    //O(1)
int SeqList<T>::GetLength()
{
	return length;
}
template<class T>    //O(n)
void SeqList<T>::PrintList()
{
	int pos;
	for(pos = 1; pos != length+1; pos++)
		cout<<pData[pos]<<" ";
	cout<<endl;
}
template<class T>
void SeqList<T>::Insert(int pos, T data)    //O(n)
{
	if(pos < 1) throw ERROR_OVERFLOW_DOWN;
	if(pos > length+1) throw ERROR_OVERFLOW_UP;
	if(length == size)
	{
		T *pTemp=new T[size+1+step];
		memcpy(pTemp,pData,sizeof(T)*(length+1));
		delete[] pData;
		pTemp=pData;
		size=size+step;
	}
	int i;
	for(i=length+1; i!=pos; i--)
		pData[i]=pData[i-1];
	pData[pos]=data;
	length++;
}
template<class T>
T SeqList<T>::Delete(int pos)     //O(n)
{
	if(pos < 1 || pos > length) throw ERROR_OVER_RANGE;
	T temp=pData[pos];
	int i;
	for(i=pos; i!=length; i++)
		pData[i]=pData[i+1];
	length--;
	return temp;
}
template<class T>
T SeqList<T>::Get(int pos)    //O(1)
{
	if(pos < 1 || pos > length) throw ERROR_OVER_RANGE;
	return pData[pos];
}
template<class T>
int SeqList<T>::Locate(T data, int start)   //O(n)
{
	if(start < 1 || start > length) throw ERROR_OVER_RANGE;
	int i;
	for(i=start; i!=length+1; i++)
		if(pData[i] == data)
			return i;
	return 0;
}
