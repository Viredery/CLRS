#include<iostream>
#define ERROR_OVER_RANGE 1
using namespace std;
template<class T>
class Metrix
{
public:
	Metrix(int num);
	~Metrix();
	void CompressionStore(int row, int col, T value);
	void PrintMetrix();
private:
	T *array;
	int n;
};
template<class T>
Metrix<T>::Metrix(int num):n(num)
{
	array=new T[n*(n+1)/2];
}
template<class T>
Metrix<T>::~Metrix()
{
	delete[] array;
}
template<class T>
void Metrix<T>::CompressionStore(int row, int col, T value)
{
	if(row<1 || row>n) throw ERROR_OVER_RANGE;
	if(col<1 || col>n) throw ERROR_OVER_RANGE;
	array[row*(row-1)/2+col-1]=value;
}
template<class T>
void Metrix<T>::PrintMetrix()
{
	int i;
	for(i=0;i!=n*(n+1)/2;i++)
		cout<<array[i]<<" ";
	cout<<endl;
}
int main()
{
	Metrix<int> metrix(3);
	int i,j;
	int array[3][3]={{1,2,0},{2,0,7},{0,7,6}};
	for(i=1;i!=4;i++)
		for(j=1;j<=i;j++)
			metrix.CompressionStore(i,j,array[i-1][j-1]);
	metrix.PrintMetrix();
}
