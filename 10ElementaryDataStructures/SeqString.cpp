#include "SeqList.h"
#include<iostream>
using namespace std;
class SeqString:public SeqList<char>
{
public:
	SeqString():SeqList<char>(){}
	void Strcat(SeqString &s);
	SeqString& Substr(int i,int j,SeqString &s);
	int Strcmp(SeqString &s);
	void InsertStr(int i,SeqString &s);
	void DeleteStr(int i,int j);
	int Index(SeqString &s,int start);
	bool Replace(SeqString &t,SeqString &v);
};
void SeqString::Strcat(SeqString &s)
{
	int sLength=s.GetLength();
	int i;
	for(int i=1;i!=sLength+1;i++)
		Insert(GetLength()+1,s.Get(i));
}
SeqString& SeqString::Substr(int i,int j,SeqString &s)
{
	if(i<1) throw ERROR_OVERFLOW_DOWN;
	if(i>GetLength() || j>GetLength()) throw ERROR_OVERFLOW_UP;
	if(i>j) throw ERROR_INPUT;
	int pos,posSub=1;
	for(pos=i;pos!=j+1;pos++)
	{
		s.Insert(posSub,Get(pos));
		posSub++;
	}
	return s;
}
int SeqString::Strcmp(SeqString &s)
{
	int length=GetLength(),sLength=s.GetLength();
	int i,k;
	k=length<sLength?length:sLength;
	for(i=1;i!=k+1;i++)
		if(Get(i)>s.Get(i))
			return 1;
		else if(Get(i)<s.Get(i))
			return -1;
	if(i==k+1)
	{
		if(length==sLength)
			return 0;
		else if(length<sLength)
			return -1;
		else
			return 1;
	}
}
void SeqString::InsertStr(int i,SeqString &s)
{
	if(i<0 || i>GetLength()+1) throw ERROR_OVER_RANGE;
	int sLength=s.GetLength();
	int pos;
	for(pos=0;pos!=sLength;pos++)
		Insert(pos+i,s.Get(pos+1));
}
void SeqString::DeleteStr(int i,int j)
{
	if(i<1) throw ERROR_OVERFLOW_DOWN;
	if(i>GetLength()) throw ERROR_OVERFLOW_UP;
	if(j<0) throw ERROR_INPUT;
	int pos;
	for(pos=i;pos!=j+i;pos++)
		Delete(i);
}
int SeqString::Index(SeqString &s,int start)
{
	int length=GetLength(),sLength=s.GetLength(),i=start,j=1;
	while(i<=length && j<=sLength)
	{
		if(Get(i)==s.Get(j)){
			i++;j++;
		}else{
			i=i-j+2;j=1;
		}
	}
	if(j>sLength)
		return i-j+1;
	else
		return 0;
}
bool SeqString::Replace(SeqString &t,SeqString &v)
{
	int tLength=t.GetLength(),vLength=v.GetLength();
	int i=1,pos;
	bool success=false;
	while((pos=Index(t,i))!=0)
	{
		DeleteStr(pos,tLength);
		InsertStr(pos,v);
		i=pos+vLength;
		success=true;
	}
	return success;
}
int main()
{
	SeqString a,b,c;
	a.Insert(1,'a');
	a.Insert(2,'b');
	a.Insert(3,'c');
	b.Insert(1,'A');
	b.Insert(2,'B');
	b.Insert(3,'C');
	a.Strcat(b);
	a.PrintList();
	cout<<a.Strcmp(b)<<endl;
	a.InsertStr(1,b);
	a.PrintList();
	a.Substr(3,5,c);
	c.PrintList();
	a.DeleteStr(5,2);
	a.PrintList();
	cout<<a.Index(b,1)<<endl;
	a.Replace(b,c);
	a.PrintList();
}
