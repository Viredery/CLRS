#include<iostream>
using namespace std;
template<class T>
void insertion_sort(T *num,int total)
{
	int i,j;
	for(i=2;i<=total;i++)
		if(num[i]<num[i-1])
		{	num[0]=num[i];
			for(j=i-1;num[0]<num[j];j--)
				num[j+1]=num[j];
			num[j+1]=num[0];
		}
}
int main()
{
	int number,i;
	cin>>number;
	int *numSort=new int[number+1];
	for(i=1;i<=number;i++)
		cin>>numSort[i];
	insertion_sort(numSort,number);
	for(i=1;i<=number;i++)
		cout<<numSort[i]<<" ";
	cout<<endl;
	delete[] numSort;
	return 0;
}
