#include<iostream>
#include<cmath>
using namespace std;

void Merge(double *num,int first,int last,int avarge)
{
	int numberOne=avarge-first+1;
	int numberTwo=last-avarge;
	double *tmpOne=new double[numberOne+1];
	double *tmpTwo=new double[numberTwo+1];
	int i;
	for(i=0;i!=numberOne;i++)
		tmpOne[i] = num[first+i];
	tmpOne[numberOne]=0xffff;
	int j;
	for(j=0;j!=numberTwo;j++)
		tmpTwo[j] = num[avarge+1+j];
	tmpTwo[numberTwo]=0xffff;
	int k;
	i=j=0;
	for(k=first;k!=last+1;k++)
	{
		if( tmpOne[i] < tmpTwo[j] )
		{
			num[k]=tmpOne[i];
			i++;
		}else{
			num[k]=tmpTwo[j];
			j++;
		}
	}
	delete[] tmpOne;
	delete[] tmpTwo;
}

void MergeSort(double *num,int first,int last)
{
	if(first<last)
	{
		int avarge=(last+first)/2;
		MergeSort(num,first,avarge);
		MergeSort(num,avarge+1,last);
		Merge(num,first,last,avarge);
	}
}


struct Dot
{
	int x;
	int y;
};
int CrossProduct(Dot dotA, Dot dotB, Dot dotC)	//叉积，AB×AC>0说明AB在AC的顺时针方向上
{
	return (dotB.x - dotA.x) * (dotC.y - dotA.y) - (dotC.x - dotA.x) * (dotB.y - dotA.y);
}
bool SegmentLeft(Dot dotA, Dot dotB, Dot dotC)	//连续线段P1P2和P2P3是否向左转
{
	return CrossProduct(dotA,dotB,dotC) > 0 ? true : false;	//大于0说明左转，小于0说明右转，等于0说明共线
}
bool OnSegment(Dot dotA, Dot dotB, Dot dotC)	//判断点C是否在线段AB上
{
	int minx,maxx,miny,maxy;
	dotA.x > dotB.x ? minx = dotB.x, maxx = dotA.x : minx = dotA.x, maxx = dotB.x;
	dotA.y > dotB.y ? miny = dotB.y, maxy = dotA.y : miny = dotA.y, maxx = dotB.y;
	if(minx <= dotC.x && maxx >= dotC.x && miny <= dotC.y && maxy >= dotC.y)
		return true;
	return false;
}
bool SegmentIntersect(Dot dot1, Dot dot2, Dot dot3, Dot dot4)	//确定两个线段是否相交
{
	int d1 = CrossProduct(dot3,dot4,dot1);
	int d2 = CrossProduct(dot3,dot4,dot2); 
	int d3 = CrossProduct(dot1,dot2,dot3);
	int d4 = CrossProduct(dot1,dot2,dot4);
	if( ((d1 < 0 && d2 > 0) || (d1 > 0 && d2 < 0)) && ((d3 < 0 && d4 > 0) || (d3 > 0 && d4 < 0)) )
		return true;
	else if(d1 == 0 && OnSegment(dot3,dot4,dot1))
		return true;
	else if(d2 == 0 && OnSegment(dot3,dot4,dot2))
		return true;
	else if(d3 == 0 && OnSegment(dot1,dot2,dot3))
		return true;
	else if(d4 == 0 && OnSegment(dot1,dot2,dot3))
		return true;
	else
		return false;
}
bool ThreePointsCollineation(Dot dot[], int n)		//确定n个点中任意三点是否共线,O(n*n*lgn)
{
	int i,j;
	double slope[n];
	for(i = 0; i != n; i++)
	{
		for(j = 0; j != n; j++)
			if(i != j)
			{
				if(dot[j].x != dot[i].x)
				{
					slope[j] = ((double)dot[j].y - (double)dot[i].y) / ((double)dot[j].x - (double)dot[i].x);
				}else
					slope[j] = 0xffff;	//设max=0xffff
			}else
				slope[j] = -0xffff;	//不可能出现的斜率
		MergeSort(slope,0,n-1);
		for(j = 0; j != n-1; j++)
			if(slope[j] == slope[j+1])
				return true;
	}
	return false;
}
int main()
{
	Dot dot[8] = {{1,2},{2,1},{3,1},{3,3},{1,10},{9,20},{18,40},{-8,-20}};
	if(SegmentIntersect(dot[0],dot[1],dot[2],dot[3]) == true)
		cout<<"相交"<<endl;
	else
		cout<<"不相交"<<endl;
	if(SegmentLeft(dot[0],dot[1],dot[3]) == true)
		cout<<"左转"<<endl;
	else
		cout<<"不左转"<<endl;
	if(ThreePointsCollineation(dot,8) == true)
		cout<<"存在共线的三点"<<endl;
	else
		cout<<"不存在共线的三点"<<endl;
}
