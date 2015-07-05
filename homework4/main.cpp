#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Chessboard.h"
#include "KQueens.h"
using namespace std;
int main()
{
while(1)
{
	int rols,cols;
	cout<<"Plase input rows and the cols:";
	cin>>rols>>cols;
  Chessboard che(rols,cols);
	cout<<"We can put "<<KQueens(&che)<<" Queens on the Chessboard.\n";
	for(int i=0;i<che.rows;i++)
	{
		for(int j=0;j<che.cols;j++)
		cout<<che.board[i][j]<<" ";
		cout<<endl;
	}
}
  return 0;
}
