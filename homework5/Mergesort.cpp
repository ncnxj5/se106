/*
name:RAINUE
ID:NCNXJ5
*/
#include "Mergesort.h"
/*code for Classic_merge_sort*/
void Classic_merge(vector<int> &vec,vector<int>& v1, vector<int>&v2)//the classic func
{
	int n1=v1.size();
	int n2=v2.size();
	int p1=0;
	int p2=0;
	while(p1<n1&&p2<n2)
	{
		if(v1[p1]<v2[p2])
			vec.push_back(v1[p1++]);
		else
			vec.push_back(v2[p2++]);
	}
	while (p1<n1) vec.push_back(v1[p1++]);
	while (p2<n2) vec.push_back(v2[p2++]);
}
void Classic_merge_sort(vector <int> &vec)
{
	int n=vec.size();
	if(n<=1) return;//if size <1 then return
	vector<int>v1;
	vector<int>v2;
	for(int i=0;i<n;i++)
	{
		if(i<n/2)
			v1.push_back(vec[i]);
		else
			v2.push_back(vec[i]);
	}
	Classic_merge_sort(v1);
	Classic_merge_sort(v2);
	vec.clear();
	Classic_merge(vec,v1,v2);
	return;
}
/*code for In_place_merge_sort*/
/*void print_t(vector<int> &vec)
{
	for(int i=0;i<vec.size();i++)
		cout<<vec[i]<<" ";
	cout<<"\n";
}*/
void Exange(int *n1,int *n2)//the func to exchange two nums
{
	int temp=(*n1);
	(*n1)=(*n2);
	(*n2)=temp;
}
void Insert_one(vector<int> &vec,int dest,int sou)//to insert one num into a pos in array
{
	int temp=vec[sou];
	if(dest<sou)
	for(int i=sou-1;i>=dest;i--)
	{
		vec[i+1]=vec[i];
	}
	else
	for(int i=sou+1;i<=dest;i++)
	{
		vec[i-1]=vec[i];
	}
	vec[dest]=temp;
}
void Insert(vector<int> &vec,int pos,int begin,int length)// insert an array of num in to the place
{
	for(int i=0;i<length;i++)
	{
		Insert_one(vec,pos,begin);
		pos++;
		begin++;
	}
}
void In_place_merge(vector<int> &vec,int low,int button,int high)//merge two num array using exchange
{
	//cout<<"low:"<<low<<" button:"<<button<<" high:"<<high<<endl;
	int begin1=low;
	int begin2=button+1;
	int length1=begin2-begin1;//compute the length of the two sort part
	int length2=high-begin2+1;
	while(length1>0&&length2>0)
	{
		//print_t(vec);
		//cout<<"begin1:"<<vec[begin1]<< " " << begin1<< "length1: "<<length1<<"  begin2:"<<vec[begin2]<<" " << begin2 <<"length2: "<<length2<<endl;
		if(vec[begin1]>vec[begin2])
		{
			Insert(vec,begin1,begin2,length2);
			//scout<<"after insert: ";
			//print_t(vec);
			begin2=begin1+1;
			length2--;
			begin1=begin2+length2;
			Exange(&begin1,&begin2);//make sure the begin1 is at left
			Exange(&length1,&length2);
		}
		else
		{
			begin1++;
			length1--;
		}
	}
	/*if(length1>0)
	{
		while()
	}
	else
	{

	}*/
}
void In_place_sort(vector <int> &vec,int low, int high)
{
	int button;
	if(low<high)
	{
		button=(low+high)/2;
		In_place_sort(vec,low,button);// devide in to two part
		In_place_sort(vec,button+1,high);
		In_place_merge(vec,low,button,high);//merge them
	}
	return;
}
void In_place_merge_sort(vector <int> &vec)
{
	int n=vec.size();
	In_place_sort(vec,0,n-1);
	return;
}
