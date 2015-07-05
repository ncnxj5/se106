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
	ifstream ifs("square");
	int x;
	citymap best(7,7);
	for(int i=0;i<7;i++)
		for(int j=0;j<7;j++)
		{
			ifs>>x;
			best.put(x,i,j);
		}
	int m=7;
	int n=7;
	best.print_map();	
	cout<<best.caculate_pop()<<endl;
	cout<<"start testing"<<m<<","<<n<<endl;
	citymap map(n,m);
	cout<<Build_city(map,best)<<"\n";
	//map.map_out_T(&ofs);
	testing(map);
	return 0;
}