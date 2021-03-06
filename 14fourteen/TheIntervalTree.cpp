//区间树，关键字为区间的低端点，附加信息为以某一结点为根的子树中所有区间的高端点的最大值
#include<iostream>
#define ERROR_NOT_EXIST 1
using namespace std;
struct Interval
{
	int low;
	int high;
};
struct Node
{
	Interval interval;
	int max;
	bool color;
	Node *parent;
	Node *left;
	Node *right;
};
static const int BLACK = 1;
static const int RED = 0;
class RedBlackTree
{
public:
	RedBlackTree();
	RedBlackTree(int low[], int high[], int n);
	bool IsNil(Node *x);
	void Insert(int low, int high);
	void Delete(int low);
	Node *Search(int low);
	Node *IntervalSearch(int low, int high);
private:
	Node *root;
	Node *nil;
	Node *Successor(int low);
	Node *Minimum(Node *x);
	void LeftRotate(Node *x);
	void RightRotate(Node *x);
	void RBDelete(Node *x);
	void RBInsert(Node *x);
	int GetMax(Node *x);
};
RedBlackTree::RedBlackTree()
{
	nil = new Node;
	nil->max = 0;
	nil->color = BLACK;
	root = nil;
}
RedBlackTree::RedBlackTree(int low[], int high[], int n)
{
	nil = new Node;
	nil->max = 0;
	nil->color = BLACK;
	root = nil;
	int i;
	for(i = 0; i != n; i++)
		Insert(low[i],high[i]);
}
bool RedBlackTree::IsNil(Node *x)
{
	if(x == nil)
		return true;
	return false;
}
void RedBlackTree::Insert(int low, int high)
{
	Node *newNode = new Node;
	newNode->interval.low = low;
	newNode->interval.high = high;
	newNode->max = high;
	newNode->color = RED;
	newNode->left = newNode->right = nil;
	Node *x = root;		//x为当前访问的结点
	Node *y = nil;		//y为当前访问的结点的双亲
	while(x != nil)		//当x为nil时，y即为应被插入的位置的结点的双亲
	{
		if(x->max < high)		//维护max的代价
			x->max = high;
		y = x;
		if(x->interval.low < low)
			x = x->right;
		else
			x = x->left;
	}
	newNode->parent = y;	//设置新结点的双亲为y
	if(y == nil)		//设置y指向新结点
		root = newNode;
	else if(y->interval.low < low)
		y->right = newNode;
	else
		y->left = newNode;
	RBInsert(newNode);	//调整以保证红黑树的性质不被破坏
}
void RedBlackTree::RBInsert(Node *node)
{
	while(node->parent->color == RED)
	{
		if(node->parent == node->parent->parent->left)
		{
			Node *uncle = node->parent->parent->right;
			if(uncle->color == RED)
			{
				node->parent->color = uncle->color = BLACK;
				uncle->parent->color = RED;
				node = uncle->parent;
			}else{
				if(node == node->parent->right)
				{
					LeftRotate(node->parent);
					node = node->left;
				}
			node->parent->parent->color = RED;
				node->parent->color = BLACK;
				RightRotate(node->parent->parent);
			}
		}else{
			Node *uncle = node->parent->parent->left;
			if(uncle->color == RED)
			{
				node->parent->color = uncle->color = BLACK;
				uncle->parent->color = RED;
				node = uncle->parent;
			}else{
				if(node == node->parent->left)
				{
					RightRotate(node->parent);
					node = node->right;
				}
				node->parent->parent->color = RED;
				node->parent->color = BLACK;
				LeftRotate(node->parent->parent);
			}
		}
	}
	root->color = BLACK;
}
void RedBlackTree::Delete(int low)
{
	Node *nodeTarget = Search(low);
	if(nodeTarget == nil)
		throw ERROR_NOT_EXIST;
	Node *nodeDeleted;
	Node *nodeChild;

	if(nodeTarget->left == nil || nodeTarget->right == nil)	//确定应被删除的结点
		nodeDeleted = nodeTarget;
	else
		nodeDeleted = Successor(low);

	Node *node = nodeDeleted->parent;				//维护max的代价
	nodeDeleted->max = 0;
	while(node != nil)
	{
		node->max = GetMax(node);
		node = node->parent;
	}

	if(nodeDeleted->left != nil)		//确定应被删除的结点的孩子（至多一个，如果没有则nodeChild等于nil）
		nodeChild = nodeDeleted->left;
	else
		nodeChild = nodeDeleted->right;

	nodeChild->parent = nodeDeleted->parent;	//连接待删除的结点的双亲和孩子
	if(nodeDeleted->parent == nil)
		root = nodeChild;
	else if(nodeDeleted == nodeDeleted->parent->left)
		nodeDeleted->parent->left = nodeChild;
	else
		nodeDeleted->parent->right = nodeChild;

	if(nodeDeleted != nodeTarget)
	{
		nodeTarget->interval.low = nodeDeleted->interval.low;
		nodeTarget->interval.high = nodeDeleted->interval.high;
	}

	if(nodeDeleted->color == BLACK)		//调整已保持红黑树的性质
		RBDelete(nodeChild);
	delete nodeDeleted;
}
void RedBlackTree::RBDelete(Node *node)
{
	while(node != root && node->color == BLACK)
	{
		if(node == node->parent->left)
		{
			Node *brother = node->parent->right;
			if(brother->color == RED)
			{
				brother->color = BLACK;
				node->parent->color = RED;
				LeftRotate(node->parent);
				brother = node->parent->right;	//此时brother的颜色为黑
			}
			if(brother->left->color == BLACK && brother->right->color == BLACK)
			{
				brother->color = RED;
				node = node->parent;
			}else{
				if(brother->right->color == BLACK) 
				{
					brother->color = RED;
					brother->left->color = BLACK;
					RightRotate(brother);
					brother = node->parent->right;
				}
				brother->color = node->parent->color;
				node->parent->color = brother->right->color = BLACK;
				LeftRotate(node->parent);
				node = root;
			}
		}else{
			Node *brother = node->parent->left;
			if(brother->color == RED)
			{
				brother->color = BLACK;
				node->parent->color = RED;
				RightRotate(node->parent);
				brother = node->parent->left;	//此时brother的颜色为黑
			}
			if(brother->left->color == BLACK && brother->right->color == BLACK)
			{
				brother->color = RED;
				node = node->parent;
			}else{
				if(brother->left->color == BLACK)
				{
					brother->color = RED;
					brother->right->color = BLACK;
					LeftRotate(brother);
					brother = node->parent->left;
				}
				brother->color = node->parent->color;
				node->parent->color = brother->left->color = BLACK;
				RightRotate(node->parent);
				node = root;
			}
		}
	}
	node->color = BLACK;
}
Node *RedBlackTree::Successor(int low)
{
	Node *node = Search(low);
	Node *result = nil;
	if(node->right != nil)
		result = Minimum(node->right);
	else{
		result = node->parent;
		while(result != nil && node == result->right)
		{
			node = result;
			result = result->parent;
		}
	}
	return result;
}
Node *RedBlackTree::Minimum(Node *node)
{
	while(node->left != nil)
		node = node->left;
	return node;
}
Node *RedBlackTree::Search(int low)
{
	Node *node = root;
	while(node != nil && node->interval.low != low)
		if(low < node->interval.low)
			node = node->left;
		else
			node = node->right;
	return node;
}
void RedBlackTree::LeftRotate(Node *x)	//函数默认x的右子树不是nil
{
	Node *y = x->right;
	//第一步
	x->right = y->left;
	if(y->left != nil)
		y->left->parent = x;
	//第二步
	y->parent = x->parent;
	if(x->parent == nil)
		root = y;
	else
		if(x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	//第三步
	y->left = x;
	x->parent = y;
	//维护max的代价
	x->max = GetMax(x);
	y->max = GetMax(y);
}
void RedBlackTree::RightRotate(Node *x)	//函数默认x的左子树不是nil
{
	Node *y = x->left;
	//第一步
	x->left = y->right;
	if(y->right != nil)
		y->right->parent = x;
	//第二步
	y->parent = x->parent;
	if(x->parent == nil)
		root = y;
	else
		if(x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
	//第三步
	y->right = x;
	x->parent = y;
	//维护max的代价
	x->max = GetMax(x);
	y->max = GetMax(y);
}
int RedBlackTree::GetMax(Node *x)
{
	int max;
	if(x->left->max > x->right->max)
		max = x->left->max;
	else
		max = x->right->max;
	if(max < x->interval.high)
		max = x->interval.high;
	return max;
}
Node *RedBlackTree::IntervalSearch(int low, int high)
{
	Node *node = root;
	while(node != nil && ( node->interval.low > high || node->interval.high < low ) )
	{
		if(node->left != nil && node->left->max > low)
			node = node->left;
		else
			node = node->right;
	}
	return node;
}
int main()
{
	int a[] = {8,15,25,16,0,6,5,19,26,17};
	int b[] = {9,23,30,21,3,10,8,20,26,19};
	RedBlackTree tree(a,b,10);
	tree.Delete(15);
	tree.Delete(25);
	Node *s = tree.IntervalSearch(22,25);
	if(!tree.IsNil(s))
		cout<<s->interval.low<<endl;
	else
		cout<<"This is an empty interval."<<endl;
}
