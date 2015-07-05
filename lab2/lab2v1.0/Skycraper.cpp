#include "Skycraper.h"
#define AVECUT 2
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
				if(y0<cur_map.m-2&&IF_RED)
				{
					dest_x=x0;
					dest_y=y0+1;
					JUMP=true;
					//printf("Jump begin\n");
				}
				return false;
			}
		if(cur_map.if_this(BLUE,x0,y0)&&!cur_map.put_blue(x0,y0))
			{
					//printf("blue false x:%d y:%d\n",x0,y0);
				
				if(y0<cur_map.m-2&&IF_RED)
				{
					dest_x=x0;
					dest_y=y0+1;
					JUMP=true;
					//printf("Jump begin\n");
				}
				return false;
			}
	}
	return true;
}
double Avrage_pop(citymap & cur_map,int pre_pop,int x,int y)
{
	return (double)pre_pop/(x*cur_map.m+y-1);
}
void Building(citymap &map,citymap & cur_map,int x,int y,int pre_pop)
{
	//char temp;
	//cur_map.print_map();
	//std::cout<<"-----------\n";
	//cin>>temp;
	
	if((x>0)&&Avrage_pop(cur_map,pre_pop,x,y)<AVECUT)//Average cut
	{
		//printf("Average cut\n");
		return;
	}
		
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
		//printf("PUT red1\n");
		cur_map.put(RED,x,y);
		IF_RED=true;
		if(if_next)
		{
			Building(map,cur_map,next_x,next_y,pre_pop+1);
			if(JUMP)
			{
				if((x!=dest_x||y!=dest_y))
				{
					//printf("Jump up to x:%d y:%d\n",dest_x,dest_y);
					return;
				}
				else
				{
					//printf("Jump done\n");
					JUMP=false;
				}
			}
			cur_map.put(EMPTY,x,y);
		}
		else 
		//if this step is the end step of this case 
		//then caculate the population
		{
			if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
				map=cur_map;
			return;
		}
	}
	else
	{
		{
			//printf("PUT blue1\n");
			cur_map.put(BLUE,x,y);
			IF_RED=false;
			if(if_next)
			{
			Building(map,cur_map,next_x,next_y,pre_pop+3);
			cur_map.put(EMPTY,x,y);
			if(JUMP)
			{
				if((x!=dest_x||y!=dest_y))
				{
					//printf("Jump up to x:%d y:%d\n",dest_x,dest_y);
					return;
				}
				else
				{
					//printf("Jump done\n");
					JUMP=false;
				}
			}
			}
			else 
			//if this step is the end step of this case 
			//then caculate the population
			{
				if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
					map=cur_map;
			}
		}
		if(!(cur_map.if_left(GREEN,x,y)||cur_map.if_up_is(GREEN,x,y)))
		//there is no green besides green because blue can always replace it
		{
			//printf("PUT green1\n");
			cur_map.put(GREEN,x,y);
			IF_RED=false;
			if(if_next)
			{
				Building(map,cur_map,next_x,next_y,pre_pop+2);
				cur_map.put(EMPTY,x,y);
				if(JUMP)
				{
					if((x!=dest_x||y!=dest_y))
					{
						//printf("Jump up to x:%d y:%d\n",dest_x,dest_y);
						return;
					}
					else
					{
						//printf("Jump done\n");
						JUMP=false;
					}
				}
			}
			else 
			//if this step is the end step of this case 
			//then caculate the population
			{
				if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
					map=cur_map;
			}
		}
		//then only can put red in it
		{
			//printf("PUT red2\n");
			cur_map.put(RED,x,y);
			IF_RED=true;
			if(if_next)
			{
				Building(map,cur_map,next_x,next_y,pre_pop+1);
				cur_map.put(EMPTY,x,y);
				if(JUMP)
				{
					if((x!=dest_x||y!=dest_y))
					{
						//printf("Jump up to x:%d y:%d\n",dest_x,dest_y);
						return;
					}
					else
					{
						//printf("Jump done\n");
						JUMP=false;
					}
				}
			}
			else 
			//if this step is the end step of this case 
			//then caculate the population
			{
				if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
					map=cur_map;
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