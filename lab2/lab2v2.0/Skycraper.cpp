#include "Skycraper.h"
double AVECUT=2;
int dest_x=0;
int dest_y=0;
bool JUMP=false;
bool IF_RED=false;
int min(int x1,int x2)
{
	if(x1<x2)
		return x1;
	return x2;
}
int max(int x1,int x2)
{
	if(x1>x2)
		return x1;
	return x2;
}
void SETAVE(citymap& map)
{
	int key=min(map.m,map.n);
	if(key==5) AVECUT=2.05;
	else if(key==6) AVECUT=2.14;
	else if(key==7) AVECUT=2.1;
	else if(key==8) AVECUT=2.16;
	else if(key==9) AVECUT=2.15;
	else AVECUT=2;
	return;
}
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
	return (double)pre_pop/(x*cur_map.m+y);
}
int rest(citymap & cur_map,int x,int y)
{
	return cur_map.m*cur_map.n-(x*cur_map.m+y);
}
void Building(citymap &map,citymap & cur_map,int x,int y,int pre_pop)
{
	//char temp;
	//cur_map.print_map();
	
	//cout<<"rest:"<<rest(cur_map,x,y)<<"  pre_pop:"<<pre_pop<<endl;
	//std::cout<<"-----------\n";
	//cout<<"Up to now max:"<<map.caculate_pop()<<"\n";
	//cin>>temp;
	int Rest=rest(cur_map,x,y);
	if(Rest>=5&&pre_pop+Rest*2.3<map.caculate_pop())
		return;
	/*if(cur_map.m>1&&(x>0)&&(x<cur_map.n-1)&&Avrage_pop(cur_map,pre_pop,x,y)<AVECUT)//Average cut
	{
		//printf("Average cut\n");
		return;
	}*/
		
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
			/*if(JUMP)
			{
				if((x!=dest_x||y!=dest_y))
					return;
				else
					JUMP=false;
			}*/
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
			IF_RED=false;
			if(if_next)
			{
			Building(map,cur_map,next_x,next_y,pre_pop+3);
			cur_map.put(EMPTY,x,y);
			/*if(JUMP)
			{
				if((x!=dest_x||y!=dest_y))
					return;
				else
					JUMP=false;
			}*/
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
				/*if(JUMP)
				{
					if((x!=dest_x||y!=dest_y))
						return;
					else
						JUMP=false;
				}*/
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
				/*if(JUMP)
				{
					if((x!=dest_x||y!=dest_y))
						return;
					else
						JUMP=false;
				}*/
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
	}
}
int Build_city(citymap &map)
{
	JUMP=false;
	IF_RED=false;
	SETAVE(map);
	citymap cur_map(map);//copy the current map as the temp
	Building(map,cur_map,0,0,0);
	return map.caculate_pop();
}