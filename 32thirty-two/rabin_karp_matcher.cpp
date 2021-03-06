//假设输入的字符的范围为‘0’至‘9’或小于‘9’
#include<iostream>
#include<string>
#include<cmath>
using namespace std;
//d是指几进制，q要满足d×q的值在一个计算机字长内
void _rabin_karp_matcher(const string &t, const string &p, int d, int q);
int main()
{
	string text("9345250435934");
	string pattern("934");
	_rabin_karp_matcher(text,pattern,10,13);
}
void _rabin_karp_matcher(const string &text, const string &pattern, int d, int q)
{
	int n = text.length();
	int m = pattern.length();
	int h = pow(d,m-1);
	h = h % q;
	int p = 0;
	int t = 0;
	int i,j;
	for(i = 0; i != m; i++)
	{
		p = (d * p + pattern[i] - '0') % q;
		t = (d * t + text[i] - '0') % q;
	}
	for(i = 0; i <= n - m; i++)
	{
		if(p == t)
		{
			for(j = 0; j != m; j++)
				if(text[i + j] != pattern[j])
					break;
			if(j == m)
				cout << "pattern occurs with shift " << i + 1 <<endl;
		}
		if(i < n - m)
		{
			t = (t - (text[i] - '0') * h) * d + text[i + m] - '0';
			t = t % q;
			if(t < 0)
				t += q;
		}
	}
}
