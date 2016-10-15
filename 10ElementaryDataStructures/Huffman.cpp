#include<iostream>
using namespace std;
struct HNode
{
	unsigned int weight;
	unsigned int parent;
	unsigned int lchild;
	unsigned int rchild;
};
struct HCode
{
	char data;
	char code[100];	
};
class Huffman
{
public:
	void CreateHTree(int a[],int n);
	void CreateCodeTable(char b[],int n);
	void Encode(char *s,char *d);
	void Decode(char *s,char *d,int n);
	~Huffman();
	void Reverse(char *s);
	void SelectTwoMin(int &x,int &y,int front,int rear);
	HNode *HTree;
	HCode *HCodeTable;
};
void Huffman::SelectTwoMin(int &x,int &y,int front,int rear)
{
	int min1=0xffff,min2=0xffff;
	int i;
	for(i=front;i!=rear;i++)
	{
		if(HTree[i].parent==-1 && HTree[i].weight<min2)
		{
			if(HTree[i].weight<min1)
			{
				min2=min1;
				min1=HTree[i].weight;
				y=x;
				x=i;
			}else{
				min2=HTree[i].weight;
				y=i;
			}
		}
	}
}
void Huffman::CreateHTree(int a[],int n)
{
	HTree=new HNode[2*n-1];
	int i;
	for(i=0;i!=n;i++)
	{
		HTree[i].weight=a[i];
		HTree[i].parent=-1;
		HTree[i].lchild=-1;
		HTree[i].rchild=-1;
	}
	for(i=n;i!=2*n-1;i++)
	{
		int x=0,y=0;
		SelectTwoMin(x,y,0,i);
		HTree[i].lchild=x;
		HTree[i].rchild=y;
		HTree[i].parent=-1;
		HTree[i].weight=HTree[x].weight+HTree[y].weight;
		HTree[x].parent=HTree[y].parent=i;
	}
}
void Huffman::Reverse(char *s)
{
	char *p=s;
	int i=0;
	char tmp[100];
	while(*p!='\0')
	{
		tmp[i]=*p;
		i++;
		p++;
	}
	i--;
	while(i!=-1)
	{
		*s=tmp[i];
		s++;
		i--;
	}
}
void Huffman::CreateCodeTable(char b[],int n)
{
	HCodeTable=new HCode[n];
	int i;
	for(i=0;i!=n;i++)
	{
		HCodeTable[i].data=b[i];
		int child=i;
		int parent=HTree[child].parent;
		int k=0;
		while(parent!=-1)
		{
			if(child==HTree[parent].lchild)
				HCodeTable[i].code[k++]='0';
			else
				HCodeTable[i].code[k++]='1';
			child=parent;
			parent=HTree[child].parent;
		}
		HCodeTable[i].code[k]='\0';
		Reverse(HCodeTable[i].code);
	}
}
void Huffman::Encode(char *s,char *d)
{
	while(*s!='\0')
	{
		int i=0,j;
		while(*s!=HCodeTable[i].data)
			i++;
		for(j=0;HCodeTable[i].code[j]!='\0';j++)
		{
			*d=HCodeTable[i].code[j];
			d++;
		}
		s++;
	}
	*d='\0';
}
void Huffman::Decode(char *s,char *d,int n)
{
	while(*s!='\0')
	{
		int parent=2*n-2;
		while(HTree[parent].lchild!=-1)
		{
			if(*s=='0')
				parent=HTree[parent].lchild;
			else
				parent=HTree[parent].rchild;
			s++;
		}
		*d=HCodeTable[parent].data;
		d++;
	}
	*d='\0';
}
Huffman::~Huffman()
{
	delete[] HTree;
	delete[] HCodeTable;
}
int main()
{
	int i;
	Huffman hfm;
	char a[5]={'a','b','c','d','e'};
	int b[5]={12,5,7,3,4};
	hfm.CreateHTree(b,5);
	hfm.CreateCodeTable(a,5);
	for(i=0;i!=5;i++)
		cout<<hfm.HCodeTable[i].code<<endl;
	cout<<"输入为："<<endl;
	char s[100]="abddbcacbdeee";
	cout<<s<<endl;
	char d[1000],r[1000];
	cout<<"哈夫曼编码为："<<endl;
	hfm.Encode(s,d);
	cout<<d<<endl;
	cout<<"编码的解码为："<<endl;
	hfm.Decode(d,r,5);
	cout<<r<<endl;
}
