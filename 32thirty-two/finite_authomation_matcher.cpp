#include<iostream>
using namespace std;
//保证a一定在数组characters内
int _search(char a, char *characters)
{
	int pos = 0;
	while(characters[pos] != a)
		pos++;
	return pos;
}
int **_compute_transition_function(int m, char *pattern, int t, char *characters);
void _finite_authomatic_matcher(int **transition, int n, char *text, int m, char *characters);
int main()
{
	char characters[3] = {'a','b','c'};
	char pattern[7] = {'a','b','a','b','a','c','a'};
	char text[17] = {'a','b','a','b','a','b','a','c','a','b','a','b','a','b','a','c','a'};
	int **transition = _compute_transition_function(7,pattern,3,characters);
	_finite_authomatic_matcher(transition,17,text,7,characters);
	int i;
	for(i = 0; i != 7+1; i++)
		delete[] transition[i];
	delete[] transition;
}



int **_compute_transition_function(int m, char *pattern, int t, char *characters)
{
	int i,j,k;
	int **transition = new int*[m + 1];
	for(i = 0; i != m + 1; i++)
		transition[i] = new int[t];
	for(i = 0; i != m + 1; i++)
		for(j = 0; j != t; j++)
		{
			int min = (i + 1 < m) ? i + 1 : m;
			bool equal = true;
			do{
				min = min - 1;
				equal = true;
				if(pattern[min] != characters[j])
					equal = false;
				for(k = min - 1; k >= 0; k--)
				{
					if(pattern[k] != pattern[i + k - min])
					{
						equal = false;
						break;
					}
				}
			}while(min > 0 && equal == false);
			if(equal == true)
				transition[i][j] = min + 1;
			else
				transition[i][j] = 0;
		}
	return transition;
}
void _finite_authomatic_matcher(int **transition, int n, char *text, int m, char *characters)
{
	int q = 0;
	int i;
	for(i = 0; i != n; i++)
	{
		q = transition[q][ _search(text[i],characters) ];
		if(q == m)
			cout << "pattern occurs with shift " << i - m + 1 + 1<<endl;	//位置比下标大1
	}
}
