/***********************************************************************
 * Header:
 *    List
 * Summary:
 *    This class contains the notion of a List. This acts like the
 *    standard library List class and is generic, meaning it accepts
 *    any data-type.
 *
 *    This will contain the class definition of:
 *       List             : similar to std::List
 * Author
 *    Coby Jenkins
 *    Michael Gibson
 ************************************************************************/

#ifndef CS235_LIST_H
#define CS235_LIST_H

#include <iostream>
#include <cstddef> // allows NULL
#include <new> // allows bad_alloc
#include "node.h"

namespace custom
{
template <class T>
class list
{
private:
   //Private Member Variables
   Node <T> * pHead;
   Node <T> * pTail;
   int numElements;

public:
   //Constructors & Destructor
   list() : pHead(NULL), pTail(NULL), numElements(0) {}
   list(const list <T> & rhs);
   ~list() { freeData(pHead); }

   //overloaded operator
   list & operator = (const list & rhs);

   //Standard container interfaces
   int size() const { return numElements; }
   bool empty() const { return pHead == NULL; }
   void clear() { numElements = 0; }

   //List specific interfaces
   void push_back(const T & t);
   void push_front(const T & t);
   void pop_back(const T & t);
   void pop_front(const T & t);

   //Setters & Getters
   T & front();
   T & front() const;
   T & back();
   T & back() const;

   //Iterators
   class iterator;
   iterator find(T element);
   void erase(iterator & it);
   iterator insert(iterator & it, const T & element);
   iterator begin() { return iterator(pHead); }
   iterator end() { return iterator(pTail); }
   iterator rbegin() { return iterator(pTail);}
   iterator rend() { return iterator(NULL); }

   //Constant Iterators
   class const_iterator;
   const_iterator cfind(const T & element) const;
   const_iterator cbegin() const { return const_iterator(pHead); }
   const_iterator cend() const { return const_iterator(pTail); }
   const_iterator crbegin() const { return const_iterator(pTail);}
   const_iterator crend() const { return const_iterator(NULL);}

};

/***************************************************************************
 * LIST ITERATOR
 * An embedded class used to iterate through the List class
 ***************************************************************************/
template <class T>
class list <t> :: iterator
{
private:
   T * p;
public:
   // constructors, destructors, and assignment operator
   iterator() : p(NULL){}
   iterator(T *p) : p(p){}
   iterator(const iterator & rhs) { *this = rhs; }

   iterator & operator = (const iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals & not equals operators
   bool operator == (const iterator & rhs) const { return rhs.p == this->p; }
   bool operator != (const iterator & rhs) const { return rhs.p != this->p; }

   // dereference operator (constant and not)
   T & operator * () { return *p; }
   const T & operator * () { return *p; }

   // increment and decrement / prefix and postfix
   iterator & operator ++ () // prefix increment
   {
      p++;
      return *this;
   }

   iterator & operator ++ (int postfix) // postfix increment
   {
      iterator tmp(*this);
      p++;
      return tmp;
   }

   iterator & operator -- () // prefix decrement
   {
      p--;
      return *this;
   }

   iterator & operator -- (int postfix) // postfix decrement
   {
      iterator tmp(*this);
      p--;
      return tmp;
   }
};

/***************************************************************************
 * LIST CONST ITERATOR
 * An embedded class used to iterate through the List class
 ***************************************************************************/
template <class T>
class list <t> :: const_iterator
{
private:
   T * p;
public:
   // constructors, destructors, assignment operator
   const_iterator() : p(NULL){}
   const_iterator(T * p) : p(p){}
   const_iterator(const const_iterator & rhs) { *this = rhs; }

   const_iterator & operator = (const const_iterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals & not equals operators
   bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }
   bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }

   // dereference operator
   const T & operator * () const { return *p; }

   // increment and decrement / prefix and postfix
   const_iterator & operator ++ () //prefix increment
   {
      p++;
      return *this;
   }
   
   const_iterator operator ++ (int postfix) // postfix increment
   {
      const_iterator tmp(*this);
      p++;
      return tmp;
   }

   const_iterator & operator -- () // prefix decrement
   {
      p--;
      return *this;
   }

   const_iterator & operator -- (int postfix) // postfix decrement
   {
      const_iterator tmp(*this);
      p--;
      return tmp;
   }

};

/*************************************************************************
 * LIST : COPY CONSTRUCTOR
 * Creates a new list from an existing list
 *************************************************************************/
template <class T>
list <T> :: list(const list <T> & rhs)
{
   //if there are no elements in the source list
   if(rhs.numElements == 0){
      this->numElements = 0;
      this->pHead = NULL;
      this->pTail = NULL;
      return;
   }

   //attempt to allocate
   try {
   Node <T> * pNewHead =  new Node <T> (rhs.data);
   Node <T> * pNewTail = pNewHead;
   }
   catch {
      throw "ERROR: unable to allocate a new node for a list";
   }

   // insert nodes from source list to new list
   for(Node <T> * p = rhs.pNext; p; p = p->pNext){
      pNewTail = insert(pNewTail, p->data, true);
   }

   // set list parameters
   this->pHead = pNewHead;
   this->pTail = pNewTail;
   this->numElements = rhs.numElements;
}

/************************************************************************
 * LIST : ASSIGNMENT OPERATOR
 * Overloaded = operator
 ***********************************************************************/
template <class T>
list <T> & list <T> :: operator = (const list & rhs)
{
   //if there are no elements in source list
   if(rhs.numElements == 0){
      this->numElements = 0;
      this->pHead = NULL;
      this->pTail = NULL;
      return *this;
   }

   //attempt to allocate Node
   try {
   Node <T> * pNewHead =  new Node <T> (rhs.data);
   Node <T> * pNewTail = pNewHead;
   }
   catch {
      throw "ERROR: unable to allocate a new node for a list";
   }

   // insert nodes from source list to new list
   for(Node <T> * p = rhs.pNext; p; p = p->pNext){
      pNewTail = insert(pNewTail, p->data, true);
   }

   // set list parameters
   this->pHead = pNewHead;
   this->pTail = pNewTail;
   this->numElements = rhs.numElements;

   return *this;
}

}

#endif //CS235_LIST_H
