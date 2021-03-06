//动态顺序统计
//顺寻统计树
#include<iostream>
#define ERROR_NOT_EXIST 1
using namespace std;
struct Node
{
	int data;
	int size;	//以该结点为根的子树的（内部）结点数（包括x本身）
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
	Node *OSSearch(int i);	//返回第i小的元素
	int OSRank(int data);	//确定一个元素的秩，即返回data在元素中的位置
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
	nil->size = 0;
	root = nil;
}
RedBlackTree::RedBlackTree(int a[], int n)
{
	nil = new Node;
	nil->color = BLACK;
	nil->size = 0;
	root = nil;
	int i;
	for(i = 0; i != n; i++)
		Insert(a[i]);
}
void RedBlackTree::Insert(int data)
{
	Node *newNode = new Node;
	newNode->data = data;
	newNode->size = 1;
	newNode->color = RED;
	newNode->left = newNode->right = nil;
	Node *x = root;		//x为当前访问的结点
	Node *y = nil;		//y为当前访问的结点的双亲
	while(x != nil)		//当x为nil时，y即为应被插入的位置的结点的双亲
	{
		x->size++;	//维护size的代价
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

	Node *node = nodeDeleted;				//维护size的代价
	while(node != nil)
	{
		node->size--;
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
	//维护size的代价
	y->size = x->size;
	x->size = x->left->size + x->right->size + 1;
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
	//维护size的代价
	y->size = x->size;
	x->size = x->left->size + x->right->size + 1;
}
Node *RedBlackTree::OSSearch(int i)
{
	Node *node = root;
	while(node != nil)
	{
		if(i == node->left->size + 1)
			break;
		else if(i < node->left->size + 1)
			node = node->left;
		else{
			i = i - node->left->size - 1;
			node = node->right;
		}
	}
	return node;
}
int RedBlackTree::OSRank(int data)
{
	Node *node = Search(data);
	if(node == nil)
		throw ERROR_NOT_EXIST;
	int rank = node->left->size + 1;
	while(node != root)
	{
		if(node->parent->right == node)
			rank += node->parent->left->size + 1;
		node = node->parent;
	}
	return rank;
}

int main()
{
	int a[] = {5,4,701,6,7,8,3,9,677,19,55,20,77,90,200,647,666,688,699,700};
	RedBlackTree tree(a,20);

	tree.Insert(10);
	tree.Delete(5);
tree.Delete(666);
tree.Delete(9);
tree.Delete(19);
tree.Insert(1000);
tree.Insert(1);
tree.Insert(14);
	Node *x;
	x = tree.OSSearch(1);
	cout<<x->data<<endl;
	cout<<tree.OSRank(3)<<endl;
cout<<tree.OSRank(1000)<<endl;
cout<<tree.OSRank(77)<<endl;
cout<<tree.OSRank(14)<<endl;
		int i;	
	for(i = 1; i <= 20; i++)
		cout<<tree.OSSearch(i)->data<<" ";
	cout<<endl;
}
