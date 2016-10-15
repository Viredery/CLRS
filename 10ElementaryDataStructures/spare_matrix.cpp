#include<iostream>
#include<cstring>
#define MAX_ELEMENT_NUMBER 100
#define ERROR_MATRIX_EMPTY 1
using namespace std;
template<class T>
struct MatrixNode
{
	int row;
	int col;
	T value;
};
template<class T>
struct SpareMatrix
{
	int m;
	int n;
	int t;
	MatrixNode<T> data[MAX_ELEMENT_NUMBER+1];
};
template<class T>
void QuickTransMat(SpareMatrix<T> *OrigMat,SpareMatrix<T> *TransMat)
{
	if(OrigMat->t == 0) throw ERROR_MATRIX_EMPTY;
	TransMat->m=OrigMat->n;
	TransMat->n=OrigMat->m;
	TransMat->t=OrigMat->t;
	int *number=new int[OrigMat->n+1];
	memset(number,0,(OrigMat->n+1)*sizeof(int));
	int i;
	for(i=1;i<=OrigMat->t;i++)
		number[OrigMat->data[i].col]++;
	int *position=new int[OrigMat->n+1];
	memset(position,0,(OrigMat->n+1)*sizeof(int));
	position[1]=1;
	for(i=2;i<=OrigMat->n;i++)
		position[i]=position[i-1]+number[i-1];
	for(i=1;i<=OrigMat->t;i++)
	{
		int pos=position[OrigMat->data[i].col]++;
		TransMat->data[pos].col=OrigMat->data[i].row;
		TransMat->data[pos].row=OrigMat->data[i].col;
		TransMat->data[pos].value=OrigMat->data[i].value;
	}
}
int main()
{
	SpareMatrix<int> ooo,ttt;
	ooo.m=3;ooo.n=2;ooo.t=2;
	ooo.data[1].row=1;
	ooo.data[1].col=1;
	ooo.data[1].value=1;
	ooo.data[2].row=2;
	ooo.data[2].col=1;
	ooo.data[2].value=1;
	QuickTransMat(&ooo,&ttt);
	cout<<ttt.data[2].row<<ttt.data[2].col<<ttt.data[2].value<<endl;
}
