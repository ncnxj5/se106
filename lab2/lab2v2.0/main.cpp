#include <iostream>
#include "Citymap.h"
#include "Skycraper.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
void testing(citymap& map)
{
	cout<<"test finished!\n";
	map.print_map();
	cout<<"pop:"<<map.caculate_pop()<<endl;
}
int main(int argc, char** argv)
{
	if(argc==3)
	{
	ifstream ifs;
	ifs.open(argv[1]);
	ofstream ofs;
	ofs.open(argv[2]);
	if((!ifs)||(!ofs))
	{
		cout<<"Can't open files!\n";
		return 1;
	}
	int num,m,n;
	string temp;
	getline(ifs,temp);
	stringstream ss(temp);
	ss>>num;
	for(int i=0;i<num;i++)
	 {
		getline(ifs,temp);
		stringstream strings(temp);
		strings>>m>>n;
		if(m<=n)
		{
			cout<<"start testing"<<m<<","<<n<<endl;
			citymap map(m,n);
			ofs<<Build_city(map)<<"\n";
			map.map_out(&ofs);
			testing(map);
		}
		else
		{
			cout<<"start testing"<<m<<","<<n<<endl;
			citymap map(n,m);
			ofs<<Build_city(map)<<"\n";
			map.map_out_T(&ofs);
			testing(map);
		}
	 }
	}
	else
	{
	cout<<"Input ERROR!\n";
	return 1;
	}
	return 0;
}