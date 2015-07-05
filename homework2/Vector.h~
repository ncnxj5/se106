/**
* Homework 2: Using Template
* Assigned: September 13
* Due: September 23 24:00
**/

// [TODO]
// Student ID: 5130379068
// Name: 陈悦昕 Chenyuexin
//

#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <string>
#include <stdexcept>

#include <iostream>

using namespace std;

template <typename T>
class Vector {
private:
	// [TODO] Add private variables and methods here
	size_t _size;
	T* _storage;
	void copy(int n,T* sourse,T* dest);
	bool if_greater(string s1,string s2);
public:
	// Do NOT modify following interfaces
	Vector();
	Vector(int size, const T& val = T());
	Vector(const Vector& x);
	~Vector();
	Vector<T>& operator=(const Vector<T>& x);
	int size() const;
	bool empty() const;
	T& operator [](int pos);
	void resize(size_t n, T val = T());
	void push_back(const T& val);
	void sort();
};

// (default constructor)
// Constructs an empty container, with no elements.
template <typename T>
Vector<T>::Vector() 
	:_size(0), _storage(NULL)
{
	// [TODO]
}

// (fill constructor)
// Constructs a container with n elements.
// Each element is a copy of val.
template <typename T>
Vector<T>::Vector(int size, const T& val) 
{
	_size=0;
	_storage=NULL;
	for(int i=0;i<size;++i)
	push_back(val);
	// [TODO]
}

// (copy constructor)
// Constructs a container with a copy of each of the
// elements in x, in the same order.
template <typename T>
Vector<T>::Vector(const Vector& x) 
	:_size(x._size)
{
	// [TODO]
	//_size=x.
	if(x._storage)
	{
	_storage=new T[x._size];
	copy(x._size,x._storage,_storage);
	}
}

// (destructor)
// Destroys the container object.
template <typename T>
Vector<T>::~Vector() {
	// [TODO]
	if(_storage)
	delete[] _storage;
}

// operator=
// Assigns new contents to the container, replacing its
// current contents, and modifying its size accordingly.
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& x) {
	// [TODO]
	//Vector<T>* vec=new Vector<T>(x);//-----------??
	T* cur_storage=_storage;
	_storage=new T[x._size];
	if(_storage)
	{
	_size=x._size;
	copy(x._size,x._storage,_storage);
	if(cur_storage!=NULL)
	delete[] cur_storage;
	}
	return *this;
}

// size
// Returns the number of elements in the vector.
// This is the number of actual objects held in the
// vector, which is not necessarily equal to its
// storage capacity.
template <typename T>
int Vector<T>::size() const {
	// [TODO]
	return _size;
}

// empty
// Returns whether the vector is empty
template <typename T>
bool Vector<T>::empty() const {
	// [TODO]
	if(_size!=0)
	return false;
	return true;
}

// operator[]
// Returns a reference to the element at position n
// in the vector container.
// if the requested position is out of range, the
// behavior is undefined
template <typename T>
T& Vector<T>::operator[](int pos) {
	if(pos<_size)
	return _storage[pos];
	return _storage[_size-1];//if the pos is out of range then return the lastest one 
	// [TODO]
}

// resize
// Resizes the container so that it contains n elements.
// If n is smaller than the current container size, the 
// content is reduced to its first n elements, removing 
// those beyond (and destroying them).
// If n is greater than the current container size, the 
// content is expanded by inserting at the end as many 
// elements as needed to reach a size of n. If val is 
// specified, the new elements are initialized as copies 
// of val, otherwise, they are value-initialized.
template <typename T>
void Vector<T>::resize(size_t n, T val) {
	// [TODO]
	if(n<=_size)
	{
	T*  cur_storage= _storage;
	_storage=new T[n];
	if(_storage)
		_size=n;
	copy(n,cur_storage,_storage);
	if(cur_storage)
	delete[] cur_storage;
	}
	else
	{
	T*  cur_storage= _storage;
	_storage=new T[n];
	
	copy(_size,cur_storage,_storage);
	if(cur_storage)
	delete[] cur_storage;
	for(int i=_size;i<n;++i)
	push_back(val);
	if(_storage)
		_size=n;
	}
	return;
}
// push_back
// Adds a new element at the end of the vector, after its
// current last element. The content of val is copied (or
// moved) to the new element.
template <typename T>
void Vector<T>::push_back(const T& val) {
	// [TODO]
	T* cur_storage=_storage;
	_size++;
	_storage= new T[_size];
	copy(_size-1,cur_storage,_storage);
	_storage[_size-1]=val;
	if(cur_storage!=NULL)
	  delete[] cur_storage;
	return;
}

// a general sort
// Sort the vector, output the result in std out
// with monotonically increasing order in one line
// for instance: 
//     your original vector is 3 2 4 5
//     your output after sorting is 2 3 4 5
// you shouldn't change the order of oringinal vector
template <typename T>
void Vector<T>::sort() {
	// [TODO]
	Vector<T> sortv(*this);
	for(int j=0;j<sortv._size;++j)
	for(int i=0;i<sortv._size-1-j;++i)
	{
		if(sortv._storage[i]>sortv._storage[i+1])
		{
			T temp=sortv._storage[i];
			sortv._storage[i]=sortv._storage[i+1];
			sortv._storage[i+1]=temp;
		}
	}
	 for (int i = 0; i <sortv._size; i ++)
    {
      cout<<sortv[i]<<" ";
    }
	cout<<"\n";	
	 return;
}

// specialization of string
// Sort the string vector in lexicographical increasing order 
// from tail to head!
// for instance:
//      your original vector is "abc" "cba" "bcaa"
//      your output after sorting is "bcaa" "cba" "abc"
// you shouldn't change the order of oringinal vector
template <>
void Vector<string>::sort() {
	//[TODO]
	Vector<string> sortv(*this);
	for(int j=0;j<_size;++j)
	for(int i=0;i<_size-1-j;++i)
	{
		if(if_greater(sortv._storage[i],sortv._storage[i+1]))
		{
			string temp=sortv._storage[i];
			sortv._storage[i]=sortv._storage[i+1];
			sortv._storage[i+1]=temp;
		}
	}
	 for (int i = 0; i <sortv._size; i ++)
    {
      cout<<sortv[i]<<" ";
    }
	cout<<"\n";
	return ;
}
template <typename T>
bool Vector<T>::if_greater(string s1,string s2)
{
	int min;
	if(s1.size()>s2.size())
		min=s2.size();
	else
		min=s1.size();
	for(int i=1;i<=min;i++)
	{
		if(s1[s1.size()-i]>s2[s2.size()-i])
			return true;
		else if(s1[s1.size()-i]<s2[s2.size()-i])
			return false;
	}
	return false;
}
template <typename T>
void Vector<T>::copy(int n,T* sourse,T* dest)
{
    for(int i=0;i<n;++i)
	dest[i]=sourse[i];
}

#endif

