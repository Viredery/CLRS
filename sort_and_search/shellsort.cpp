#include<iostream>
using namespace std;
template<class T>
void ShellInsert(T num[],int total)
{
	int d,i,j;
	for(d=total/2; d>=1; d=d/2)
		for(i=d+1;i<=total;i++)
			if(num[i]<num[i-d])
			{
				num[0]=num[i];
				for(j=i-d; j>0 && num[0]<num[j]; j=j-d)
					num[j+d]=num[j];
				num[j+d]=num[0];
			}
}
int main()
{
	int number;
	cin>>number;
	int *numSort=new int[number+1];
	int i;
	for(i=1;i<=number;i++)
		cin>>numSort[i];
	ShellInsert(numSort,number);
	for(i=1;i<=number;i++)
		cout<<numSort[i]<<" ";
	cout<<endl;
	delete[] numSort;
	return 0;
}
