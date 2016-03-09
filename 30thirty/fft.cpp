#include<iostream>
#define PI 3.14159265
using namespace std;

class complex
{
	double real;
	double imag;
	complex(double r = 0, double i = 0): real = r, imag = i {}
	complex(const complex &c): real = c.real, imag = c.imag {}
	complex& operator=(const complex &c);
	complex operator+(const complex &rc);
	complex operator-(const complex &rc);
	complex operator*(const complex &rc);
	complex operator/(const int a);
	~complex(){}
	
};
complex& complex::operator=(const complex &c)
{
	real = c.real;
	imag = c.imag;
	return *this;
}
complex complex::operator+(const complex &rc)
{
	complex result(real + rc.real, imag + rc.imag);
	return result;
}
complex complex::operator-(const complex &rc)
{
	complex result(real - rc.real, imag - rc.imag);
	return result;
}
complex complex::operator*(const complex &rc)
{
	double r = this->real * a.real - this->imag * a.imag;
	double i = this->real * a.imag + this->imag * a.real;
	complex result(r,i);
	return result;
}
complex complex::operator/(const int a)
{
	complex result(real / a, imag / a);
	return result;
}

class polynomial
{
public:
	int degree_bound;
	complex *coef;
	polynomial(int n);
	polynomial(const polynomial &p);
	polynomial& operator=(const polynomial &p);
	polynomial();
	~polynomial();
	//加法
	//求值,霍纳法则
	//乘法
};
polynomial::polynomial(int n): degree_bound = n
{
	coef = new complex[n];
}
polynomial::polynomial(const polynomial &p)
{
	degree_bound = p.degree_bound;
	coef = new complex[n];
	int i;
	for(i = 0; i != n; i++)
		ceof[i] = p.ceof[i];
}
polynomial& polynomial::operator=(const polynomial &p)
{
	delete[] coef;
	degree_bound = p.degree_bound;
	coef = new complex[n];
	int i;
	for(i = 0; i != n; i++)
		ceof[i] = p.ceof[i];
}
polynomial::~polynomial()
{
	delete[] coef;
}


complex *_recursive_fft(int n, complex *a)
{
	if(n == 1)
	{
		complex *result = new complex(a[0]);
		return result;
	}
	complex wn(cos(2 * PI / n), sin(2 * PI / n));
	complex w(1,0);
	complex a_even[n / 2];
	complex a_odd[n / 2];
	int i;
	for(i = 0; i != n / 2; i++)
	{
		a_even[i] = a[2 * i];
		a_odd[i] = a[2 * i + 1];
	}
	complex *y_even = _recursive_fft(n / 2, a_even);
	complex *y_odd = _recursive_fft(n / 2, a_odd);

	int k;
	complex *y = new complex[n];
	for(k = 0; k != n / 2; k++)
	{
		y[k] = y_even[k] + w * y_odd[k];
		y[k + n / 2] = y_even[k] - w * y_odd[k];
		w = w * wn;
	}
	delete[] y_even;
	delete[] y_odd;
	return y;
}

complex *_recursive_ifft(int n, complex *y)
{
	if(n == 1)
	{
		complex *result = new complex(y[0]);
		return result;
	}
	complex wn(cos(2 * PI / n), - sin(2 * PI / n));
	complex w(1,0);
	complex y_even[n / 2];
	complex y_odd[n / 2];
	int i;
	for(i = 0; i != n / 2; i++)
	{
		y_even[i] = y[2 * i];
		y_odd[i] = y[2 * i + 1];
	}
	complex *a_even = _recursive_fft(n / 2, y_even);
	complex *a_odd = _recursive_fft(n / 2, y_odd);

	int k;
	complex *a = new complex[n];
	for(k = 0; k != n / 2; k++)
	{
		a[k] = (a_even[k] + w * a_odd[k]) / n;
		a[k + n / 2] = (a_even[k] - w * a_odd[k]) / n;
		w = w * wn;
	}
	delete[] a_even;
	delete[] a_odd;
	return a;
}
