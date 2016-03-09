#include<iostream>
using namespace std;
void _naive_string_matcher(int n, char *t, int m, char *p);
int main()
{
	char p[6] = "adadc";
	char t[19] = "adadcfjdadadcadadc";
	_naive_string_matcher(18,t,5,p);
}
void _naive_string_matcher(int n, char *t, int m, char *p)
{
	int i,j;
	for(i = 0; i <= n - m; i++)
	{
		for(j = 0; j != m; j++)
			if(t[i + j] != p[j])
				break;
		if(j == m)
			cout << "pattern occurs with shift" << i + 1 <<endl;
	}
}
