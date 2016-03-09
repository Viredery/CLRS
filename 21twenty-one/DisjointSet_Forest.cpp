#include<iostream>
using namespace std;
struct Node
{
	int data;
	int rank;
	Node *parent;
};
Node *MakeSet(int x)
{
	Node *node = new Node;
	node->data = x;
	node->parent = node;
	node->rank = 0;
	return node;
}
Node *FindSet(Node *x)		//两趟方法：一趟沿路径上升，直至找到根；第二趟是沿查找路径下降，以便更新每个结点，使之直接指向根
{
	if(x != x->parent)
		x->parent = FindSet(x->parent);
	return x->parent;
}
void Link(Node *x, Node *y)
{
	if(x->rank > y->rank)
		y->parent = x;
	else{
		x->parent = y;
		if(x->rank == y->rank)
			y->rank = y->rank + 1;
	}
}
void Union(Node *x, Node *y)
{
	Link(FindSet(x),FindSet(y));
}
int main()
{
	int i;
	Node *set[17];
	for(i = 1; i <= 16; i++)
		set[i] = MakeSet(i);
	for(i = 1; i <= 15; i += 2)
		Union(set[i],set[i+1]);
	for(i = 1; i <= 13; i += 4)
		Union(set[i],set[i+2]);
	Union(set[1],set[5]);
	Union(set[11],set[13]);
	Union(set[1],set[10]);
	for(i = 1; i <= 16; i++)
		cout<<FindSet(set[i])->data<<endl;
}
