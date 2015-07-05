#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

class Hash
{
public:
	Hash(string s);
	string get_result();
	char hash_table[255][2];
	int hash(char c);
	string str;
	//void print();
};
Hash::Hash(string s)
:str(s)
{
	//cout<<str<<endl;
	for(int i=0;i<255;i++)
		hash_table[i][1]='E';
	//print();
	for(int i=0;i<s.size();i++)
	{
		int hash_num=hash(s[i]);
		//compute the hash number
		if(hash_table[hash_num][1]=='E')
		{
			hash_table[hash_num][0]=s[i];
			//put char into hash table
			hash_table[hash_num][1]='O';
			//put the sign to 'O' as one time
		}
		else if(hash_table[hash_num][1]=='O')
		{
			hash_table[hash_num][1]='T';
			//sign the signial to 'T' as two
		}
	}
	//print();
}
int Hash::hash(char c)
{
	return (int)c;
}
string Hash::get_result()
{
	for(int i=0;i<str.size();i++)
	{
		string result=" ";
		int hash_num=hash(str[i]);
		//compute the hash number
		if(hash_table[hash_num][1]=='O')
		{
			result[0]=hash_table[hash_num][0];
			return result;
		}
	}
	return "None";
}
int main(int argc, char const *argv[])
{
	ifstream ifs;
	ifs.open("hash.in");
	ofstream ofs;
	ofs.open("hash.out");
	int num;
	string temp;
	getline(ifs,temp);
	stringstream ss(temp);
	ss>>num;
	//get how many test case there are
	for(int i=0;i<num;i++)
	 {
		getline(ifs,temp);
		Hash hash(temp);
		ofs<<hash.get_result()<<endl;
	 }

	return 0;
}