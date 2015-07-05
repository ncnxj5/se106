/*
Name: RAINUE
ID:NCNXJ5
*/
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <iostream>

/*
the definetion of the obj citymap that store city
*/
#ifndef CITYMAP_H
#define CITYMAP_H

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
citymap::citymap(int m,int n)
:m(m),n(n)
{
  board = (int**)malloc(sizeof(int*) * m);
  //cout<<" Get board:"<<board<<"\n";
  if (NULL == board)
    {
      std::cout<<"Citymap memory allocation error.\n";
    }

  for (int i = 0; i < m; i++)
    {
      board[i] = (int*)malloc(sizeof(int) * n);
      if (NULL == board[i])
	{
	  std::cout<<"Citymap memory allocation error.\n";
	}
    }

  for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
	{
	  board[i][j] = EMPTY;
	}
    }
}
citymap::~citymap()
{
  for (int i = 0; i < m; i++)
    {
      free(board[i]);
    }
    //cout<<"free board: "<<board<<"\n";
  free(board);
}
void citymap::map_out(ofstream *ofs)
{
  for(int i=0;i<m;i++)
  {
    for(int j=0;j<n;j++)
      (*ofs)<<board[i][j]<<" ";
    (*ofs)<<"\n";
  }
}
citymap::citymap(const citymap& map)
{
  m=map.m;
  n=map.n;
  board = (int**)malloc(sizeof(int*) * m);
  if (NULL == board)
    {
      std::cout<<"Citymap memory allocation error.\n";
    }

  for (int i = 0; i < m; i++)
    {
      board[i] = (int*)malloc(sizeof(int) * n);
      if (NULL == board[i])
  {
    std::cout<<"Citymap memory allocation error.\n";
  }
    }

  for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
  {
    board[i][j] = map.board[i][j];
  }
    }
}
citymap& citymap::operator=(const citymap &map)
{
  if(&map!=this)
  {
    m=map.m;
  n=map.n;
  board = (int**)malloc(sizeof(int*) * m);
  if (NULL == board)
    {
      std::cout<<"Citymap memory allocation error.\n";
    }

  for (int i = 0; i < m; i++)
    {
      board[i] = (int*)malloc(sizeof(int) * n);
      if (NULL == board[i])
  {
    std::cout<<"Citymap memory allocation error.\n";
  }
    }

  for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
  {
    board[i][j] = map.board[i][j];
  }
    }
  }
}
int citymap::caculate_pop()
{
  int sum=0;
  //cout<<"start caculate\n";
  for (int i = 0; i < m; i++)
  {
      for (int j = 0; j < n; j++)
      {
        sum+=board[i][j];
      }
  }
  //cout<<"finished caculate\n";
  return sum;
}
void citymap::put(int col,int x,int y)
{
  if(x<n&&y<m)
    board[y][x]=col;
}
bool citymap::if_end(int x,int y)
{
  if(y>=m-2&&x>=n-1)
    return true;
  return false;
}
bool citymap::if_down_0(int x,int y)
{
  if(y>=m-2)
    return true;
  return false;
}
bool citymap::put_green(int x,int y)
{
  if(x!=0)
    if(board[y][x-1]==RED)
      return true;
  if(y!=0)
    if(board[y-1][x]==RED)
      return true;
  if(x<n-1)
    if(board[y][x+1]==RED)
      return true;
  if(y<m-1)
    if(board[y+1][x]==RED)
      return true;
  return false;
}
bool citymap::put_blue(int x,int y)
{
  if(!put_green(x,y))
    return false;
  if(x!=0)
    if(board[y][x-1]==GREEN)
      return true;
  if(y!=0)
    if(board[y-1][x]==GREEN)
      return true;
  if(x<n-1)
    if(board[y][x+1]==GREEN)
      return true;
  if(y<m-1)
    if(board[y+1][x]==GREEN)
      return true;
  return false;
}
void citymap::init()
{
  for (int i = 0; i < m; i++)
  {
      for (int j = 0; j < n; j++)
      {
        board[i][j]=EMPTY;
      }
  }
}
void citymap::print_map()
{
  for (int i = 0; i < m; i++)
  {
      for (int j = 0; j < n; j++)
      {
        cout<<board[i][j];
      }
      cout<<"\n";
  }
}
bool citymap::if_success()
{
  for (int i = 0; i < m; i++)
  {
      for (int j = 0; j < n; j++)
      {
        if(board[i][j]==GREEN)
          if(!put_green(j,i))
            return false;
        if(board[i][j]==BLUE)
          if(!put_blue(j,i))
            return false;
      }
  }
  return true;
}
bool citymap::if_left(int col,int x,int y)
{
  if(x>0)
  {
    if(board[y][x-1]==col)
      return true;
  }
  return false;
}
/*
the part of func Build_city that to help compute the result of the best solution
*/
int Build_city(citymap &map);

bool go_next(int *x,int *y,citymap& map)
{
	if(map.if_end(*x,*y))
	{
		return false;
	}
	else if(map.if_down_0(*x,*y))
	{
		(*x)++;
		if((*x)%2==0)
		(*y)=0;
		else
		(*y)=1;
	}
	else
	{
		(*y)+=2;
	}
	return true;
}
bool rest_go_next(int *x,int *y,citymap& map)
{
	if(map.if_end(*x,*y))
	{
		return false;
	}
	else if(map.if_down_0(*x,*y))
	{
		(*x)++;
		if((*x)%2==0)
		(*y)=1;
		else
		(*y)=0;
	}
	else
	{
		(*y)+=2;
	}
	return true;
}
//
bool Put(citymap & map,citymap & cur_map,int x,int y)
{
	int next_x;
	int next_y;
	if(cur_map.put_blue(x,y))//look if this pos can put blue in
	{
		next_x=x;next_y=y;
		cur_map.put(BLUE,x,y);
		bool if_next=rest_go_next(&next_x,&next_y,cur_map);
		if(if_next)
		{
			if(Put(map,cur_map,next_x,next_y))
				return true;
		}
		else
		{
			if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
			{
				map=cur_map;
				return true;
			}
		}
		cur_map.put(GREEN,x,y);
		if(if_next)
		{
			if(Put(map,cur_map,next_x,next_y))
				return true;
		}
		else
		{
			if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
			{
				map=cur_map;
				return true;
			}
		}
		cur_map.put(RED,x,y);
		if(if_next)
		{
			if(Put(map,cur_map,next_x,next_y))
				return true;
		}
		else
		{
			if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
			{
				map=cur_map;
				return true;
			}
		}
	}
	else if(cur_map.put_green(x,y))//look if this pos can put green in
	{
		next_x=x;next_y=y;
		cur_map.put(GREEN,x,y);
		bool if_next=rest_go_next(&next_x,&next_y,cur_map);
		if(if_next)
		{
			if(Put(map,cur_map,next_x,next_y))
				return true;
		}
		else
		{
			if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
			{
				map=cur_map;
				return true;
			}
		}
		cur_map.put(RED,x,y);
		if(if_next)
		{
			if(Put(map,cur_map,next_x,next_y))
				return true;
		}
		else
		{
			if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
			{
				map=cur_map;
				return true;
			}
		}
	}
	else//then only can put red in it
	{
		next_x=x;next_y=y;
		cur_map.put(RED,x,y);
		bool if_next=rest_go_next(&next_x,&next_y,cur_map);
		if(if_next)
		{
			if(Put(map,cur_map,next_x,next_y))
				return true;
		}
		else
		{
			if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
			{
				map=cur_map;
				return true;
			}
		}
	}
	return false;
}
void Put_E(citymap & cur_map,int x,int y)
{
	cur_map.put(EMPTY,x,y);
}
void Empty_rest(citymap & cur_map)
{
	int x,y;
	if(cur_map.m==1)
	{
		x=1;y=0;
	}
	else
	{
		x=0;y=1;
	}
	Put_E(cur_map,x,y);
	return;
}
bool Build_rest(citymap &map,citymap & cur_map)
{
	int x,y;
	if(cur_map.m==1)
	{
		x=1;y=0;
	}
	else
	{
		x=0;y=1;
	}
	return Put(map,cur_map,x,y);
}
void Building(citymap &map,citymap & cur_map,int x,int y)
{
	//char temp;
	int next_x=x;
	int next_y=y;
	bool if_next=go_next(&next_x,&next_y,cur_map);
	//if(cur_map.put_blue(x,y))//look if this pos can put blue in
		//if(cur_map.put_blue(x,y))
	{
		cur_map.put(BLUE,x,y);
		
		if(if_next)
		{
			Building(map,cur_map,next_x,next_y);
			//cur_map.put(EMPTY,next_x,next_y);//clean the prev ground
			//std::cout<<"ONE after:\n";
			//cur_map.print_map();
		}
		else 
		//if this step is the end step of this case 
		//then caculate the population
		{
			//cur_map.print_map();
			//std::cout<<"-----------\n";
			//cin>>temp;
			Build_rest(map,cur_map);
			//if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
				//map=cur_map;
			//Empty_rest(cur_map);
			//cur_map.init();
			//return;
		}
	}
	//if(cur_map.put_green(x,y))//look if this pos can put green in
	{
		cur_map.put(GREEN,x,y);
		if(if_next)
		{
			Building(map,cur_map,next_x,next_y);
		}
		else 
		//if this step is the end step of this case 
		//then caculate the population
		{
			Build_rest(map,cur_map);
		}
	}
	//then only can put red in it
	{
		cur_map.put(RED,x,y);
		if(if_next)
		{
			Building(map,cur_map,next_x,next_y);
		}
		else 
		//if this step is the end step of this case 
		//then caculate the population
		{
			Build_rest(map,cur_map);
			return;
		}
	}
}
int Build_city(citymap &map)
{
	//cout<<"computing\n";
	citymap cur_map(map);//copy the current map as the temp
	Building(map,cur_map,0,0);
	//cout<<"finished!\n";
	
	//cout<<"pop: "<<pop<<"\n";
	return map.caculate_pop();
}
/*
the main func of this part
*/
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
