//d叉树排序的实现
#include<iostream>
using namespace std;
class DHeap
{
public:
	DHeap(int *array, int num);
	HeapSort();
private:
	MaxHeapCreate();
	MaxHeapify(int pos);
	int *pData;
	int length;
	int d;
	int heapSize;
};
