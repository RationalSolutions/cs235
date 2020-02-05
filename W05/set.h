/***********************************************************************
 * Header:
 *    Set
 * Summary:
 *    This class contains the notion of an Set. This acts like the
 *    standard library Set class and is generic, meaning it accepts
 *    any data-type. New data can be pushed or popped
 *    from either side as well. However, the elements between the
 *    first and last element cannot be touched. The order of these
 *    elements are maintained.
 *
 *    This will contain the class definition of:
 *       Set             : similar to std::Set
 * Author
 *    Coby Jenkins
 *    Michael Gibson
 ************************************************************************/

#ifndef CS235_SET_H
#define CS235_SET_H

#include <cstddef> // allows NULL
#include <new> // allows bad_alloc
#include <cassert>

namespace custom;

{
/*********************************************************
 * SET
 * A data structure that is an abstract data type container,
 * representing a collection of unique elements. The Set can
 * be accessed either sequentially or by search. It expands to
 * meet the needs of the client.
 * *********************************************************/
template <class T>
class set
{
private:
   T * data;
   int numElements;
   int numCapacity;

   void resize(int newCapacity);
   int capacity() const { return numCapacity; }
   int findIndex(const T & t);

public:
   // constructors and destructors
   set(): numCapacity(0), numElements(0), data(NULL){};
   set(int numCapacity);
   set(const set <T> & rhs);
   ~set()
   {
      data = NULL;
      delete []data;
   }

   // overload operators
   set & operator = (const set & rhs);  // assignment
   set & operator || (const set & rhs); // union
   set & operator && (const set & rhs); // intersection
   set & operator - (const set & rhs);  // difference

   // standard container interfaces
   int size() const { return numElements; }
   bool empty() const { return (size() == 0); }
   void clear() { numElements = 0; data = NULL; }
   void insert(const T & t);

   // iterator interfaces
   class iterator;
   iterator begin()      { return iterator (data); }
   iterator end();
   reverse_iterator rbegin();
   iterator find(T t);
   iterator erase(iterator it);

   class const_iterator;
   const_iterator cbegin() const { return const_iterator (data); }
   const_iterator cend() const;
   const_reverse_iterator crbegin() const;
   const_iterator find(const T & t) const;

};

/**************************************************
 * SET ITERATOR
 * An iterator through set
 *************************************************/
template <class T>
class set <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator()      : p(NULL)      {              }
   iterator(T * p) : p(p)         {              }
   iterator(const iterator & rhs) { *this = rhs; }
   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
         T & operator * ()       { return *p; }
   const T & operator * () const { return *p; }

   // prefix increment
   iterator & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   iterator operator ++ (int postfix)
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }

   // prefix decrement
   iterator & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix decrement
   iterator & operator -- (int postfix)
   {
      iterator tmp(*this);
      p--;
      return tmp;
   }
   
private:
   T * p;
};

/**************************************************
 * SET CONST ITERATOR
 * A protected iterator through set
 *************************************************/
template <class T>
class set <T> :: const_iterator
{
public:
   // constructors, destructors, assignment operator
   const_iterator()      : p(NULL)            {              }
   const_iterator(T * p) : p(p)               {              }
   const_iterator(const const_iterator & rhs) { *this = rhs; }
   const_iterator & operator= (const const_iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operators
   bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
   bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

   // dereference operator
   const T & operator * () const { return *p; }

   // prefix increment
   const_iterator & operator ++ ()
   {
      p++;
      return *this;
   }
   
   // postfix increment
   const_iterator operator ++ (int postfix)
   {
      const_iterator tmp(*this);
      p++;
      return tmp;
   }

   // prefix decrement
   const_iterator & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix decrement
   const_iterator & operator -- (int postfix)
   {
      const_iterator tmp(*this);
      p--;
      return tmp;
   }

private:
   T * p;
};

/********************************************
* SET ITERATOR :: END
* Note that you have to use "typename" before the return value type
********************************************/
template <class T>
typename set <T>::iterator set<T>::end()
{
   return iterator(data + numElements);
}

/********************************************
* SET ITERATOR :: FIND
* Note that you have to use "typename" before the return value type
********************************************/
template <class T>
typename set<T>::iterator set<T>::find(T t)
{
   for (iterator it = begin(); it != end(); it++)
   {
      if(*(it) == t)
         return it;
   }

   return end();
}

/********************************************
* SET ITERATOR :: ERASE
* Note that you have to use "typename" before the return value type
********************************************/
template <class T>
typename set<T>::iterator set<T>::erase(set<T>::iterator it)
{
   int index = findIndex(*(it++));

   int a = 0;
   T* tempData = new T[numCapacity];

   for (int i = 0; i < (numElements - 1) ; ++i)
   {
      if(n == index)
         ++a;

      tempData[i] = data[a++];
   }

   try
   {
      this->data = new T[rhs.capacity()];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for set";
   }

   for (int j = 0; j < numElements; j++)
   {
      data[j] = tempData[j];
   }

   delete[] tempData;
   numElements--;

   return it;


}

} //namespace custom