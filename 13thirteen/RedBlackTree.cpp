#include<iostream>
#define ERROR_NOT_EXIST 1
using namespace std;
struct Node
{
	int data;
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
	RedBlackTree(int a[], int n);
	void Insert(int data);
	void Delete(int data);
	Node *Search(int data);
private:
	Node *root;
	Node *nil;
	Node *Successor(int data);
	Node *Minimum(Node *node);
	void LeftRotate(Node *x);
	void RightRotate(Node *x);
	void RBDelete(Node *x);
	void RBInsert(Node *x);
};
RedBlackTree::RedBlackTree()
{
	nil = new Node;
	nil->color = BLACK;
	root = nil;
}
RedBlackTree::RedBlackTree(int a[], int n)
{
	nil = new Node;
	nil->color = BLACK;
	root = nil;
	int i;
	for(i = 0; i != n; i++)
		Insert(a[i]);
}
void RedBlackTree::Insert(int data)
{
	Node *newNode = new Node;
	newNode->data = data;
	newNode->color = RED;
	newNode->left = newNode->right = nil;
	Node *x = root;		//x为当前访问的结点
	Node *y = nil;		//y为当前访问的结点的双亲
	while(x != nil)		//当x为nil时，y即为应被插入的位置的结点的双亲
	{
		y = x;
		if(x->data < data)
			x = x->right;
		else
			x = x->left;
	}
	newNode->parent = y;	//设置新结点的双亲为y
	if(y == nil)		//设置y指向新结点
		root = newNode;
	else if(y->data < data)
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
void RedBlackTree::Delete(int data)
{
	Node *nodeTarget = Search(data);
	if(nodeTarget == nil)
		throw ERROR_NOT_EXIST;
	Node *nodeDeleted;
	Node *nodeChild;

	if(nodeTarget->left == nil || nodeTarget->right == nil)	//确定应被删除的结点
		nodeDeleted = nodeTarget;
	else
		nodeDeleted = Successor(data);

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
		nodeTarget->data = nodeDeleted->data;

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
Node *RedBlackTree::Successor(int data)
{
	Node *node = Search(data);
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
Node *RedBlackTree::Search(int data)
{
	Node *node = root;
	while(node != nil && node->data != data)
		if(data < node->data)
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
}
int main()
{
	int a[] = {5,4,6,7,8,3,9,19,55,20,77,90,200,647,666,677,688,699,700,701};
	RedBlackTree tree(a,20);
	tree.Insert(10);
	tree.Delete(5);
	Node *x = tree.Search(10);
	cout<<x->data<<endl;
}
