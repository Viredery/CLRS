#include<iostream>
#include<string>
using namespace std;
void _kmp_matcher(const string &text, const string &pattern, int *prefix);
int *_compute_prefix_function(const string &pattern);
int main()
{
	string p("abababca");
	int *prefix = _compute_prefix_function(p);
	int i;
	for(i = 0; i != p.length(); i++)
		cout<<prefix[i]<<" ";
	cout<<endl;

	string t("abaabxxabbabababcab");
	_kmp_matcher(t,p,prefix);
}
int *_compute_prefix_function(const string &pattern)
{
	int m = pattern.length();
	int *prefix = new int[m];
	prefix[0] = -1;
	int k = prefix[0];
	int i;
	for(i = 1; i != m; i++)
	{
		while(k > -1 && pattern[i] != pattern[k + 1])
			k = prefix[k];
		if(pattern[i] == pattern[k + 1])
			k = k + 1;
		prefix[i] = k;
	}
	return prefix;
}
void _kmp_matcher(const string &text, const string &pattern, int *prefix)
{
	int n = text.length();
	int m = pattern.length();
	int k = -1;
	int i;
	for(i = 0; i != n; i++)
	{
		while(k > -1 && text[i] != pattern[k + 1])
			k = prefix[k];
		if(text[i] == pattern[k + 1])
			k = k + 1;
		if(k == m - 1)
		{
			cout << "pattern occurs with shift " << i - m + 1 + 1<<endl;
			k = prefix[k];
		}
	}
}
