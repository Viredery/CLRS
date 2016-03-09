//该程序省略了磁盘的读（DISK-READ()）写（DISK-WRITE()）操作
//假设整个类都在内存中
#include<iostream>
#define ERROR_NOT_EXIST 1
using namespace std;
static const int t = 2;		//B树的最小度数
struct Node
{
	int length;
	int key[2 * t];		//不使用数组的下标为0的位置
	Node *child[2 * t + 1];
	bool leaf;
};
class BTree
{
public:
	Node *root;
	BTree();
	BTree(int key[], int n);
	int Search(Node *node, int data, Node *&result);	//搜索以node为根的子树，得到data所在的结点result返回其在结点中的关键字序列数
	void Insert(int data);
	void Delete(Node *x, int data);
	void Print(Node *x); 
private:
	void Create();
	void SplitChild(Node *x, Node *y, int pos);	//y是x的第pos个孩子
	void InsertNonfull(Node *x, int data);
};
BTree::BTree()
{
	Create();
}
BTree::BTree(int key[], int n)
{
	Create();
	int i;
	for(i = 0; i != n; i++)
		Insert(key[i]);
}
void BTree::Create()
{
	Node *x = new Node;
	x->length = 0;
	x->leaf = true;
	root = x;
}
void BTree::SplitChild(Node *x, Node *y, int i)	//调用该函数的条件是，结点y是个满结点，即有2t-1个关键字
{
	Node *yBrother = new Node;		//分裂结点y
	yBrother->length = t - 1;
	yBrother->leaf = y->leaf;
	int pos;
	for(pos = 1; pos <= t - 1; pos++)
		yBrother->key[pos] = y->key[pos + t];
	if(!y->leaf)
		for(pos = 1; pos <= t; pos++)
			yBrother->child[pos] = y->child[pos + t];
	y->length = t - 1;

	x->length++;		//将y的中间关键字插入到x中去
	for(pos = x->length + 1; pos != i + 1; pos--)
		x->child[pos] = x->child[pos - 1];
	x->child[i + 1] = yBrother;
	for(pos = x->length; pos != i; pos--)
		x->key[pos] = x->key[pos - 1];
	x->key[i] = y->key[t];
}
void BTree::InsertNonfull(Node *x, int data)
{
	int pos = x->length;
	if(x->leaf)
	{
		while(pos >= 1 && x->key[pos] > data)
		{
			x->key[pos + 1] = x->key[pos];
			pos--;
		}
		x->key[pos + 1] = data;
		x->length += 1;
	}else{
		while(pos >= 1 && x->key[pos] > data)
			pos = pos - 1;
		pos += 1;
		if(x->child[pos]->length == 2 * t - 1)
		{
			SplitChild(x,x->child[pos],pos);
			if(x->key[pos] < data)
				pos = pos + 1;
		}
		InsertNonfull(x->child[pos],data);
	}
}
void BTree::Insert(int data)
{
	Node *r = root;
	if(r->length == 2 * t - 1)
	{
		Node *s = new Node;
		s->length = 0;
		s->leaf = false;
		s->child[1] = r;
		root = s;
		SplitChild(s,r,1);
		InsertNonfull(s,data);
	}else
		InsertNonfull(r,data);
}
int BTree::Search(Node *node, int data, Node *&result)
{
	int pos = 1;
	while(pos <= node->length && data > node->key[pos])
		pos++;
	if(pos <= node->length && data == node->key[pos])
	{
		result = node;
		return pos;
	}
	if(node->leaf)
	{
		result = NULL;
		return 0;
	}else
		Search(node->child[pos],data,result);
}
void BTree::Delete(Node *x,int data)
{
	if(x->leaf)		//1
	{
		int pos = 1;
		while(pos <= x->length && x->key[pos] < data)
			pos += 1;
		if(pos <= x->length && x->key[pos] == data)	//判断data是否存在
		{
			while(pos != x->length)
			{
				x->key[pos] = x->key[pos + 1];
				pos++;
			}
			x->length = x->length - 1;
cout<<"a"<<endl;
		}else
			throw ERROR_NOT_EXIST;
	}else{
		int pos = 1;
		while(pos <= x->length && x->key[pos] < data)
			pos += 1;
		if(pos <= x->length && x->key[pos] == data)
		{
			if(x->child[pos]->length >= t)			//2a
			{
				Node *p = x->child[pos];
				while(!p->leaf)
					p = p->child[p->length+1];
				x->key[pos] = p->key[p->length];
				Delete(x->child[pos],x->key[pos]);
			}else if(x->child[pos+1]->length >= t){		//2b
				Node *p = x->child[pos+1];
				while(!p->leaf)
					p = p->child[1];
				x->key[pos] = p->key[1];
				Delete(x->child[pos+1],x->key[pos]);
			}else{						//2c
				//*left和*right的长度均为t-1,此时合并成left，删除right
				Node *left = x->child[pos], *right = x->child[pos+1];
				left->length = 2 * t -1;
				left->key[t] = x->key[pos];
				int i;
				for(i = 1; i <= t - 1; i++)
					left->key[t + i] = right->key[i];
				if(!left->leaf)
					for(i = 1; i <= t; i++)
						left->child[t + i] = right->child[i];
				delete right;
				//将x的长度减1
				x->length = x->length - 1;
				for(i = pos; i <= x->length; i++)
					x->key[i] = x->key[i+1];
				for(i = pos + 1; i<= x->length + 1; i++)
					x->child[i] = x->child[i+1];
				//如果x是根结点且为空，则删除x
				if(x->length == 0 && x == root)
				{
					root = left;
					delete x;
				}
				//递归求解
				Delete(x->child[pos],data);
			}
		}else{
			if(x->child[pos]->length == t - 1)	//pos的可能范围为1 ~ x->length+1
			{
				if(pos != 1 && x->child[pos - 1]->length >= t)		//3a
				{
					Node *y = x->child[pos], *z = x->child[pos - 1];
					y->length += 1;
					int i;
					for(i = y->length; i != 1; i--)
						y->key[i] = y->key[i-1];
					y->key[1] = x->key[pos-1];
					x->key[pos-1] = z->key[z->length];
					if(!y->leaf)
					{
						for(i = y->length + 1; i != 1; i--)
							y->child[i] = y->child[i-1];
						y->child[1] = z->child[z->length + 1];
					}
					z->length = z->length - 1;
					Delete(y,data);
				}else if(pos != x->length + 1 && x->child[pos + 1]->length >= t){
					Node *y = x->child[pos], *z = x->child[pos + 1];
					y->length += 1;
					y->key[y->length] = x->key[pos];
					x->key[pos] = z->key[1];
					z->length = z->length - 1;
					int i;
					for(i = 1; i <= z->length; i++)
						z->key[i] = z->key[i+1];
					if(!z->leaf)
					{
						y->child[y->length + 1] = z->child[1];
						for(i = 1; i <= z->length + 1; i++)
							z->child[i] = z->child[i+1];
					}
					Delete(y,data);
				}else{						//3b
					//*y和*z的长度均为t-1,此时合并成y，删除z
					Node *y = x->child[pos];
					if(pos == 1)
					{
						Node *z = x->child[pos + 1];
						Node *left = x->child[pos], *right = x->child[pos+1];
						y->length = 2 * t -1;
						y->key[t] = x->key[pos];
						int i;
						for(i = 1; i <= t - 1; i++)
							y->key[t + i] = z->key[i];
						if(!y->leaf)
							for(i = 1; i <= t; i++)
								y->child[t + i] = z->child[i];
						delete z;
						//将x的长度减1
						x->length = x->length - 1;
						for(i = pos; i <= x->length; i++)
							x->key[i] = x->key[i+1];
						for(i = pos + 1; i<= x->length + 1; i++)
							x->child[i] = x->child[i+1];
						//如果x是根结点且为空，则删除x
						if(x->length == 0 && x == root)
						{
							root = y;
							delete x;
						}
						//递归求解
						Delete(y,data);
					}else{
						Node *z = x->child[pos - 1];
						z->length = 2 * t -1;
						z->key[t] = x->key[pos - 1];
						int i;
						for(i = 1; i <= t - 1; i++)
							z->key[t + i] = y->key[i];
						if(!z->leaf)
							for(i = 1; i <= t; i++)
								z->child[t + i] = y->child[i];
						delete y;
						//将x的长度减1
						x->length = x->length - 1;
						for(i = pos - 1; i <= x->length; i++)
							x->key[i] = x->key[i+1];
						for(i = pos; i <= x->length + 1; i++)
							x->child[i] = x->child[i+1];
						//如果x是根结点且为空，则删除x
						if(x->length == 0 && x == root)
						{
							root = z;
							delete x;
						}
						//递归求解
						Delete(z,data);
					}
				}
			}else
				Delete(x->child[pos],data);
		}	
	}
}
void BTree::Print(Node *n)
{  
	int i;
	for(i = 1; i <= n->length; i++)  
	{
		if(!n->leaf)  
			Print(n->child[i]);
		cout<<n->key[i]<<' ';  
	}
	if(!n->leaf)  
		Print(n->child[n->length + 1]);  
}  
int main()
{
	int a[]={3,47,6,7,5,10,12,1,4,11,9,16,2,19,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44};
	BTree btree(a,34);
	Node *result;
	int k = btree.Search(btree.root,9,result);
	if(result != NULL)
		cout<<result->key[k]<<endl;
	btree.Delete(btree.root,1);btree.Delete(btree.root,35);btree.Delete(btree.root,27);btree.Delete(btree.root,43);btree.Delete(btree.root,5);
	int i;
	for(i = 1;i<=6;i++)
	{
		k = btree.Search(btree.root,i,result);
		cout<<k<<endl;
	}
	btree.Print(btree.root);
	cout<<endl;
}
