/*
 * File: RandomWriter.cpp
 * ----------------------
 * [TODO: fill in your name and student ID]
 * Name: RAINUE
 * Student ID: NCNXJ5
 * This file is the starter project for the random writer problem.
 * [TODO: extend the documentation]
 */

#include <fstream>
#include <iostream>
#include <string>
//#include <vector>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"

#include "vector.h"
#include "filelib.h"
using namespace std;

/*string find_highest(vector<string>* vp)
{
	vp->sort(vp->begin(),vp->end());
	string old_s;
	string new_s;
	string heighest=(*vp)[0];
	int heighest_num=1;
	int num=1;
	for(int i=0;i<(*vp).size()-1;++i)
	{
		old_s=(*vp)[i];
		new_s=(*vp)[i+1];
		if(old_s==new_s)
		{
			num++;
			if(num>heighest_num)
			{
				heighest_num=num;
				heighest=new_s;
			}
		}
		else
		{
			num=1;
		}
	}
	return heighest;
}*/
string writer(string name,int order)
{
	//cout<<"in writer\n";
	ifstream input(name.c_str());
	Map<string,vector<char>*> map;
	//vector<string> large_a;
	//cout<<"name:"<<name<<"\norder:"<<order;
	char ch;
	string text="";
	string output="";
	while (input.get(ch)) 
	{
		string temp=" ";
		temp[0]=ch;
		text+=temp;
        /* ... process ch ... */
		//cout<<ch;
	}
	//cout<<"text size: "<<text.size()<<"\n";
	int highest_num=1;
	string highest_string="";
	for(int i=0;i<text.size()-order;i++)
	{
		string temp="";
		for(int j=0;j<order;j++)
		{
			string t=" ";
			t=text[i+j];
			temp+=t; 
		}
		//large_a.push_back(temp);
		//cout<<temp<<"\n";	
		if (map.containsKey(temp))//if the temp has already in the map 
			//then just push the next char into the vector
		{
			 vector<char>* vp=map.get(temp);
			 vp->push_back(text[i+order]);
			 if(vp->size()>highest_num)
			 {
			 	highest_num=vp->size();
			 	highest_string=temp;
			 }
		}
		else
		//if the temp haven't been in the map then new the vector and put them in
		{
			vector<char>* vp=new vector<char>;
			vp->push_back(text[i+order]);
			map.put(temp,vp);
		}
	}
	//string highest=find_highest(&large_a);
	//cout<<"build_output\n";
	output=highest_string;
	string key=highest_string;
	for(int i=0;i<2000-order;++i)
	{
		//cout<<"loop\n";
		vector<char>* vp=map.get(key);
		if(vp==NULL)
			return output;
		char next=(*vp)[randomInteger(0, vp->size()-1)];
		string temp=" ";
		temp[0]=next;
		output+=temp;
		for(int j=0;j<order-1;j++)
		{
			key[j]=key[j+1];
		}
		key[order-1]=next;
	}
	//cout<<"finished\n";
	return output;
}
int main() 
{
	while(1)
	{
	string name="";
	cout<<"Enter the source text: ";
	cin>>name;
	ifstream input(name.c_str());
	if(!input)
	cout<<"Unable to open that file.  Try again.\n";
	else
		{
		while(1)
		{
			bool if_legal=true;
			string temp;
			cout<<"Enter the Markov order [0-10]: ";
			cin>>temp;
			for(int i=0;i<temp.size();++i)
			{
				if(temp[i]<'0'||temp[i]>'9')
					if_legal=false;
			}
			int order;
			if(if_legal)
			order=atoi(temp.c_str());
			if(order<0&&order>10)
				if_legal=false;
			if(if_legal)
			{
				string output=writer(name,order);
				cout<<output;
				break;
			}
			else
			{
				cout<<"Illegal integer format.  Try again\n";
			}
		}
		break;
		}
	}

  return 0;
}
