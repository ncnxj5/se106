/*
Name: ncnxj5
I  D: rainue
*/
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct H_Tree_node
//the struct for tree node
{
  H_Tree_node(char ch,int t):parent(NULL),left(NULL),right(NULL),ch(ch),time(t),bin(-1) {}
  H_Tree_node(H_Tree_node*left,H_Tree_node*right,int t)
  :parent(NULL),left(left),right(right),time(t),ch(0),bin(-1){}
  H_Tree_node*left;
  H_Tree_node*right;
  H_Tree_node*parent;
  char ch;
  char bin;
  int time;
};
int cmp(const H_Tree_node *x,const H_Tree_node *y )
{
  return x->time > y->time;
}
class H_Tree
// the class that mainly used for free the memory of the tree
{
public:
  H_Tree() :head(NULL){};
  H_Tree_node *head;
  void free_tree(H_Tree_node* h)
  {
    if(h->left!=NULL)
      free_tree(h->left);
    if(h->right!=NULL)
      free_tree(h->right);
    h->~H_Tree_node();
  }
  ~H_Tree()
  {
    if(head!=NULL)
    free_tree(head);
  }
};


typedef pair<char,string> PAIR;
vector<PAIR> table;
string chartable="";
string file="";
//the file is used as a buffer for write 
H_Tree h_tree;

string find(char c)
// find string in table using char
{
  for(int i=0;i<table.size();i++)
    if(table[i].first==c)
      return table[i].second;
  return "";
}
bool if_find(string s)
// tell that if there is string in table
{
  for(int i=0;i<table.size();i++)
    if(table[i].second==s)
      return true;
  return false;
}
char find(string s)
// find char in table using string
{
  for(int i=0;i<table.size();i++)
    if(table[i].second==s)
      return table[i].first;
  return -1;
}
void naiveCopy(string inputFilename, string outputFilename) {
  ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
  ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  char c;
  while (ifs.get(c)) {cout<<c<<1<<endl;ofs.put(c);}
  ofs.close();
  ifs.close();
}
bool if_find(char ch)
{
  for(int i=0;i<chartable.size();i++)
    if(chartable[i]==ch)
      return true;
  return false;
}
char str2bin(string str)
//change from string(8) to one char
{
  char result=0;
  int i=0;
  for(i=0;i<str.size();i++)
  {
    char temp=str[i]<<i;
    result=result|temp;
  }
    return result;
}
string bin2str(char bin)
//change from one char to string(8)
{
  string result="";
  string temp=" ";
  char mask=1;
  for(int i=0;i<8;i++)
  {
    temp[0]=((bin&mask)>>i)&1;
    mask=mask<<1;
    //cout<<"bin "<<(int)temp[0]<<endl;
    result+=temp;
  }
  return result;
}
void compress(string inputFilename, string outputFilename) 
{
  //naiveCopy(inputFilename, outputFilename); return;
  ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
  ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  ifstream ifs0(inputFilename.c_str(), ios::in | ios::binary);
  //constructure the ifs ofs
  map<char,int> STORE;
  vector<H_Tree_node*> STORE_vec;
  vector<H_Tree_node*> all_vec;
  char c;
  //cout<<"here!\n";
  int ite=0;
  while (ifs.get(c))
  //first scan the file 
  {
    ite++;
    if(if_find(c))
    { STORE[c]++; }
    else
    {
      STORE[c]=1;
      //put it into the map
      string tstr=" ";
      tstr[0]=c;
      chartable+=tstr;
    }
  }
  if(ite==0)
    return;//if the file is empty then return just
  //construct a vector to sort
  for(map<char,int>::iterator map_i=STORE.begin();map_i!=STORE.end();map_i++)
  {
    STORE_vec.push_back(new H_Tree_node(map_i->first,map_i->second));
    //cout<<map_i->first<<" "<<map_i->second<<endl;
  }
  sort(STORE_vec.begin(),STORE_vec.end(),cmp);
  all_vec=STORE_vec;

  while(STORE_vec.size()>1)
    //construct the h tree
  {
    H_Tree_node* left= STORE_vec[STORE_vec.size()-2];
    H_Tree_node* right= STORE_vec[STORE_vec.size()-1];
    H_Tree_node* newnode =new H_Tree_node(left,right,left->time+right->time);
    STORE_vec.pop_back();STORE_vec.pop_back();//pop the least one from heap
    left->bin=1;
    right->bin=0;
    left->parent=newnode;
    right->parent=newnode;
    STORE_vec.push_back(newnode);
    sort(STORE_vec.begin(),STORE_vec.end(),cmp);
  }
  //create table
  h_tree.head=STORE_vec[0];
  for(int i=0;i<all_vec.size();i++)
  {
    string temp="";
    string cha=" ";
    char c=all_vec[i]->ch; 
    H_Tree_node *curr=all_vec[i];
    while(curr->parent!=NULL)
    {
      if(curr->bin!=-1)
        cha[0]=curr->bin;
      temp=cha+temp;
      curr=curr->parent;
    }
    table.push_back(make_pair(c,temp));
  }
  //the part of writing the head table into the file
  int num=table.size();
  //first write that there are how many items in table
  ofs<<(char)num;
  ofs<<(char)(num>>8);
  ofs<<(char)(num>>16);
  ofs<<(char)(num>>24);
  //then write the length of char in the file
  ofs<<(char)ite;
  ofs<<(char)(ite>>8);
  ofs<<(char)(ite>>16);
  ofs<<(char)(ite>>24);
  for(int i=0;i<table.size();i++)
  {
    ofs<<table[i].first;
    ofs<<table[i].second;
    ofs<<(char)0xff;
    //end with an 0xff to end
  }

  while (ifs0.get(c)) 
  {
    file+=find(c);
    //constructure the file to write out
  }

//Then write into the file
  int i;
  for(i=0;i<file.size();i+=8)
  {
    string temp="";
    string cha=" ";
    for(int j=0;j<8;j++)
    {
      cha[0]=file[i+j];
      temp+=cha;
    }
    
    ofs.put(str2bin(temp));
  }
  if(i<file.size())
  {
    string temp="";
    for(i;i<file.size();i++)
    {
      string cha=" ";
      cha[0]=file[i];
      temp+=cha;
    }
    ofs.put(str2bin(temp));
  }
  ofs.close();
  ifs.close();
  ifs0.close();
  return;
};

void decompress(string inputFilename, string outputFilename) 
{
  ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
  ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  int num=0;
  int length=0;
  char c;
  for(int i=0;i<4;i++)
  {
    if(ifs.get(c))
    num|=(((int)((int)c)&(0xff))<<(8*i));
    else
      return;//if the file was empty then just return
  }
  for(int i=0;i<4;i++)
  {
    ifs.get(c);
    length|=(((int)((int)c)&(0xff))<<(8*i));
  }
  //cout<<"length:"<<length<<endl;
  //read the length of the file
  for(int i=0;i<num;i++)
  {
    ifs.get(c);
    char key=c;
    string value="";
    string strtemp=" ";
    while(1)
    {
      ifs.get(c);
      if(c==-1)
        break;
      strtemp[0]=c;
      value+=strtemp;
    }
    /*cout<<(int)key<<endl;
    for(int j=0;j<value.size();j++)
    {
      cout<<(int)value[j]<<" ";
    }
    cout<<endl;*/
  table.push_back(make_pair(key,value));
  //reconstruct the table
  }
  while(ifs.get(c))
  {
    file+=bin2str(c);
  }
  int l=0;
  //reconstruct the file
  //rewrite the file
  for(int i=0;i<file.size();i++)
  {
    string str="";
    str+=file[i];
    while(!if_find(str)&&i<file.size())
    {
      i++;
      str+=file[i];
    }
    if(l<length)
    {
      ofs<<find(str);
      l++;
    }
  }
  //cout<<num<<endl;
  ofs.close();
  ifs.close();
}

void useage(string prog) {
  cerr << "Useage: " << endl
      << "    " << prog << "[-d] input_file output_file" << endl;
  exit(2);
}

int main(int argc, char* argv[]) {
  
  int i;
  string inputFilename, outputFilename;
  bool isDecompress = false;
  for (i = 1; i < argc; i++) {
    if (argv[i] == string("-d")) isDecompress = true;
    else if (inputFilename == "") inputFilename = argv[i];
    else if (outputFilename == "") outputFilename = argv[i];
    else useage(argv[0]);
  }
  if (outputFilename == "") useage(argv[0]);
  if (isDecompress) {decompress(inputFilename, outputFilename);}
  else compress(inputFilename, outputFilename);
  return 0;
}
