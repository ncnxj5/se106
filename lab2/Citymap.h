#ifndef CITYMAP_H
#define CITYMAP_H

#include <stdlib.h>
#include <string.h>
#include <fstream>

#define EMPTY 0
#define RED 1
#define GREEN 2
#define BLUE 3

using namespace std;
class citymap
{
public:
	citymap(int m,int n);
	citymap(const citymap &map);
	citymap& operator=(const citymap &map);//map 
	~citymap();
	void map_out(ofstream *ofs);
	int caculate_pop();
	int **board;
	int m,n;
	void put(int col,int x,int y);
	bool if_end(int x,int y);
	bool if_down_0(int x,int y);

	bool put_green(int x,int y);
	bool put_blue(int x,int y);
	bool if_left(int col,int x,int y);
	void init();
	void print_map();
	bool if_success();
};

#endif