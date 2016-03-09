#include<iostream>
#define ERROR 1
#define UNBOUNDED 2
#define INFEASIBLE 3
using namespace std;
class linear_programming
{
public:
	linear_programming(int number_basic_var, int number_nonbasic_var);
	~linear_programming();
	int n;
	int m;
	int *nonbasic_set;
	int *basic_set;
	double **A;
	double *b;
	double *c;
	double v;
};
linear_programming::linear_programming(int number_basic_var, int number_nonbasic_var)
{
	n = number_basic_var;
	m = number_nonbasic_var;
	nonbasic_set = new int[n];
	basic_set = new int[m];
	b = new double[m];
	c = new double[n + m];
	A = new double*[m];
	int i;
	for(i = 0; i != m; i++)
		A[i] = new double[n];
}
linear_programming::~linear_programming()
{
	delete[] nonbasic_set;
	delete[] basic_set;
	delete[] b;
	delete[] c;
	int i;
	for(i = 0; i != n; i++)
		delete[] A[i];
	delete[] A;
}

linear_programming *_initialize_simplex(int n, double **A, double *b, double *c);
_simplex();
linear_programming *_pivot(linear_programming *lp, int l, int e)

int main()
{}

linear_programming *_initialize_simplex(int n, int m, double **A, double *b, double *c)
{
	if(n <= 0)
		throw ERROR;
	int minimum_b = b[0];
	int min = 0;
	int i,j,k;
	for(i = 1; i != n; i++)
		if(b[i] < minimum_b)
		{
			minimum_b = b[i];
			min = i;
		}
	if(minimum_b >= 0)
	{
		linear_programming *lp = new linear_programming(n,m);
		int i;
		for(i = 0; i != n; i++)
		{
			lp->nonbasic_set[i] = i;
			lp->c[i] = c[i];
		}
		for(i = 0; i != m; i++)
		{
			lp->c[n + i] = 0;
			lp->basic_set[i] = n + i;
			lp->b[i] = b[i];
			int j;
			for(j = 0; j != n; j++)
				lp->A[i][j] = -A[i][j];
		}
		lp->v = 0;
		return lp;
	}
	//建立辅助线性规划
	linear_programming *laux = new linear_programming(n+1,m);
	int i;
	for(i = 0; i != n+1; i++)
	{
		laux->nonbasic_set[i] = i;
		laux->c[i] = 0;
	}
	laux->c[n] = -1;
	laux->v = 0;
	for(i = 0; i != m; i++)
	{
		laux->c[n + 1 + i] = 0;
		laux->basic_set[i] = n + 1 + i;
		laux->b[i] = b[i];
		for(j = 0; j != n; j++)
			laux->A[i][j] = -A[i][j];
		laux->A[i][n] = 1;
	}
	//得到可行解
	l = n + 1 + k;		//换出变量
	laux = _pivot(laux,l,n);
	//重复调用_pivot()，直到得到laux的最优解
	while(true)
	{
		int min_var;
		for(min_var = 0; min_var != laux->n + laux->m; min_var++)
			if(laux->c[min_var] > 0)
				break;
		if(min_var == laux->n + laux->m)
			break;
		
		int pos_min_var;
		for(i = 0; i != n; i++)
			if(laux->nonbasic_set[i] == min_var)
			{
				pos_min_var = i;
				break;
			}
		int pos_max_limit;
		double min = 0xffff;
		for(i = 0; i != m; i++)
		{
			if(laux->A[i][pos_min_var] > 0)
			{
				int temp = laux->b[i] / laux->A[i][pos_min_var];
				if(temp < min)
				{
					min = temp;
					pos_max_limit = i;
				}
			}
		}
		if(min == 0xffff)
			throw UNBOUNDED;
		else
			laux = _pivot(laux,pos_max_limit,pos_min_var);
	//根据最优解是否为0,来判断是否存在这个线性规划是否可行
	if(laux->v != 0)
		throw INFEASIBLE;
	//有可行解,即laux->v == 0时
	for(i = 0; i != n; i++)
		laux->c[i] = c[i];
	for(i = 0; i != m; i++)
		laux->c[n + i] = 0;
	for(i = 0; i != n + 1; i++)
	{
		if(laux->nonbasic_set[i] == n && i != n)
		{
			laux->nonbasic_set[i] = laux->nonbasic_set[n];
			for(j = 0; j != m; j++)
				laux->A[j][i] = laux->A[j][n];
			break;
		}
	}
	laux->n = n;
	for(i = 0; i != m; i++)
	{
		if(laux->basic_set[i] < n)
		{
			lp->v = v + lp->c[ laux->basic_set[i] ] * lp->b[i];
			for(j = 0; j != n; j++)
				lp->c[ lp->nonbasic_set[j] ] = lp->c[ lp->nonbasic_set[j] ] - lp->c[ laux->basic_set[i] ] * lp->A[i][j];
			lp->c[ laux->basic_set[i] ] = 0;
		}
	}
}
_simplex(int n, int m, double **A, double *b, double *c)
{
	linear_programming *lp = _initialize_simplex(n,m,A,b,c);
	int i;
	while(true)
	{
		//总选择具有最小下标的变量来防止循环
		int min_var;
		for(min_var = 0; min_var != lp->n + lp->m; min_var++)
			if(lp->c[min_var] > 0)
				break;
		if(min_var == lp->n + lp->m)
			break;
		
		int pos_min_var;
		for(i = 0; i != n; i++)
			if(lp->nonbasic_set[i] == min_var)
			{
				pos_min_var = i;
				break;
			}
		int pos_max_limit;
		double min = 0xffff;	//初始最大值，若比值temp超出该值且不为无限大则系统会崩溃
		for(i = 0; i != m; i++)
		{
			if(lp->A[i][pos_min_var] > 0)
			{
				int temp = lp->b[i] / lp->A[i][pos_min_var];
				if(temp < min)
				{
					min = temp;
					pos_max_limit = i;
				}
			}
		}
		if(min == 0xffff)
			throw UNBOUNDED;
		else
			lp = _pivot(lp,pos_max_limit,pos_min_var);
	}
	for(i = 0; i != n; i++)
	{
		if(lp->basic_set[i] < n)
		cout<<lp->basic_set[i]<<" = "<<lp->b[i]<<endl;
	}
	for(i = 0; i != m; i++)
	{
		if(lp->nonbasic_set[i] < n)
		cout<<lp->nonbasic_set[i]<<" = "<<0<<endl;
	}
	cout<<"result = "<<lp->v<<endl;
}
linear_programming *_pivot(linear_programming *lp, int l, int e)
{
	lp->b[l] = lp->b[l] / lp->A[l][e];
	int i,j;
	for(i = 0; i != n; i++)
		if(i != e)
			lp->A[l][i] = lp->A[l][i] / lp->A[l][e];
	lp->A[l][e] = 1 / lp->A[l][e];
	for(i = 0; i != m; i++)
		if(i != l)
		{
			lp->b[i] = lp->b[i] - lp->A[i][e] * lp->b[l];
			for(j = 0; j != n; j++)
				if(j != e)
					lp->A[i][j] = lp->A[i][j] - lp->A[i][e] * lp->A[l][j];
			lp->A[i][e] = - lp->A[i][e] * lp->A[l][e];
		}
	lp->v = lp->v + lp->c[ lp->nonbasic_set[e] ] * lp->b[l];
	for(i = 0; i != n; i++)
		if(i != e)
			lp->c[ lp->nonbasic_set[i] ] = lp->c[ lp->nonbasic_set[i] ] - lp->c[ lp->nonbasic_set[e] ] * lp->A[l][i];
	lp->c[ lp->basic_set[l] ] = - lp->c[ lp->nonbasic_set[e] ] * lp->A[l][e];
	lp->c[ lp->nonbasic_set[e] ] = 0;

	temp = lp->basic_set[l];
	lp->basic_set[l] = lp->nonbasic_set[e];
	lp->nonbasic_set[e] = temp;
	return lp;
}
