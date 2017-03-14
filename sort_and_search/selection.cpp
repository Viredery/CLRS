#include<iostream>
using namespace std;
void selection_sort(int *,int);
int main()
{
	int number;
	cin>>number;
	int *numSort=new int[number+1];
	int i;
	for(i=1;i<=number;i++)
		cin>>numSort[i];
	selection_sort(numSort,number);
	for(i=1;i<=number;i++)
		cout<<numSort[i]<<" ";
	cout<<endl;
	delete[] numSort;
	return 0;
}

void selection_sort(int *num,int total)
{
	int i,j;
	for(i=1;i<=total;i++)
	{
		int min=i;
		for(j=i+1;j<=total;j++)
			if(num[j]<num[min])
				min=j;
		num[0]=num[i];
		num[i]=num[min];
		num[min]=num[0];
	}
}
