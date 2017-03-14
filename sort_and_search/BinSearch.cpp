#include<iostream>
using namespace std;
template<class T>
int BinSearch(T *a,T need,int low,int hige)
{
	int start=low-1,end=hige-1;
	while(start<=end)
	{
		int pos=(start+end)/2;
		if(a[pos]==need)
			return pos+1;
		else if(a[pos]>need)
			end=pos-1;
		else
			start=pos+1;
	}
	return 0;
}
int main()
{
	int a[10]={3,6,11,23,45,64,67,85,90,97};
	int pos=BinSearch(a,10,1,10);
	cout<<pos<<endl;
}
