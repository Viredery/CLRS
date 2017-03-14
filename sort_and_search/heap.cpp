#include<iostream>
#define ERROR_EMPTY 1
using namespace std;
void swap(int *a,int *b){
	int tmp=*a;*a=*b;*b=tmp;
}
void MaxHeap(int *num,int pos,int total);
void BuildMaxHeap(int *num,int total);
void HeapSort(int *num,int total);
int main()
{
	int number;
	cin>>number;
	int *numSort=new int[number+1];
	int i;
	for(i=1;i<=number;i++)
		cin>>numSort[i];
	HeapSort(numSort,number);
	for(i=1;i<=number;i++)
		cout<<numSort[i]<<" ";
	cout<<endl;
	delete[] numSort;
	return 0;
}
void HeapSort(int *num,int total)
{
	if(total < 1)
		throw ERROR_EMPTY;
	BuildMaxHeap(num,total);
	int i,heapSize = total;
	for(i = heapSize; i != 1; i--)
	{
		swap(&num[1],&num[i]);
		heapSize--;
		MaxHeap(num,1,heapSize);
	}
}
void BuildMaxHeap(int *num,int total)
{
	int i;
	for(i = total / 2; i != 0; i--)
		MaxHeap(num,i,total);
}
void MaxHeap(int *num,int pos,int total)
{
	int largest = pos;
	while(true)
	{
		if(pos*2 <= total && num[pos*2] > num[largest])
			largest = pos * 2;
		if(pos*2+1 <= total && num[pos*2+1] > num[largest])
			largest = pos *2 + 1;
		if(largest != pos)
		{
			swap(&num[largest],&num[pos]);
			pos = largest;
		}else
			break;
	}
}
