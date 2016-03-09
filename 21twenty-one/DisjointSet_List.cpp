#include<iostream>
using namespace std;
struct Node
{
	int data;
	Node *next;
	Node *rep;
};
class DisjointSet
{
public:
	DisjointSet();
	Node *head;
	Node *tail;
	int size;
	~DisjointSet();
};
DisjointSet::DisjointSet()
{
	head = tail = NULL;
	size = 0;
}
DisjointSet::~DisjointSet()
{
	while(head != NULL)
	{
		Node *p = head;
		head = head->next;
		delete p;
	}
}
DisjointSet *MakeSet(int x)
{
	Node *node = new Node;
	node->data = x;
	node->next = NULL;
	node->rep = node;
	DisjointSet *disjointSet = new DisjointSet;
	disjointSet->head = disjointSet->tail = node;
	disjointSet->size = 1;
}
DisjointSet *Union(DisjointSet *set1, DisjointSet *set2)
{
	if(set1->size < set2->size)	//make the size of set1 biger by swaping set1 and set2
	{
		Node *tmp = set2->head;
		set2->head = set1->head;
		set1->head = tmp;
		set2->tail = set1->tail;
		set1->tail = tmp;
		int size = set2->size;
		set2->size = set1->size;
		set1->size = size;
	}
	set1->tail->next = set2->head;
	Node *pCurrent = set2->head;
	while(pCurrent != NULL)
	{
		pCurrent->rep = set1->head;
		pCurrent = pCurrent->next;
	}
	set1->size = set2->size = set1->size + set2->size;
	set1->tail = set2->tail;
	set2->head = set1->head;
	set2->size = 0;
	return set1;
}
int FindSet(Node *x)
{
	if(x != NULL)
		return x->rep->data;
	return -1;
}
int main()
{
	int i;
	DisjointSet *set[17];
	for(i = 1; i <= 16; i++)
		set[i] = MakeSet(i);
	Node *node2 = set[2]->head;
	Node *node9 = set[9]->head;
	for(i = 1; i <= 15; i += 2)
		Union(set[i],set[i+1]);
	for(i = 1; i <= 13; i += 4)
		Union(set[i],set[i+2]);
	Union(set[1],set[5]);
	Union(set[11],set[13]);
	Union(set[1],set[10]);
	cout<<FindSet(node2)<<endl;
	cout<<FindSet(node9)<<endl;
	
}
