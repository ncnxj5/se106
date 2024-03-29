/*
name: RAINUE
 I D: NCNXJ5
*/
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <string.h>
#include <sstream>

using namespace std;
class Tree//the tree to rebuild
{
public:
	Tree();
	Tree(int n);
	Tree(Tree * l,Tree * r,int n);
	Tree* left;
	Tree* right;
	int num;
};
Tree::Tree()
	:num(0),left(NULL),right(NULL)
	{};
Tree::Tree(int n)
	:num(n)
	{left=NULL;right=NULL;};
Tree::Tree(Tree * l,Tree * r,int n)
	:left(l),right(r),num(n)
	{};
string get_str(string sou,int begin,int end)
//get a part of the string
{
	string ret="";
	for(int i=begin;i<=end;i++)
		ret+=sou[i];
	return ret;
}
int find_n(string s,int i)
//the func to find the NO i in the string
{
	for(int j=0;j<s.size();j++)
		if(s[j]==i)
			return j;
	return -1;
}
void print_ans(ofstream *ofs,Tree * ans)
//the func to print ans to file
{
	if(ans->left!=NULL)
		print_ans(ofs,ans->left);
	if(ans->right!=NULL)
		print_ans(ofs,ans->right);
	(*ofs)<<ans->num<<" ";
}
Tree* find_pos_order(string pr_order,string in_order)
//the func to build the tree
{
	if(pr_order.size()==in_order.size())
	{
		if(pr_order.size()==1)
		{
			Tree *t=new Tree(pr_order[0]);
			return t;
		}
	int f=pr_order[0];
	int left=find_n(in_order,f);
	//cout<<"button:"<<left<<endl;
	Tree* left_s=NULL;
	Tree* right_s=NULL;
	if(left>0)
		left_s=find_pos_order(get_str(pr_order,1,left),get_str(in_order,0,left-1));
	else
		left_s=NULL;
	if(left<pr_order.size()-1)
		right_s=find_pos_order(get_str(pr_order,left+1,pr_order.size()-1),get_str(in_order,left+1,in_order.size()-1));
	else
		right_s=NULL;
	Tree * c_t=new Tree(left_s,right_s,f);//combined them together to make a tree
	return c_t;
	}
}
int main(int argc, char** argv)
{
	//string x="abc";
	//cout<<x.substr(0,0);
	if(argc==3)
	{
	ifstream ifs;
	ifs.open(argv[1]);
	ofstream ofs;
	ofs.open(argv[2]);
	if((!ifs)||(!ofs))//make sure that the files can be open
	{
		cout<<"Can't open files!\n";
		return 1;
	}
	int num,n;
	string temp;
	getline(ifs,temp);
	stringstream ss(temp);
	ss>>num;
	/home/mblue/programc++/homework8/main.cpp//read there are how many test case
	for(int i=0;i<num;i++)
	 {
	 	string pr_temp="";
		string in_temp="";
		string pr_order="";
		string in_order="";
		getline(ifs,temp);
		getline(ifs,pr_temp);
		getline(ifs,in_temp);
		stringstream strings(temp);
		strings>>n;
		stringstream p_strings(pr_temp);
		stringstream i_strings(in_temp);
		for(int j=0;j<n;j++)
		{
			string t=" ";
			int p_t;
			int i_t;
			p_strings>>p_t;
			i_strings>>i_t;
			t=p_t;
			pr_order+=t;
			t=i_t;
			in_order+=t;
		}//get the test num and put them into a string
		Tree* ans=find_pos_order(pr_order,in_order);
		print_ans(&ofs,ans);
		//print out the ans to a file
		ofs<<"\n";
	 }
	}
	else
	{
	cout<<"Input ERROR!\n";
	return 1;
	}
	return 0;
}
