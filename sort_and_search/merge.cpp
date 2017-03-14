#include<iostream>
using namespace std;
void merge(int *,int,int,int);
void merge_sort(int *,int,int);
int main()
{
	int number;
	cin>>number;
	int *numSort=new int[number];
	int i;
	for(i=0;i!=number;i++)
		cin>>*(numSort+i);
	merge_sort(numSort,0,number-1);
	for(i=0;i!=number;i++)
		cout<<*(numSort+i)<<" ";
	cout<<endl;
	delete[] numSort;
	return 0;
}

void merge_sort(int *num,int first,int last)
{
	if(first<last)
	{
		int avarge=(last+first)/2;
		merge_sort(num,first,avarge);
		merge_sort(num,avarge+1,last);
		merge(num,first,last,avarge);
	}
}
void merge(int *num,int first,int last,int avarge)
{
	int numberOne=avarge-first+1;
	int numberTwo=last-avarge;
	int *tmpOne=new int[numberOne+1];
	int *tmpTwo=new int[numberTwo+1];
	int i;
	for(i=0;i!=numberOne;i++)
		*(tmpOne+i)=*(num+first+i);
	*(tmpOne+numberOne)=0xffff;
	int j;
	for(j=0;j!=numberTwo;j++)
		*(tmpTwo+j)=*(num+avarge+1+j);
	*(tmpTwo+numberTwo)=0xffff;
	int k;
	i=j=0;
	for(k=first;k!=last+1;k++)
	{
		if( *(tmpOne+i) < *(tmpTwo+j) )
		{
			*(num+k)=*(tmpOne+i);
			i++;
		}else{
			*(num+k)=*(tmpTwo+j);
			j++;
		}
	}
	delete[] tmpOne;
	delete[] tmpTwo;
}
