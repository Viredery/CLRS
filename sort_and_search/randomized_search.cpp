#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;
//select a number in an array,which there are "n" numbers less than.
void swap(int *a, int *b){
	int swap = *a;
	*a = *b;
	*b = swap;
}
int randomized_position(int *array, int first, int last);
int randomized_search(int *array,int first,int last,int ranking);
int main()
{
	int number,ranking,conclusion;
	cin>>number>>ranking;
	int *numSort = new int[number];
	int i;
	for(i = 0; i != number; i++)
		cin>>numSort[i];
	conclusion = randomized_search(numSort,0,number-1,ranking);
	cout<<conclusion;
	return 0;
}

int randomized_search(int *array,int first,int last,int ranking)
{
	if(first == last)
		return array[first];
	int avarge=randomized_position(array,first,last);
	int position = avarge - first + 1;
	if(ranking == position)
		return array[avarge];
	else if(ranking < position)
		return randomized_search(array,first,avarge-1,ranking);
	else
		return randomized_search(array,avarge+1,last,ranking-position);
}

int randomized_position(int *array, int first, int last)
{
	srand((unsigned)time(NULL));
	int random = rand()  % (last - first + 1) + first;
	int key = array[random];
	swap(array[random],array[last]);
	int j,i = first - 1;
	for(j = first; j != last; j++)
		if(array[j] < key)
		{
			i++;
			swap(array[i],array[j]);
		}
	swap(array[last],array[i+1]);
	return i+1;
}
