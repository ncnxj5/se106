#include "Citymap.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

citymap::citymap(int m,int n)
:m(m),n(n)
{
  s_m=m/16+1;
  s_n=n;
  board = (int**)malloc(sizeof(int*) * s_m);
  if (NULL == board)
    {
      std::cout<<"Citymap memory allocation error.\n";
    }

  for (int i = 0; i < s_m; i++)
    {
      board[i] = (int*)malloc(sizeof(int) * n);
      if (NULL == board[i])
	{
	  std::cout<<"Citymap memory allocation error.\n";
	}
    }

  for (int i = 0; i < s_m; i++)
    {
      for (int j = 0; j < s_n; j++)
	{
	  board[i][j] = EMPTY;
	}
  }
}
citymap::~citymap()
{
  for (int i = 0; i < s_m; i++)
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
      (*ofs)<<get(j,i);;
    (*ofs)<<"\n";
  }
}
void citymap::map_out_T(ofstream *ofs)
{
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<m;j++)
      (*ofs)<<get(i,j);
    (*ofs)<<"\n";
  }
}
citymap::citymap(const citymap& map)
{
  m=map.m;
  n=map.n;
  s_m=m/16+1;
  s_n=n;
  board = (int**)malloc(sizeof(int*) * s_m);
  if (NULL == board)
    {
      std::cout<<"Citymap memory allocation error.\n";
    }

  for (int i = 0; i < s_m; i++)
    {
      board[i] = (int*)malloc(sizeof(int) * s_n);
      if (NULL == board[i])
  {
    std::cout<<"Citymap memory allocation error.\n";
  }
    }

  for (int i = 0; i < s_m; i++)
    {
      for (int j = 0; j < s_n; j++)
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
    s_m=m/16+1;
    s_n=n;
  board = (int**)malloc(sizeof(int*) * s_m);
  if (NULL == board)
    {
      std::cout<<"Citymap memory allocation error.\n";
    }

  for (int i = 0; i < s_m; i++)
    {
      board[i] = (int*)malloc(sizeof(int) * s_n);
      if (NULL == board[i])
  {
    std::cout<<"Citymap memory allocation error.\n";
  }
    }

  for (int i = 0; i < s_m; i++)
    {
      for (int j = 0; j < s_n; j++)
  {
    board[i][j] = map.board[i][j];
  }
    }
  }
}
int citymap::Get_no(int sou,int n)
{
  sou=sou>>(30-2*n);
  //int mask=3<<(30-n);
  return sou&3;
}
void citymap::Put_no(int *des,int sou,int n)
{
  int mask=3<<(30-2*n);
  (*des)=(*des)&(~mask);
  sou=sou<<(30-2*n);
  (*des)=(*des)|(sou&mask);
  return;
}
int citymap::caculate_pop()
{
  int sum=0;
  for (int i = 0; i < m; i++)
  {
      for (int j = 0; j < n; j++)
      {
        sum+=get(j,i);
      }
  }
  return sum;
}
int citymap::get(int x,int y)
{
  int i=y/16;
  int j=x;
  return Get_no(board[i][j],y%16);
}
void citymap::put(int col,int x,int y)
{
  int i=y/16;
  int j=x;
  Put_no(&board[i][j],col,y%16);
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
    if(get(x-1,y)==RED)
      return true;
  if(y!=0)
    if(get(x,y-1)==RED)
      return true;
  if(x<n-1)
    if(get(x+1,y)==RED)
      return true;
  if(y<m-1)
    if(get(x,y+1)==RED)
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
    if(get(x-1,y)==GREEN)
      return true;
  if(y!=0)
    if(get(x,y-1)==GREEN)
      return true;
  if(x<n-1)
    if(get(x+1,y)==GREEN)
      return true;
  if(y<m-1)
    if(get(x,y+1)==GREEN)
      return true;
  return false;
}
void citymap::init()
{
  for (int i = 0; i < m; i++)
  {
      for (int j = 0; j < n; j++)
      {
        put(EMPTY,j,i);
      }
  }
}
void citymap::print_map()
{
  for (int i = 0; i < m; i++)
  {
      for (int j = 0; j < n; j++)
      {
        cout<<get(j,i);//board[i][j];
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
        if(get(j,i)==GREEN)
          if(!put_green(j,i))
            return false;
            
        if(get(j,i)==BLUE)
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
    if(get(x-1,y)==col)
      return true;
  }
  return false;
}
bool citymap::if_up_is(int col,int x,int y)
{
  if(y>0)
  {
    if(get(x,y-1)==col)
      return true;
  }
  return false;
}
bool citymap::if_down_is(int col,int x,int y)
{
  if(y<m-1)
  {
    if(get(x,y+1)==col)
      return true;
  }
  return false;
}
bool citymap::if_this(int col,int x,int y)
{
  if(get(x,y)==col)
      return true;
    return false;
}