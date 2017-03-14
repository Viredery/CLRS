#include<iostream>
using namespace std;
void countingsort(int *num,int total,int max);
int main()
{
	int max,number;
	cin>>max>>number;
	int *numSort=new int[number];
	int i;
	for(i=0;i!=number;i++)
		cin>>numSort[i];
	countingsort(numSort,number,max);
	for(i=0;i!=number;i++)
		cout<<numSort[i]<<" ";
	cout<<endl;
	return 0;
}
void countingsort(int *num,int total,int max)
{
	int array[max],count=0;
	int i;
	for(i=0;i!=max;i++)
		array[i]=0;
	for(i=0;i!=total;i++)
		array[num[i]]++;
	for(i=0;i!=max;i++)
	{
		while(array[i]!=0)
		{
			num[count]=i;
			count++;
			array[i]--;
		}
	}
		
}
