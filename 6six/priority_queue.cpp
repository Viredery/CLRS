//用最大堆实现优先级队列
#include<iostream>
#define ERROR_QUEUE_EMPTY 1
#define ERROR_QUEUE_FULL 2
#define ERROR_NUMBER_SMALL 3
#define ERROR_ELEMENT_NEXIST 4
using namespace std;
class PriorityQueue
{
public:
	PriorityQueue(int *a,int n);	//传入一个关键字数组，构造最大堆
	void Insert(int x);		//插入一个关键字为x的元素
	int Maximum();			//返回队列中最大关键字的元素
	int Extract();			//去掉并返回队列中最大关键字的元素
	int Delete(int pos);		//去掉并返回指定位置的元素
	void Increase(int pos,int x);	//将位置pos上的元素的关键字增加到x
private:
	void BuildPriorityQueue();
	void StayMaxHeapDown(int pos);
	void StayMaxHeapUp(int pos);
	int *pData;
	int length;
	int heapSize;
};
PriorityQueue::PriorityQueue(int *a,int n)
{
	pData = new int[n+1];
	length = heapSize = n;
	int i;
	for(i = 1; i <= n; i++)
		pData[i] = a[i-1];
	BuildPriorityQueue();
}
void PriorityQueue::BuildPriorityQueue()
{
	int pos;
	for(pos = heapSize / 2; pos != 0; pos--)
		StayMaxHeapDown(pos);
}
void PriorityQueue::StayMaxHeapDown(int pos)
{
	int largest = pos;
	while(pos <= heapSize)
	{
		int left = pos * 2, right = pos * 2 + 1;
		if(left <= heapSize && pData[left] > pData[pos])
			largest = left;
		if(right <= heapSize && pData[right] > pData[largest])
			largest = right;
		if(largest != pos)
		{
			int tmp = pData[pos];
			pData[pos] = pData[largest];
			pData[largest] = tmp;
			pos = largest;
		}else
			break;
	}
}
int PriorityQueue::Maximum()
{
	return pData[1];
}
int PriorityQueue::Extract()
{
	if(heapSize < 1)
		throw ERROR_QUEUE_EMPTY;
	int max = pData[1];
	pData[1] = pData[heapSize];
	heapSize--;
	StayMaxHeapDown(1);	
	return max;
}
void PriorityQueue::StayMaxHeapUp(int pos)
{
	while(pos > 1 && pData[pos] > pData[pos/2])
	{
		int tmp = pData[pos];
		pData[pos] = pData[pos/2];
		pData[pos/2] = tmp;
		pos = pos / 2;
	}
}
void PriorityQueue::Insert(int x)
{
	if(heapSize == length)
		throw ERROR_QUEUE_FULL;
	heapSize++;
	pData[heapSize] = x;
	StayMaxHeapUp(heapSize);
}
void PriorityQueue::Increase(int pos,int x)
{
	if(x < pData[pos])
		throw ERROR_NUMBER_SMALL;
	pData[pos] = x;
	StayMaxHeapUp(pos);
}
int PriorityQueue::Delete(int pos)
{
	if(pos > heapSize)
		throw ERROR_ELEMENT_NEXIST;
	int result = pData[pos];
	pData[pos] = pData[heapSize];
	pData[heapSize] = result;
	heapSize--;
	if(pData[pos] > pData[pos/2])
		StayMaxHeapUp(pos);
	else
		StayMaxHeapDown(pos);
	return result;
}
int main()
{
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	PriorityQueue queue(a,10);
	cout<<queue.Maximum()<<endl;
	cout<<queue.Extract()<<endl;
	cout<<queue.Delete(8)<<endl;
	queue.Insert(0);
	cout<<queue.Maximum()<<endl;
	queue.Increase(4,20);
	cout<<queue.Maximum()<<endl;
}
