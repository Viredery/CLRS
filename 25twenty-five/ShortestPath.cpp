#include<iostream>
#define ERROR_EXCESS_VERTEXNUM 1
#define MAXIMUM 0xffffff
using namespace std;
class Graph
{
public:
	Graph(int n);
	~Graph();
	void AllPairsShortestPath();
	void FloydWarshall();
private:
	int **weight;
	int number;
	void ExtendShortestPaths(int **arrayFrom, int **arrayTo);
};
Graph::Graph(int n)
{
	number = n;
	weight = new int*[number + 1];
	int i,j;
	for(i = 1; i <= number; i++)
	{
		weight[i] = new int[number + 1];
		for(j = 1; j <= number; j++)
			i != j ? weight[i][j] = MAXIMUM : weight[i][j] = 0;
	}
/*	cout<<"请输入图的边数："<<endl;
	int numE;
	cin>>numE;
	for(i = 1; i <= numE; i++)
	{
		cout<<"分别输入第"<<i<<"条边的起始点、结束点和权重："<<endl;
		int vertexone,vertextwo,w;
		cin>>verteFrom>>vertexTo>>w;
		if(vertexFrom > number || vertexTo > number || vertexFrom <= 0 || vertexTo <= 0)
			throw ERROR_EXCESS_VERTEXNUM;
		weight[vertexFrom,vertexTo] = w;
	}*/
	weight[1][2] = 3;
	weight[1][3] = 8;
	weight[1][5] = -4;
	weight[2][5] = 7;
	weight[2][4] = 1;
	weight[3][2] = 4;
	weight[4][3] = -5;
	weight[4][1] = 2;
	weight[5][4] = 6;
}
Graph::~Graph()
{
	int i;
	for(i = 1; i <= number; i++)
		delete[] weight[i];
	delete[] weight;
}
void Graph::ExtendShortestPaths(int **arrayFrom, int **arrayTo)
{
	int i,j,k;
	for(i = 1; i <= number; i++)
		for(j = 1; j <= number; j++)
		{
			arrayTo[i][j] = MAXIMUM;
			for(k = 1; k <= number; k++)
				if(arrayTo[i][j] > arrayFrom[i][k] + weight[k][j])
					arrayTo[i][j] = arrayFrom[i][k] + weight[k][j];
		}
}
void Graph::AllPairsShortestPath()
{
	//create dynamic arrays
	int **arrayone = new int*[number + 1];
	int **arraytwo = new int*[number + 1];
	int i,j;
	for(i = 1; i <= number; i++)
	{
		arrayone[i] = new int[number + 1];
		arraytwo[i] = new int[number + 1];
	}
	//arrayone[i][j] = weight[i][j] by initialising
	for(i = 1; i <= number; i++)
		for(j = 1; j <= number; j++)
			arrayone[i][j] = weight[i][j];
	//use two arrays by turns
	j = 1;
	for(i = 1; i <= number; i = i * 2)
	{
		if(j % 2 == 1)
			ExtendShortestPaths(arrayone,arraytwo);
		else
			ExtendShortestPaths(arraytwo,arrayone);
		j++;
	}
	//output the result about shortest paths
	int **&result = (j & 2 == 1 ? arrayone : arraytwo);
	for(i = 1; i <= number; i++)
	{
		for(j = 1; j <= number; j++)
			cout<<result[i][j]<<" ";
		cout<<endl;
	}
	//delete dynamic arrays
	for(i = 1; i <= number; i++)
	{
		delete[] arrayone[i];
		delete[] arraytwo[i];
	}
	delete[] arrayone;
	delete[] arraytwo;
}
void PrintPaths(int **parent, int i, int j)
{
	if(i == j)
		cout<<i<<" ";
	else if(parent[i][j] == 0)
		cout<<"no path"<<endl;
	else{
		PrintPaths(parent,i,parent[i][j]);
		cout<<j<<" ";
	}
}
void Graph::FloydWarshall()
{
	int array[number + 1][number + 1];
	int **parent = new int*[number + 1];
	int i,j,k;
	for(i = 1; i <= number; i++)
	{
		parent[i] = new int[number + 1];
		for(j = 1; j <= number; j++)
		{
			array[i][j] = weight[i][j];
			i == j || array[i][j] == MAXIMUM ? parent[i][j] = 0 : parent[i][j] = i;
		}
	}
	for(k = 1; k <= number; k++)
		for(i = 1; i <= number; i++)
			for(j = 1; j <= number; j++)
				if(array[i][j] > array[i][k] + array[k][j])
				{
					array[i][j] = array[i][k] + array[k][j];
					parent[i][j] = parent[k][j];
				}
	for(i = 1; i <= number; i++)
	{
		for(j = 1; j <= number; j++)
			cout<<array[i][j]<<" ";
		cout<<endl;
	}
	for(i = 1; i <= number; i++)
		for(j = 1; j <= number; j++)
		{
			PrintPaths(parent,i,j);
			cout<<endl;
		}
	for(i = 1; i <= number; i++)
		delete[] parent[i];
	delete[] parent;
}
int main()
{
	Graph graph(5);
//	graph.AllPairsShortestPath();
	graph.FloydWarshall();
}
