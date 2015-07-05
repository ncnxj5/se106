#ifndef CITYMAP_H
#define CITYMAP_H

#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>


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
	void map_out_T(ofstream *ofs);
	int caculate_pop();
	int **board;
	int m,n;
	void put(int col,int x,int y);
	bool if_end(int x,int y);
	bool if_down(int x,int y);
	bool put_green(int x,int y);
	bool put_blue(int x,int y);
	int blue_less(int x,int y);
	bool if_left(int col,int x,int y);
	bool if_up_is(int col,int x,int y);
	bool if_down_is(int col,int x,int y);
	bool if_this(int col,int x,int y);
	void init();
	void print_map();
	bool if_success();
};

#endif
citymap::citymap(int m,int n)
:m(m),n(n)
{
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
void citymap::map_out_T(ofstream *ofs)
{
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
      (*ofs)<<board[j][i]<<" ";
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
  for (int i = 0; i < m; i++)
  {
      for (int j = 0; j < n; j++)
      {
        sum+=board[i][j];
      }
  }
  return sum;
}
void citymap::put(int col,int x,int y)
{
    board[y][x]=col;
}
bool citymap::if_end(int x,int y)
{
  if(y>=m-1&&x>=n-1)
    return true;
  return false;
}
bool citymap::if_down(int x,int y)
{
  if(y>=m-1)
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
  {
    return false;
  }
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
int citymap::blue_less(int x,int y)
{
  int ans=0;
  if(x!=0&&board[y][x-1]!=BLUE)
    ans|=board[y][x-1];
  if(y!=0&&board[y-1][x]!=BLUE)
    ans|=board[y-1][x];
  if(x<n-1&&board[y][x+1]!=BLUE)
    ans|=board[y][x+1];
  if(y<m-1&&board[y+1][x]!=BLUE)
    ans|=board[y+1][x];
  return ans&3;//&0011
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
//check the last two row
{
  //printf("If success test:\n");
  //print_map();
  //cout<<"************\n";
  int s_row;
  if(n-2>0) s_row=n-2;
  else s_row=0;
  for (int j = s_row; j < n; j++)
  {
      for (int i = 0; i < m; i++)
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
bool citymap::if_up_is(int col,int x,int y)
{
  if(y>0)
  {
    if(board[y-1][x]==col)
      return true;
  }
  return false;
}
bool citymap::if_down_is(int col,int x,int y)
{
  if(y<m-1)
  {
    if(board[y+1][x]==col)
      return true;
  }
  return false;
}
bool citymap::if_this(int col,int x,int y)
{
  if(board[y][x]==col)
      return true;
    return false;
}

int dest_x=0;
int dest_y=0;
bool JUMP=false;
bool IF_RED=false;
bool go_next(int *x,int *y,citymap& map)
{
	if(map.if_end(*x,*y))
		return false;
	else if(map.if_down(*x,*y))
	{
		(*x)++;
		(*y)=0;
	}
	else
		(*y)++;
	return true;
}
bool if_stand(citymap & cur_map,int x,int y)
{
if(x>0)
	{
		int x0,y0;
		if(y>0)
		{
			x0=x-1;
			y0=y-1;
		}
		else if(x>1)
		{
			x0=x-2;
			y0=cur_map.m-1;
		}
		else
			return true;
		if(cur_map.if_this(GREEN,x0,y0)&&!cur_map.put_green(x0,y0))
			{
				//printf("green false x:%d y:%d\n",x0,y0);
				if(IF_RED)
				if(y0<cur_map.m-1)
				{
					dest_x=x0;
					dest_y=y0+1;
					JUMP=true;
				}

				return false;
			}
		if(cur_map.if_this(BLUE,x0,y0)&&!cur_map.put_blue(x0,y0))
			{
				if(IF_RED)
				if(y0<cur_map.m-1&&x0==0)
				{
					dest_x=x0;
					dest_y=y0+1;
					JUMP=true;
				}
				return false;
			}
	}
	return true;
}
double Avrage_pop(citymap & cur_map,int pre_pop,int x,int y)
{
	return (double)pre_pop/(x*cur_map.m+y);
}
int rest(citymap & cur_map,int x,int y)
{
	return cur_map.m*cur_map.n-(x*cur_map.m+y);
}
void Building(citymap &map,citymap & cur_map,int x,int y,int pre_pop)
{
	int Rest=rest(cur_map,x,y);
	if(Rest>=5&&pre_pop+Rest*2.3<map.caculate_pop())
		return;
	if(!if_stand(cur_map,x,y))
	{
		return;
	}	
	//possiblity cut
	//if the (x-1,y-1) cannot stand than abandon this way
	//next caculate the next point 
	int next_x=x;
	int next_y=y;
	bool if_next=go_next(&next_x,&next_y,cur_map);
	if((x>0)&&cur_map.if_left(GREEN,x,y)&&!cur_map.put_green(x-1,y))
	//if this place can only put red(often because the left one is green but no red besides)
	{
		cur_map.put(RED,x,y);
		IF_RED=true;
		if(if_next)
		{
			Building(map,cur_map,next_x,next_y,pre_pop+1);
			cur_map.put(EMPTY,x,y);
			if(JUMP)
				{
					if((x!=dest_x||y!=dest_y))
						return;
					else
						JUMP=false;
				}
		}
		else 
		//if this step is the end step of this case 
		//then caculate the population
		{
			if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
			{
				map=cur_map;
			}
				
			return;
		}
	}
	else
	{
		{
			cur_map.put(BLUE,x,y);

			IF_RED=false;
			if(if_next)
			{
			Building(map,cur_map,next_x,next_y,pre_pop+3);
			cur_map.put(EMPTY,x,y);
			if(JUMP)
				{
					if((x!=dest_x||y!=dest_y))
						return;
					else
						JUMP=false;
				}
			
			}
			else 
			//if this step is the end step of this case 
			//then caculate the population
			{
				//cout<<"Up to current:"<<cur_map.caculate_pop()<<"\n";
				if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
				{
					map=cur_map;
				}
			}
		}
		if(!(cur_map.if_left(GREEN,x,y)||cur_map.if_up_is(GREEN,x,y)))
		//there is no green besides green because blue can always replace it
		{
			cur_map.put(GREEN,x,y);
			IF_RED=false;
			if(if_next)
			{
				Building(map,cur_map,next_x,next_y,pre_pop+2);
				cur_map.put(EMPTY,x,y);
				if(JUMP)
				{
					if((x!=dest_x||y!=dest_y))
						return;
					else
						JUMP=false;
				}
				
			}
			else 
			//if this step is the end step of this case 
			//then caculate the population
			{
				//cout<<"Up to current:"<<cur_map.caculate_pop()<<"\n";
				if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
					{
						map=cur_map;
					}
			}
		}
		//then only can put red in it
		{
			cur_map.put(RED,x,y);
			IF_RED=true;
			if(if_next)
			{
				Building(map,cur_map,next_x,next_y,pre_pop+1);
				cur_map.put(EMPTY,x,y);
				if(JUMP)
				{
					//cout<<"JUMP";
					if((x!=dest_x||y!=dest_y))
						return;
					else
						JUMP=false;
				}
				
			}
			else 
			//if this step is the end step of this case 
			//then caculate the population
			{
				//cout<<"Up to current:"<<cur_map.caculate_pop()<<"\n";
				if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
				{
					map=cur_map;
				}
				return;
			}
		}
	}
}
int Build_city(citymap &map)
{
	JUMP=false;
	IF_RED=false;
	citymap cur_map(map);//copy the current map as the temp
	Building(map,cur_map,0,0,0);
	return map.caculate_pop();
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
			//cout<<"start testing"<<m<<","<<n<<endl;
			citymap map(m,n);
			ofs<<Build_city(map)<<"\n";
			map.map_out(&ofs);
			//testing(map);
		}
		else
		{
			//cout<<"start testing"<<m<<","<<n<<endl;
			citymap map(n,m);
			ofs<<Build_city(map)<<"\n";
			map.map_out_T(&ofs);
			//testing(map);
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
