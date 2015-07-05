#include "Skycraper.h"
int temp_pop=0;
bool if_max=false;
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
void Building(citymap &map,citymap & cur_map,int x,int y,int pop)
{
	char temp;
	
	
	if(if_max)
		return;
	int next_x=x;
	int next_y=y;
	bool if_next=go_next(&next_x,&next_y,cur_map);
	{
		cur_map.put(BLUE,x,y);
		
		if(if_next)
		{
			Building(map,cur_map,next_x,next_y,pop+BLUE);
		}
		else 
		//if this step is the end step of this case 
		//then caculate the population
		{
			if(Build_rest(map,cur_map))
			{
				
				cout<<"***finded!*****\n";
				cout<<"pop:"<<pop<<" temp_pop:"<<temp_pop<<"\n";
				cur_map.print_map();
				int popu=map.caculate_pop();
				cout<<"population:"<<popu<<endl;
				temp_pop=popu;
				cin>>temp;
			}
		}
	}
	//if(cur_map.put_green(x,y))//look if this pos can put green in
	{
		cur_map.put(GREEN,x,y);
		if(if_next)
		{
			Building(map,cur_map,next_x,next_y,pop+GREEN);
		}
		else 
		//if this step is the end step of this case 
		//then caculate the population
		{
			if(Build_rest(map,cur_map))
			{
				cout<<"***finded!*****\n";
				cout<<"pop:"<<pop<<" temp_pop:"<<temp_pop<<"\n";
				cur_map.print_map();
				int popu=map.caculate_pop();
				cout<<"population:"<<popu<<endl;
				temp_pop=popu;
				cin>>temp;
			}
		}
	}
	//then only can put red in it
	{
		cur_map.put(RED,x,y);
		if(if_next)
		{
			Building(map,cur_map,next_x,next_y,pop+RED);
			//cur_map.put(EMPTY,next_x,next_y);//clean the prev ground
		}
		else 
		//if this step is the end step of this case 
		//then caculate the population
		{
			if(Build_rest(map,cur_map))
			{
				//temp_pop=pop;
				cout<<"***finded!*****\n";
				cout<<"pop:"<<pop<<" temp_pop:"<<temp_pop<<"\n";
				cur_map.print_map();
				//Empty_rest(cur_map);
				int popu=map.caculate_pop();
				cout<<"population:"<<popu<<endl;
				temp_pop=popu;
				cin>>temp;
			}
			return;
		}
	}
}
int Build_city(citymap &map)
{
	//cout<<"computing\n";
	citymap cur_map(map);//copy the current map as the temp
	Building(map,cur_map,0,0,0);
	//cout<<"finished!\n";
	
	//cout<<"pop: "<<pop<<"\n";
	return map.caculate_pop();
}