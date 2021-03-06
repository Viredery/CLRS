#include<iostream>
using namespace std;
struct Point
{
	int x;
	int y;
};
int CrossProduct(Point dotA, Point dotB, Ponit dotC)	//叉积，AB×AC>0说明AB在AC的顺时针方向上
{
	return (dotB.x - dotA.x) * (dotC.y - dotA.y) - (dotC.x - dotA.x) * (dotB.y - dotA.y);
}
bool SegmentLeft(Dot dotA, Dot dotB, Dot dotC)	//连续线段P1P2和P2P3是否向左转
{
	return CrossProduct(dotA,dotB,dotC) > 0 ? true : false;	//大于0说明左转，小于0说明右转，等于0说明共线
}
void Merge(Point *num,int first,int last,int avarge,int base)
{
	int numberOne=avarge-first+1;
	int numberTwo=last-avarge;
	Point *tmpOne=new Point[numberOne+1];
	Point *tmpTwo=new Point[numberTwo+1];
	int i;
	for(i=0;i!=numberOne;i++)
	{
		tmpOne[i].x = num[first+i].x;
		tmpOne[i].y = num[first+i].y;
	}
	tmpOne[numberOne].x = tmpOne[numberOne].y = 0xffff;
	int j;
	for(j=0;j!=numberTwo;j++)
	{
		tmpTwo[j].x = num[avarge+1+j].x;
		tmpTwo[j].y = num[avarge+1+j].y;
	}
	tmpTwo[numberTwo].x = tmpTwo[numberTwo].y = 0xffff;
	int k;
	i=j=0;
	for(k=first;k!=last+1;k++)
	{
		if(tmpOne[i].x != 0xffff && tmpTwo[j].x != 0xffff)
		{
			if(CrossProduct(num[base],tmpOne[i],tmpTwo[j]) > 0)
			{
				num[k].x=tmpOne[i].x;
				num[k].y=tmpOne[i].y;
				i++;
			}else{
				num[k].x=tmpTwo[j].x;
				num[k].y=tmpTwo[j].y;
				j++;
			}
		}
		else if(tmpOne[i].x == 0xffff)
		{
			num[k].x=tmpTwo[j].x;
			num[k].y=tmpTwo[j].y;
			j++;
		}else{
			num[k].x=tmpOne[i].x;
			num[k].y=tmpOne[i].y;
			i++;
		}
	}
	delete[] tmpOne;
	delete[] tmpTwo;
}

void MergeSort(Point *num,int first,int last,int base)
{
	if(first<last)
	{
		int avarge=(last+first)/2;
		MergeSort(num,first,avarge,base);
		MergeSort(num,avarge+1,last,base);
		Merge(num,first,last,avarge,base);
	}
}

void GrahamScan(Point point[],int n)
{
	//找出y轴值最小的点（如果有多个，选择x轴值最小的那个）
	int pos = 0;
	int i;
	for(i = 1; i != n; i++)
		if(point[i].y < point[pos].y || (point[i].y == point[pos].y && point[i].x < point[pos].x))
			pos = i;
	//将剩下的点排序，按照相对与pos的位置
	Point element[n];
	for(i = 0; i != n; i++)
	{
		element[i].x = point[i].x;
		element[i].y = point[i].y;
	}
	int tmp = element[pos].x;
	element[pos].x = element[n].x; element[n].x = tmp;
	tmp = element[pos].y;
	element[pos].y = element[n].y; element[n].y = tmp;
	MergeSort(element,0,n-1,n);
	//建堆
	Point stack[n];
	int top = -1;
	stack[++top] = point[pos];
	stack[++top] = element[0];
	stack[++top] = element[1];
	for(i = 2; i != n-1; i++)
	{//应该要一直左转
	}
}
