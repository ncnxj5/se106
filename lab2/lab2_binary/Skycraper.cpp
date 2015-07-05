#include "Skycraper.h"
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
				return false;
			}
		if(cur_map.if_this(BLUE,x0,y0)&&!cur_map.put_blue(x0,y0))
			{
					//printf("blue false x:%d y:%d\n",x0,y0);
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
		if(if_next)
		{
			Building(map,cur_map,next_x,next_y,pre_pop+1);
			cur_map.put(EMPTY,x,y);
		}
		else 
		//if this step is the end step of this case 
		//then caculate the population
		{
			//cout<<"Up to current:"<<cur_map.caculate_pop()<<"\n";
			if(cur_map.if_success()&&(map.caculate_pop()<cur_map.caculate_pop()))
			{
				map=cur_map;
				//cout<<"Update!\n"<<map.caculate_pop()<<endl;
			}
				
			return;
		}
	}
	else
	{
		{
			cur_map.put(BLUE,x,y);
			if(if_next)
			{
			Building(map,cur_map,next_x,next_y,pre_pop+3);
			cur_map.put(EMPTY,x,y);
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
			//printf("PUT green1\n");
			cur_map.put(GREEN,x,y);
			if(if_next)
			{
				Building(map,cur_map,next_x,next_y,pre_pop+2);
				cur_map.put(EMPTY,x,y);
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
			if(if_next)
			{
				Building(map,cur_map,next_x,next_y,pre_pop+1);
				cur_map.put(EMPTY,x,y);
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
	citymap cur_map(map);//copy the current map as the temp
	Building(map,cur_map,0,0,0);
	return map.caculate_pop();
}