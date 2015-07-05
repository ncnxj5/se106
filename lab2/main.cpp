#include <iostream>
#include "Citymap.h"
#include "Skycraper.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
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
		citymap map(m,n);
		//cout<<"Pop:"<<Build_city(map)<<"\n";
		ofs<<Build_city(map)<<"\n";
		map.map_out(&ofs);
	 }
	}
	else
	{
	cout<<"Input ERROR!\n";
	return 1;
	}
	return 0;
}