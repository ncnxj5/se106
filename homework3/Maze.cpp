/*
 * [TODO] delte this comment
 * Our test compiler is g++,
 * you can use '$ g++ -v' to see version, suggest 4.8 or newest,
 * add any header file you need from standard C++ library
 * and create any class or function you need to use
 */
//NCNXJ5
//RAINUE
/*
 * Use standard I/O to read test file and output answer.
 * There are three test file: testmap_1.txt, testmap_2.txt, testmap_3.txt,
 * and your output should like:
 * testmap_1: (1,1) (1,2) (1,3) (2,3) ...
 * More detail on course websit
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
enum Direction {NORTH, EAST, SOUTH, WEST, NONE};
void add_direction (Direction* dir)//to add on Direction
{
	if(*dir==NORTH)
		*dir= EAST;
	else if(*dir==EAST)
		*dir= SOUTH;
	else if(*dir==SOUTH)
		*dir= WEST;
	else if(*dir==WEST)
		*dir= NONE;
}

struct point//the struct of point
{
	point(int x,int y):x(x),y(y){ };
	int x;
	int y;
	void print() {cout<<" ("<<x<<","<<y<<")";};
};

class Maze// the class for slove the problem
{
public:
	Maze(ifstream *map_in) :map_in(map_in) 
	{
		for(int i=0;i<64;++i)
			for(int j=0;j<64;++j)
				map[i][j]='0';
	};
	void read_map()
	{
		//(*map_in)>>x>>y;//read length and wedth to the map
		string temp;
		getline(*map_in,temp);
		stringstream ss;
		ss<<temp;
		ss>>x>>y;
	//	cout<<"x:"<<x<<" y:"<<y<<endl;
	//if(!(*map_in)>>x>>y)//read the x and y from map
		//return;
	//else
	{
		//cout<<endl<<"begin:\n";
		//cout<<"x:"<<x<<" y:"<<y<<endl;
		string line;
		for(int i=0;i<y;++i)
		{
			line="null";
			while(line=="null")//get line
			getline(*map_in,line);
			//cout<<"line :"<<line<<endl;
			for(int j=0;j<line.size();++j)
			{
				if(line[j]=='S')
				{
					s_x=j;
					s_y=i;//set start x,start y
				}
				else if(line[j]=='E')
				{
					d_x=j;
					d_y=i;
				}
				else if(line[j]!=' ')
				{
					map[j][i]='1';
				}

			}
				//map[j][i]=line[j];
		}
		/*for(int i=0;i<y;++i)
		{
			for(int j=0;j<x;++j)
				cout<<map[j][i];
			cout<<"\n";
		}*/
	}
	return;
	}
	bool is_Outside(point p)
	{
		if(p.x==d_x&&p.y==d_y)
			return true;
		return false;
	}
	bool is_Marked(point p)
	{
		for(int i=0;i<path.size();++i)
		if(p.x==path[i].x&&p.y==path[i].y)
			return true;
		return false;
	}
	point start_point()
	{
		return point(s_x,s_y);
	}
	point next_point(point start, Direction dir)
	{
		point next(start.x,start.y);
		if(dir==NORTH&&next.y>0)
			next.y--;
		else if(dir==EAST&&next.x>0)
			next.x--;
		else if(dir==SOUTH&&next.y<y)
			next.y++;
		else if(dir==WEST&&next.x<x)
			next.x++;
		return next;
	}
	bool wallExists(point start, Direction dir)
	{
		point temp=next_point(start, dir);
		if(map[temp.x][temp.y]=='1')
		{
			//cout<<"x:"<<temp.x<<" y:"<<temp.y<<"\n";
			return true;
		}
		return false;
	}
	void markSquare(point po)
	{
		path.push_back(po);
	}
	void unmarkSquare(point po)
	{
		//path.pop_back();
		for(int i=0;i<path.size();++i)
		{
			if(path[i].x==po.x&&path[i].y==po.y)
			{
				path.erase(path.begin()+i);
				//cout<<"successfully erased\n";
				//print();
				//cout<<"\n";
			}
		}
	}
	void print()
	{
		for(int i=1;i<path.size();++i)
		{
			(path)[i].print();
		}
		point(d_x,d_y).print();
		return;
	}
private:
	char map[64][64];
	vector<point> path;
	int x;
	int y;
	int s_x;
	int s_y;
	int d_x;
	int d_y;
	ifstream *map_in;
};
bool solveMaze(Maze & maze, point start)//the function to find the path
{
   	if (maze.is_Outside(start)) return true;
   	if (maze.is_Marked(start)) return false;
   		maze.markSquare(start);
   		for (Direction dir = NORTH; dir <= WEST; add_direction(&dir)) 
   		{
      		if (!maze.wallExists(start, dir)) 
      		{
         		if (solveMaze(maze, maze.next_point(start, dir))) 
         		{
            		return true;
         		}
      		}
   		}
   maze.unmarkSquare(start);
   return false;
}
void find_path(ifstream *map_in)
{
	Maze maze(map_in);
	maze.read_map();
	if(solveMaze(maze, maze.start_point()))
		maze.print();
	//char map[64][64];
	//read_map(map_in,&map);
}
int main()
{
	ifstream map_1("testmap_1.txt");
	ifstream map_2("testmap_2.txt");
	ifstream map_3("testmap_3.txt");
	if(map_1&&map_2&&map_3)//if all of the test part have been successfully open
	{
		cout<<"testmap_1: ";
		//vector<point>path1;
		find_path(&map_1);
		//print(&path1);
		cout<<"\ntestmap_2: ";
		//vector<point>path2;
		find_path(&map_2);
		//print(&path2);
		cout<<"\ntestmap_3: ";
		//vector<point>path3;
		find_path(&map_3);
		//print(&path3);
		cout<<"\n";
	}
	else
		cout<<"ERROR Can't open some of the files!\n";
	//cout << 123 << endl;
	return 0;
}
