/*
name:RAINUE
ID: NCNXJ5
*/
#include "Mergesort.h"
#include <cstdlib>

void print(vector<int> &vec)
{
	for(int i=0;i<vec.size();i++)
		cout<<vec[i]<<" ";
	cout<<"\n";
}
void random(vector<int> &vec,int num)
{
	vec.clear();
	srand( (unsigned)time(NULL)); //生成种子
	for(int i=0;i<num;i++)
		vec.push_back(rand()%100);
}
void test_classic()//test the CLASSIC VERSION
{
	cout<<"Start testing Classic Merge sort...\n";
	vector<int>test;
	int num;
	cout<<"Give the size of the array:";
	cin>>num;
	random(test,num);
	cout<<"Before sort:";
	print(test);
	Classic_merge_sort(test);
	cout<<"After sort:";
	print(test);
	cout<<"\n";
}
void test_in_place()//test the IN PLACE VERSION
{
	cout<<"Start testing In-place Merge sort...\n";
	vector<int>test;
	int num;
	cout<<"Give the size of the array:";
	cin>>num;
	random(test,num);
	cout<<"Before sort:";
	print(test);
	In_place_merge_sort(test);
	cout<<"After sort:";
	print(test);
	cout<<"\n";
}
int main()
{
	while(1)
	{
	test_classic();
	test_in_place();
	}
	return 0;
}
