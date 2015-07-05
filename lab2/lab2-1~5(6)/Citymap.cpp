#include "Citymap.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

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
      (*ofs)<<board[i][j];
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