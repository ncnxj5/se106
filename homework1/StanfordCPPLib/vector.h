/*
 * File: vector.h
 * --------------
 * This file exports the <code>Vector</code> class, which provides an
 * efficient, safe, convenient replacement for the array type in C++.
 */

#ifndef _vector_h
#define _vector_h

#include <iterator>
#include <iostream>
#include <sstream>
#include <string>
#include "foreach.h"
#include "strlib.h"

/*
 * Class: Vector<T>
 * ------------------------
 * This class stores an ordered list of values similar to an array.
 * It supports traditional array selection using square brackets, but
 * also supports inserting and deleting elements.  It is similar in
 * function to the STL <code>vector</code> type, but is simpler both
 * to use and to implement.
 */

template <typename T>
class Vector {

public:

   Vector();
   explicit Vector(int n, T value = T());
   virtual ~Vector();
   int size() const;
   bool isEmpty() const;
   void clear();
   const T & get(int index) const;
   void set(int index, const T & value);
   void insert(int index, T value);
   void remove(int index);
   void add(T value);
   void push_back(T value);
   T & operator[](int index);
   const T & operator[](int index) const;
   Vector operator+(const Vector & v2) const;
   Vector & operator+=(const Vector & v2);
   Vector & operator+=(const T & value);
   std::string toString();
   void mapAll(void (*fn)(T)) const;
   void mapAll(void (*fn)(const T &)) const;

   template <typename FunctorType>
   void mapAll(FunctorType fn) const;

private:
  T *elements;        /* A dynamic array of the elements   */
   int capacity;               /* The allocated size of the array   */
   int count;                  /* The number of elements in use     */
   void expandCapacity();
   void deepCopy(const Vector & src);

public:
   Vector(const Vector & src);
   Vector & operator=(const Vector & src);
   Vector & operator,(const T & value);
   class iterator :
      public std::iterator<std::random_access_iterator_tag, T> {

   private:
      const Vector *vp;
      int index;

   public:

      iterator() {
         this->vp = NULL;
      }

      iterator(const iterator & it) {
         this->vp = it.vp;
         this->index = it.index;
      }

      iterator(const Vector *vp, int index) {
         this->vp = vp;
         this->index = index;
      }

      iterator & operator++() {
         index++;
         return *this;
      }

      iterator operator++(int) {
         iterator copy(*this);
         operator++();
         return copy;
      }

      iterator & operator--() {
         index--;
         return *this;
      }

      iterator operator--(int) {
         iterator copy(*this);
         operator--();
         return copy;
      }

      bool operator==(const iterator & rhs) {
         return vp == rhs.vp && index == rhs.index;
      }

      bool operator!=(const iterator & rhs) {
         return !(*this == rhs);
      }

      bool operator<(const iterator & rhs) {
         extern void error(std::string msg);
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index < rhs.index;
      }

      bool operator<=(const iterator & rhs) {
         extern void error(std::string msg);
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index <= rhs.index;
      }

      bool operator>(const iterator & rhs) {
         extern void error(std::string msg);
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index > rhs.index;
      }

      bool operator>=(const iterator & rhs) {
         extern void error(std::string msg);
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index >= rhs.index;
      }

      iterator operator+(const int & rhs) {
         return iterator(vp, index + rhs);
      }

      iterator operator+=(const int & rhs) {
         index += rhs;
         return *this;
      }

      iterator operator-(const int & rhs) {
         return iterator(vp, index - rhs);
      }

      iterator operator-=(const int & rhs) {
         index -= rhs;
         return *this;
      }

      int operator-(const iterator & rhs) {
         extern void error(std::string msg);
         if (vp != rhs.vp) error("Iterators are in different vectors");
         return index - rhs.index;
      }

      T & operator*() {
         return vp->elements[index];
      }

      T *operator->() {
         return &vp->elements[index];
      }

      T & operator[](int k) {
         return vp->elements[index + k];
      }

   };

   iterator begin() const {
      return iterator(this, 0);
   }

   iterator end() const {
      return iterator(this, count);
   }

};

extern void error(std::string msg);
template <typename T>
Vector<T>::Vector() {
   count = capacity = 0;
   elements = NULL;
}

template <typename T>
Vector<T>::Vector(int n, T value) {
   count = capacity = n;
   elements = (n == 0) ? NULL : new T[n];
   for (int i = 0; i < n; i++) {
      elements[i] = value;
   }
}

template <typename T>
Vector<T>::~Vector() {
   if (elements != NULL) delete[] elements;
}
template <typename T>
int Vector<T>::size() const {
   return count;
}

template <typename T>
bool Vector<T>::isEmpty() const {
   return count == 0;
}

template <typename T>
void Vector<T>::clear() {
   if (elements != NULL) delete[] elements;
   count = capacity = 0;
   elements = NULL;
}

template <typename T>
const T & Vector<T>::get(int index) const {
   if (index < 0 || index >= count) error("get: index out of range");
   return elements[index];
}

template <typename T>
void Vector<T>::set(int index, const T & value) {
   if (index < 0 || index >= count) error("set: index out of range");
   elements[index] = value;
}

template <typename T>
void Vector<T>::insert(int index, T value) {
   if (count == capacity) expandCapacity();
   if (index < 0 || index > count) {
      error("insert: index out of range");
   }
   for (int i = count; i > index; i--) {
      elements[i] = elements[i - 1];
   }
   elements[index] = value;
   count++;
}

template <typename T>
void Vector<T>::remove(int index) {
   if (index < 0 || index >= count) error("remove: index out of range");
   for (int i = index; i < count - 1; i++) {
      elements[i] = elements[i + 1];
   }
   count--;
}

template <typename T>
void Vector<T>::add(T value) {
   insert(count, value);
}

template <typename T>
void Vector<T>::push_back(T value) {
   insert(count, value);
}

template <typename T>
T & Vector<T>::operator[](int index) {
   if (index < 0 || index >= count) error("Selection index out of range");
   return elements[index];
}
template <typename T>
const T & Vector<T>::operator[](int index) const {
   if (index < 0 || index >= count) error("Selection index out of range");
   return elements[index];
}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector & v2) const {
   Vector<T> vec = *this;
   foreach (T value in v2) {
      vec.add(value);
   }
   return vec;
}

template <typename T>
Vector<T> & Vector<T>::operator+=(const Vector & v2) {
   foreach (T value in v2) {
      *this += value;
   }
   return *this;
}

template <typename T>
Vector<T> & Vector<T>::operator+=(const T & value) {
   this->add(value);
   return *this;
}

template <typename T>
std::string Vector<T>::toString() {
   ostringstream os;
   os << *this;
   return os.str();
}
template <typename T>
Vector<T>::Vector(const Vector & src) {
   deepCopy(src);
}

template <typename T>
Vector<T> & Vector<T>::operator=(const Vector & src) {
   if (this != &src) {
      if (elements != NULL) delete[] elements;
      deepCopy(src);
   }
   return *this;
}

template <typename T>
void Vector<T>::deepCopy(const Vector & src) {
   count = capacity = src.count;
   elements = (capacity == 0) ? NULL : new T[capacity];
   for (int i = 0; i < count; i++) {
      elements[i] = src.elements[i];
   }
}

/*
 * Implementation notes: The , operator
 * ------------------------------------
 * The comma operator works adding the right operand to the vector and
 * then returning the vector by reference so that it is set for the next
 * value in the chain.
 */

template <typename T>
Vector<T> & Vector<T>::operator,(const T & value) {
   this->add(value);
   return *this;
}

/*
 * Implementation notes: mapAll
 * ----------------------------
 * The various versions of the mapAll function apply the function or
 * function object to each element in ascending index order.
 */

template <typename T>
void Vector<T>::mapAll(void (*fn)(T)) const {
   for (int i = 0; i < count; i++) {
      fn(elements[i]);
   }
}

template <typename T>
void Vector<T>::mapAll(void (*fn)(const T &)) const {
   for (int i = 0; i < count; i++) {
      fn(elements[i]);
   }
}

template <typename T>
template <typename FunctorType>
void Vector<T>::mapAll(FunctorType fn) const {
   for (int i = 0; i < count; i++) {
      fn(elements[i]);
   }
}

/*
 * Implementation notes: expandCapacity
 * ------------------------------------
 * This function doubles the array capacity, copies the old elements
 * into the new array, and then frees the old one.
 */

template <typename T>
void Vector<T>::expandCapacity() {
   capacity = max(1, capacity * 2);
   T *array = new T[capacity];
   for (int i = 0; i < count; i++) {
      array[i] = elements[i];
   }
   if (elements != NULL) delete[] elements;
   elements = array;
}

/*
 * Implementation notes: << and >>
 * -------------------------------
 * The insertion and extraction operators use the template facilities in
 * strlib.h to read and write generic values in a way that treats strings
 * specially.
 */

template <typename T>
std::ostream & operator<<(std::ostream & os, const Vector<T> & vec) {
   os << "{";
   int len = vec.size();
   for (int i = 0; i < len; i++) {
      if (i > 0) os << ", ";
      writeGenericValue(os, vec[i], true);
   }
   return os << "}";
}

template <typename T>
std::istream & operator>>(std::istream & is, Vector<T> & vec) {
   char ch;
   is >> ch;
   if (ch != '{') error("operator >>: Missing {");
   vec.clear();
   is >> ch;
   if (ch != '}') {
      is.unget();
      while (true) {
         T value;
         readGenericValue(is, value);
         vec += value;
         is >> ch;
         if (ch == '}') break;
         if (ch != ',') {
            error(std::string("operator >>: Unexpected character ") + ch);
         }
      }
   }
   return is;
}

#endif
