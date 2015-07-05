#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "KQueens.h"
#include "Chessboard.h"
using namespace std;
/*
 * You should modify this function. Before you start, make
 * sure you have a clear idea of what you are doing.
 * Good Luck!
 */
/*struct pos
{
	pos(int x,int y);
	int x,y;
};*/
//pos::pos(x,y)
//:x(x),y(y){}
int min(int i1,int i2)
{
	if(i1<i2)
	return i1;
	return i2;	
}
void put(int rows,int cols,Chessboard *c)
{
	c->board[rows][cols]=Queen;
}
void clean(int rows,int cols,Chessboard *c)
{
	c->board[rows][cols]=Empty;
}
bool move_up(int rows,int cols,Chessboard *c)
{
	if(rows<c->rows-1&&cols<c->cols)
	{
		clean(rows,cols,c);
		put(rows+1,cols,c);
		return true;
	}
	return false;
}
bool move_right(int rows,int cols,Chessboard *c)
{
	if(cols<c->cols-1&&rows<c->rows)
	{
		clean(rows,cols,c);
		put(rows,cols+1,c);
		return true;
	}
	return false;
}
bool if_success(int rows,int cols,Chessboard *c)
{
	//cout<<"in_if_success rows:"<<rows<<" cols:"<<cols<<endl;
	for(int i=0;i<(c->rows);++i)
		if(c->board[i][cols]==Queen&&i!=rows)
			return false;

	for(int i=0;i<(c->cols);++i)
		if(c->board[rows][i]==Queen&&i!=cols)
			return false;
	int i=rows;
	int j=cols;
	//cout<<"in1\n";
	while(i<(c->rows)-1&&j<(c->cols)-1)
	{
		//cout<<"i:"<<i<<" j:"<<j<<endl;
		i++;j++;
		if(c->board[i][j]==Queen)
			return false;
	}
	//cout<<"in2\n";
	i=rows;
	j=cols;
	//cout<<"here!\n";
	while(i>0&&j>0)
	{
		i--;j--;
		if(c->board[i][j]==Queen)
			return false;
	}
	//cout<<"here!\n";
	i=rows;
	j=cols;
	//cout<<"in3\n";
	while(i>0&&j<c->cols-1)
	{
		i--;j++;
		if(c->board[i][j]==Queen)
			return false;
	}
	i=rows;
	j=cols;
	//cout<<"in4\n";
	while(i<c->rows-1&&j>0)
	{
		i++;j--;
		//cout<<"i:"<<i<<" j:"<<j<<endl;
		if(c->board[i][j]==Queen)
			return false;
	}
	//cout<<"out_if_success\n";
	return true;
}
bool Put_Q_in_rows(int line,Chessboard *c,int avoid)
{
	//cout<<"Start in\n";
	if(line==c->cols)
		return true;
	else if(line==avoid)
	{
		if(Put_Q_in_rows(line+1,c,avoid))
			return true;
		else
			return false;
	}
	int rows=0;
	int cols=line;//to put Q at the cols
	//cout<<"rest:"<<(c->cols-rest)<<endl;
	//cout<<"here!\n"<<"rows:"<<rows<<" cols:"<<cols<<"\n";
	put(rows,cols,c);
	//cout<<"after put\n";
	while(1)
	{
		if(!if_success(rows,cols,c))
		{
			if(move_up(rows,cols,c))
			{
				rows++;
				continue;
			}
			else
			{
				clean(rows,cols,c);
				return false;
			}
		}
		//cout<<"  	here!\n"<<" 	rows:"<<rows<<" cols:"<<cols<<"\n";
		//cout<<"  	print:\n";
		
		//c->print();
		if(Put_Q_in_rows(line+1,c,avoid))
			return true;
		else
		{
			if(move_up(rows,cols,c))
				rows++;
			else
			{
				clean(rows,cols,c);
				return false;
			}
		}
	}
	return false;
}
bool Put_Q_in_cols(int line,Chessboard *c,int avoid)
{
	//cout<<"Start in\n";

	if(line==c->rows)
		return true;
	else if(line==avoid)
	{
		if(Put_Q_in_cols(line+1,c,avoid))
			return true;
		else
			return false;
	}
	int cols =0;
	int rows=line;//to put Q at the cols
	//cout<<"rest:"<<(c->cols-rest)<<endl;
	//cout<<"here!\n"<<"rows:"<<rows<<" cols:"<<cols<<"\n";
	put(rows,cols,c);
	//cout<<"after put\n";
	while(1)
	{
		if(!if_success(rows,cols,c))
		{
			if(move_right(rows,cols,c))
			{
				cols++;
				continue;
			}
			else
			{
				clean(rows,cols,c);
				return false;
			}
		}
		//cout<<"  	here!\n"<<" 	rows:"<<rows<<" cols:"<<cols<<"\n";
		//cout<<"  	print:\n";
		
		//c->print();
		if(Put_Q_in_cols(line+1,c,avoid))
			return true;
		else
		{
			if(move_right(rows,cols,c))
				cols++;
			else
			{
				clean(rows,cols,c);
				return false;
			}
		}
	}
	return false;
}
int KQueens(Chessboard *c)
{
	//vector<pos>q_pos;
	//cout<<"Start"<<min(c->rows,c->cols)<<"\n";
	//for(int i=0;i<min(c->rows,c->cols);++i)
	if(c->cols<=c->rows)
	{
		//cout<<"rows\n";
		if(Put_Q_in_rows(0,c,c->cols+1))
			return c->cols;
		else
			for(int i=0;i<c->cols;++i)
				if(Put_Q_in_rows(0,c,i))
					return c->cols-1;
	}
	else
	{
		//cout<<"cols\n";
		if(Put_Q_in_cols(0,c,c->rows+1))
			return c->rows;
		else
			for(int i=0;i<c->rows;++i)
				if(Put_Q_in_cols(0,c,i))
					return c->rows-1;
	}
	return -1;
}
