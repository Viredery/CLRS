#include<iostream>
using namespace std;
void bubble_sort(int *,int);
int main()
{
	int number;
	cin>>number;
	int *numSort=new int[number+1];
	int i;
	for(i=1;i<=number;i++)
		cin>>numSort[i];
	bubble_sort(numSort,number);
	for(i=1;i<=number;i++)
		cout<<numSort[i]<<" ";
	cout<<endl;
	delete[] numSort;
	return 0;
}
void bubble_sort(int *num,int total)
{
	int i,j;
	for(i=1;i<=total;i++)
		for(j=total;j!=i;j--)
			if(num[j]<num[j-1])
			{
				num[0]=num[j];
				num[j]=num[j-1];
				num[j-1]=num[0];
			}
}
