// complete this file for your homework7
//ID  : NCNXJ5
//name: RAINUE
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define ID 0
#define NUM 1
#define COM 2
/**************************************************************/
//Tokenscanner class writen
class Tokenscanner
{
public:
	Tokenscanner(string str);
	int num;
	string str;
	char nextToken();
	string nextString();
	void put_back(string s);
};
Tokenscanner::Tokenscanner(string str)
:str(str),num(0)
{}
char Tokenscanner::nextToken()
//the func to get next char
{
	if(num<str.size())
	{
		num++;
		return str[num-1]; 	
	}
	else
		return ' ';
}
string Tokenscanner::nextString()
//the func to get next char
{
	//cout<<"get next string string: "<<str<<" num: "<<num;
	string temp=" ";
	string token="";
	char tmp;
	while(num<str.size()&&str[num]==' ')
		num++;
	while(num<str.size()&&str[num]!=' ')
	{
		temp[0]=str[num];
		token+=temp;
		num++;
	}
	return token;
}
void Tokenscanner::put_back(string s)
// the func to put back string
{
	num-=s.size();
}

/**************************************************************/
class Expression
//expression class
{
public:
	Expression(){};
	virtual int key()=0;
	string value;
	Expression* exp;
	Expression* rhs;
};
class IdentifierExp : public Expression
{
public:
	IdentifierExp(string s);
	int key(){return ID;}
	
};
IdentifierExp::IdentifierExp(string s)
{value =s;}
class ConstantExp : public Expression
{
public:
	ConstantExp(string s);
	int key(){return NUM;}
};
ConstantExp::ConstantExp(string s)
{value =s;}
class CompoundExp : public Expression
{
public:
	CompoundExp(string s,Expression* exp,Expression* rhs);
	int key(){return COM;}
};
CompoundExp::CompoundExp(string s,Expression* e,Expression* r)
{value =s; exp=e; rhs=r;}
/**************************************************************/
bool IF_NUM(string str)
{
	bool res=true;
	for(int i=0;i<str.size();i++)
		if(str[i]<48||str[i]>57)
			res=false;
	return res;
}
bool IF_WORD(string str)
{
	bool res=true;
	for(int i=0;i<str.size();i++)
		if(str[i]=='('||str[i]==')')
			res=false;
	return res;
}
int precedence(string token) {
   if (token == "=") return 1;
   if (token == "+" || token == "-") return 2;
   if (token == "*" || token == "/") return 3;
   return 0;
}
Expression* readE(Tokenscanner * scanner, int prec);
Expression* readT(Tokenscanner * scanner) 
{
   //cout<<"In readT\n";
   string token = scanner->nextString();
   //cout<<"In readT get token : "<<token<<"\n"; 
   if (IF_NUM (token))	return new ConstantExp(token);
   if (IF_WORD(token))  return new IdentifierExp(token);
   if (token != "(") cout<<"Illegal term in expression\n";
   Expression *exp = readE(scanner,0);
   if (scanner->nextString() != ")") {
      cout<<"Unbalanced parentheses in expression\n";
   }
   return exp;
}
Expression* readE(Tokenscanner * scanner, int prec) 
{
	//cout<<"in readE\n";
   Expression *exp = readT(scanner);
   string token;
   while (true) {
      token = scanner->nextString();
      //cout<<"In readE get token : "<<token<<"\n"; 
      int newPrec = precedence(token);
      if (newPrec <= prec) break;
      Expression *rhs = readE(scanner, newPrec);
      exp = new CompoundExp(token, exp, rhs);
   }
   scanner->put_back(token);
   return exp;
}
/**************************************************************/
void Print_result(Expression* print)
{
	if(print->key()==NUM||print->key()==ID)
		cout<<print->value<<" ";
	else if(print->key()==COM)
	{
		Print_result(print->exp);
		Print_result(print->rhs);
		cout<<print->value<<" ";
	}
	return;
}
int main()
{
	string expr;
	getline(cin,expr);
	while(expr!="quit")
		//look if the input is quit
	{
		//cout<<"Get value:\n";
		Tokenscanner scanner(expr);
		//readE(&scanner, 0);
		//cout<<"Start creating\n";
		Expression* exp=readE(&scanner,0);
		//cout<<"Printing result\n";
		Print_result(exp);
		cout<<endl;
		getline(cin,expr);
	}
	return 0;
}
