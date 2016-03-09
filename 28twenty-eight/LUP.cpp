//求解线性方程组，LUP分解+正向替换与逆向替换
#include<iostream>
#include<cmath>
using namespace std;
double** _input_A(int n);
double* _input_b(int n);
void _output(int n, double *x);
int* _lup_decomposition(int n, double **a);
double* _lup_solve(int n, double **a, double *b, int *p);
void clean(int n, double **a, double *b, int *p, double *x);
int main()
{
	cout << "input n:" << endl;
	int n;
	cin >> n;
	double **a = _input_A(n);
	double *b = _input_b(n);
	int *p = _lup_decomposition(n,a);
	double *x = _lup_solve(n,a,b,p);
	_output(n,x);
	clean(n,a,b,p,x);
}

double** _input_A(int n)
{
	cout << "input A:" << endl;
	double **a = new double*[n];
	int line, row;
	for(line = 0; line != n; line++)
	{
		a[line] = new double[n];
		for(row = 0; row != n; row++)
			cin >> a[line][row];
	}
	return a;
}
double* _input_b(int n)
{
	cout << "input b:" << endl;
	double *b = new double[n];
	int pos;
	for(pos = 0; pos != n; pos++)
		cin >> b[pos];
	return b;
}
int* _lup_decomposition(int n, double **a)
{
	int *p = new int[n];
	int line, row, pos;
	for(line = 0; line != n; line++)
		p[line] = line;
	for(pos = 0; pos != n; pos++)
	{
		double max = 0;
		int pos_max = -1;
		for(line = pos; line != n; line++)
		{
			if(fabs(a[line][pos]) > max)
			{
				max = fabs(a[line][pos]);
				pos_max = line;
			}
		}
		if(max == 0)
		{
			cerr << "singular matrix" <<endl;
		}
		double temp;
		temp = p[pos];
		p[pos] = p[pos_max];
		p[pos_max] = temp;
		for(row = 0; row != n; row++)
		{
			temp = a[pos_max][row];
			a[pos_max][row] = a[pos][row];
			a[pos][row] = temp;
		}
		for(line = pos + 1; line != n; line++)
		{
			a[line][pos] = a[line][pos] / a[pos][pos];
			for(row = pos + 1; row != n; row++)
				a[line][row] = a[line][row] - a[line][pos] * a[pos][row];
		}
	}
	return p;
}
double* _lup_solve(int n, double **a, double *b, int *p)
{
	double *y = new double[n];
	int line, row;
	for(line = 0; line != n; line++)
	{
		y[line] = b[p[line]];
		for(row = 0; row != line; row++)
			y[line] -= a[line][row] * y[row];	
	}
	double *x = new double[n];
	for(line = n - 1; line >= 0; line--)
	{
		x[line] = y[line];
		for(row = line + 1; row != n; row++)
			x[line] -= a[line][row] * x[row];
		x[line] = x[line] / a[line][line];
	}
	delete[] y;
	return x;
}
void _output(int n, double *x)
{
	cout << "output x:" <<endl;
	int line;
	for(line = 0; line != n; line++)
		cout << x[line] << " ";
	cout << endl;
}
void clean(int n, double **a, double *b, int *p, double *x)
{
	int line;
	for(line = 0; line != n; line++)
		delete[] a[line];
	delete[] a;
	delete[] b;
	delete[] x;
}
