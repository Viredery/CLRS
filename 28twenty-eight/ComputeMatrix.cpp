#include<iostream>
using namespace std;
const int N = 4;	//Define the size of the Matrix
template< typename T >
void Strassen(int n, T A[][N], T B[][N], T C[][N]);
template< typename T >
void Input(int n, T p[][N]);
template< typename T >
void Output(int n, T C[][N]);
int main() 
{   
	//Define three Matrices
	int A[N][N],B[N][N],C[N][N];       
	//对A和B矩阵赋值
	Input(N,A);Input(N,B);
	//调用Strassen方法实现C=A*B
	Strassen(N, A, B, C);
	//输出矩阵C中值
	Output(N, C);
}
template< typename T >
void MatrixAdd(int n, T A[][N], T B[][N], T C[][N])
{
	for(int i = 0; i != n; i++)
		for(int j = 0; j != n; j++)
			C[i][j] = A[i][j] + B[i][j];
}
template< typename T>
void MatrixMinus(int n, T A[][N], T B[][N], T C[][N])
{
	for(int i = 0; i != n; i++)
		for(int j = 0; j != n; j++)
			C[i][j] = A[i][j] - B[i][j];
}
template< typename T >
void Strassen(int n, T A[][N], T B[][N], T C[][N])
{
	if(n == 1)
	{
		C[0][0] = A[0][0] * B[0][0];
		return;
	}
	T a[N][N],b[N][N],c[N][N],d[N][N];
	T e[N][N],f[N][N],g[N][N],h[N][N];
	T r[N][N],s[N][N],t[N][N],u[N][N];
	T p1[N][N],p2[N][N],p3[N][N],p4[N][N],p5[N][N],p6[N][N],p7[N][N];
	T temp1[N][N],temp2[N][N];
	for(int i = 0; i != n/2; i++)
		for(int j = 0; j != n/2; j++)
		{
			a[i][j] = A[i][j];
			b[i][j] = A[i][j+n/2];
			c[i][j] = A[i+n/2][j];
			d[i][j] = A[i+n/2][j+n/2];
			e[i][j] = B[i][j];
			f[i][j] = B[i][j+n/2];
			g[i][j] = B[i+n/2][j];
			h[i][j] = B[i+n/2][j+n/2];
		}

	MatrixMinus(n/2,f,h,temp1);
	Strassen(n/2,a,temp1,p1);
	MatrixAdd(n/2,a,b,temp1);
	Strassen(n/2,temp1,h,p2);
	MatrixAdd(n/2,p1,p2,s);

	MatrixAdd(n/2,c,d,temp1);
	Strassen(n/2,temp1,e,p3);
	MatrixMinus(n/2,g,e,temp1);
	Strassen(n/2,d,temp1,p4);
	MatrixAdd(n/2,p3,p4,t);

	MatrixAdd(n/2,a,d,temp1);
	MatrixAdd(n/2,e,h,temp2);
	Strassen(n/2,temp1,temp2,p5);
	MatrixMinus(n/2,b,d,temp1);
	MatrixAdd(n/2,g,h,temp2);
	Strassen(n/2,temp1,temp2,p6);
	MatrixAdd(n/2,p5,p4,temp1);
	MatrixMinus(n/2,temp1,p2,temp2);
	MatrixAdd(n/2,temp2,p6,r);

	MatrixMinus(n/2,a,c,temp1);
	MatrixAdd(n/2,e,f,temp2);
	Strassen(n/2,temp1,temp2,p7);
	MatrixAdd(n/2,p5,p1,temp1);
	MatrixMinus(n/2,temp1,p3,temp2);
	MatrixMinus(n/2,temp2,p7,u);

	for(int i = 0; i != n/2; i++)
		for(int j = 0; j != n/2; j++)
		{
			C[i][j] = r[i][j];
			C[i][j+n/2] = s[i][j];
			C[i+n/2][j] = t[i][j];
			C[i+n/2][j+n/2] = u[i][j];
		}
}
template< typename T >
void Input(int n, T p[][N])
{
	for(int i = 0; i != n; i++)
	{
		cout<<"Input "<<n<<" elements in line "<<i+1<<" :"<<endl;
		for(int j = 0; j != n ; j++)
			cin>>p[i][j];
	}
}
template< typename T >
void Output(int n, T C[][N])
{
	cout<<"The Output Matrix is :"<<endl;
	for(int i = 0; i != n; i++)
	{
		for(int j = 0; j != n ; j++)
			cout<<C[i][j]<<" ";
		cout<<endl;
	}
}

