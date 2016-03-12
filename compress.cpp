//程序中的unsigned char类型保证数据都为非负数

#include<iostream>
#include<fstream>
#define ERROR_FILE_NOTEXIST 1
#define ERROR_NOT_ASCII 2
using namespace std;
struct HNode
{
	unsigned int weight;
	int parent;
	int lchild;
	int rchild;
};
struct HCode
{
	char data;
	char code[100];	
};
class Huffman
{
public:
	void CreateHTree(int a[],int n);	//建立哈夫曼树
	void CreateCodeTable(char b[],int n);	//建立哈夫曼表
	void Encode(char *s,char *d,int n);	//编码（压缩）
	void Decode(char *s,char *d);		//解码（解压缩）
	~Huffman();				//析构函数
	HNode *HTree;				//哈夫曼树
	HCode *HCodeTable;			//哈夫曼表
private:
	void SelectTwoMin(int &x,int &y,int front,int rear);		//辅助函数for CreateHTree函数
	void Reverse(char *s);						//辅助函数for CreateCodeTable函数
	unsigned char TransferToChar(char *transbefore);		//辅助函数
	void TransferToBinary(unsigned char c,char *transafter);	//辅助函数
};
void Huffman::SelectTwoMin(int &x,int &y,int front,int rear)	//辅助函数，找到最小的两个权重
{
	int min1=0xffff,min2=0xffff;
	int i;
	for(i = front; i != rear; i++)
	{
		if(HTree[i].parent == -1 && HTree[i].weight < min2)
		{
			if(HTree[i].weight < min1)
			{
				min2 = min1;
				min1 = HTree[i].weight;
				y = x;
				x = i;
			}else{
				min2 = HTree[i].weight;
				y = i;
			}
		}
	}
}
void Huffman::CreateHTree(int a[],int n)
{
	HTree = new HNode[2*n-1];
	int i;
	for(i = 0; i != n; i++)
	{
		HTree[i].weight = a[i];
		HTree[i].parent = -1;
		HTree[i].lchild = -1;
		HTree[i].rchild = -1;
	}
	for(i=n;i!=2*n-1;i++)
	{
		int x = 0, y = 0;
		SelectTwoMin(x,y,0,i);
		HTree[i].lchild = x;
		HTree[i].rchild = y;
		HTree[i].parent = -1;
		HTree[i].weight = HTree[x].weight + HTree[y].weight;
		HTree[x].parent = HTree[y].parent = i;
	}
}
void Huffman::Reverse(char *s)	//辅助函数，将从结点读到根的编码反转
{
	char *p = s;
	int i = 0;
	char tmp[100];
	while(*p != '\0')
	{
		tmp[i] = *p;
		i++;
		p++;
	}
	i--;
	while(i != -1)
	{
		*s = tmp[i];
		s++;
		i--;
	}
}
void Huffman::CreateCodeTable(char b[],int n)
{
	HCodeTable = new HCode[n];
	int i;
	for(i = 0; i != n; i++)
	{
		HCodeTable[i].data = b[i];
		int child = i;
		int parent = HTree[child].parent;
		int k = 0;
		while(parent != -1)
		{
			if(child == HTree[parent].lchild)
				HCodeTable[i].code[k++] = '0';
			else
				HCodeTable[i].code[k++] = '1';
			child = parent;
			parent = HTree[child].parent;
		}
		HCodeTable[i].code[k] = '\0';
		Reverse(HCodeTable[i].code);
	}
}
unsigned char Huffman::TransferToChar(char *transbefore)
{
	int i,j;
	unsigned char result=0;
	for(i = 0; i != 8; i++)
	{
		char times = 1;
		for(j = i+1; j != 8; j++)
			times = times * 2;
		result = result + (transbefore[i] - '0') * times;
	}
	return result; 
}
void Huffman::Encode(char *s,char *d,int n)
{
	ifstream in(s);
	if(!in)
		throw ERROR_FILE_NOTEXIST;
	ofstream out(d);
	if(!out)
		throw ERROR_FILE_NOTEXIST;
	in.unsetf(ios::skipws);		//取消自动忽略空格等字符的设置

	unsigned char num = n;
	out<<num;
	char tmpParent,tmpLchild,tmpRchild;
	int i;
	for(i = 0; i != 2*num-1; i++)
	{
		tmpParent = HTree[i].parent;
		tmpLchild = HTree[i].lchild;
		tmpRchild = HTree[i].rchild;
		out<<tmpParent<<tmpLchild<<tmpRchild;
	}
	for(i = 0; i != num; i++)
		out<<HCodeTable[i].data;

	unsigned char c,zoreInsert = 0;
	out<<zoreInsert;		//为后面得到的zoreInsert的保存占位
	char transBefore[8];
	int pos = 0;
	while(in>>c, !in.eof())
	{
		int i=0,j;
		while(c != HCodeTable[i].data)
			i++;
		for(j = 0; HCodeTable[i].code[j] != '\0'; j++)
		{
			transBefore[pos++] = HCodeTable[i].code[j];
			if(pos == 8)
			{
				unsigned char transAfter = TransferToChar(transBefore);
				out<<transAfter;
				pos = 0;
			}
		}
	}
	//结尾的操作，即最后transbefore不到8就读完数据的情况
	zoreInsert = (8 - pos) % 8;
	if(zoreInsert != 0)
	{
		while(pos != 8)
			transBefore[pos++] = '0';
		unsigned char transAfter = TransferToChar(transBefore);
		out<<transAfter;
	}
	out.seekp(7*num-2,ios::beg);
	out<<zoreInsert;
}
//保证传入的数组长度不小于8
void Huffman::TransferToBinary(unsigned char c,char *transafter)
{
	int a = c,b,i;
	for(i = 7; i != -1; i--)
	{
		b = a % 2;
		transafter[i] = b + '0';
		a = a / 2;
	}
}
void Huffman::Decode(char *s,char *d)
{
	ifstream in(s);
	if(!in)
		throw ERROR_FILE_NOTEXIST;
	in.unsetf(ios::skipws);	
	ofstream out(d);
	if(!out)
		throw ERROR_FILE_NOTEXIST;

	delete[] HTree;
	delete[] HCodeTable;
	unsigned char num;
	in>>num;
	char tmpParent,tmpLchild,tmpRchild;
	int i;
	HTree = new HNode[2*num-1];
	for(i = 0; i != 2*num-1; i++)
	{
		in>>tmpParent>>tmpLchild>>tmpRchild;
		HTree[i].parent = tmpParent;
		HTree[i].lchild = tmpLchild;
		HTree[i].rchild = tmpRchild;
	}
	HCodeTable = new HCode[num];
	for(i = 0; i != num; i++)
		in>>HCodeTable[i].data;

	unsigned char zoreInsert;
	in>>zoreInsert;
	unsigned char c;
	char transAfter[8];
	unsigned char pos = 8;
	bool finally = false;
	while(true)
	{
		int parent=2*num-2;
		while(HTree[parent].lchild!=-1)
		{
			if(finally == true && pos == 8 - zoreInsert )
				return;
			if(pos == 8)
			{
				in>>c;
				TransferToBinary(c,transAfter);						
				if(in>>c)
					in.seekg(-1,ios::cur);
				else
					finally = true;
				pos = 0;
			}
			if(transAfter[pos++] == '0')
				parent=HTree[parent].lchild;
			else
				parent=HTree[parent].rchild;
		}
		out<<HCodeTable[parent].data;
	}
}
Huffman::~Huffman()
{
	delete[] HTree;
	delete[] HCodeTable;
}
//传入occurNum数组，同时传入两个空数组，一个数组保存出现的字符，一个数组保存每个字符出现的次数，两个数组的相同下标的元素一一对应
//无法保证传入的空数组的长度（用户传入过小长度的数组讲导致溢出）
//返回文件中出现的不同ASCII码的数量。
int GetData(int *occurNum, int totalNum, char *letter, int *occur)
{
	int i,num = -1;
	for(i = 0; i != totalNum; i++)
		if(occurNum[i] != 0)
		{
			letter[++num] = i;
			occur[num] = occurNum[i];
		}
	return num+1;
}
//读取一个文件，得到每个ASCII码的出现次数
int ReadFile(char *filename, char *letter, int *occur)
{
	ifstream in(filename);
	if(!in)
		throw ERROR_FILE_NOTEXIST;
	in.unsetf(ios::skipws);		//取消自动忽略空格等字符的设置
	char c;
	int occurNum[128] = {0};
	while(in>>c, !in.eof())
		occurNum[c]++;
	return GetData(occurNum,128,letter,occur);
}
int main()
{
	char letter[128];
	int occur[128];
	char infile[256]="/home/dingyiran/data.txt",outfile[256]="/home/dingyiran/deal.txt";	//Windows中最多允许256个字符的文件名
	cout<<"输入你要压缩的文件的路径："<<endl;
	int num = ReadFile(infile,letter,occur);
	Huffman hfm;
	hfm.CreateHTree(occur,num);
	hfm.CreateCodeTable(letter,num);
	cout<<"输入压缩文件保存的路径："<<endl;
	hfm.Encode(infile,outfile,num);
	cout<<"输入保存解压缩文件的路径:"<<endl;
	char r[256]="/home/dingyiran/deal2.txt";
	hfm.Decode(outfile,r);
}
