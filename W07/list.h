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

#include "node.h"

namespace custom{
   template <class T>
   class list
   {
   private:
      //Private Member Variables
      Node * pHead;
      Node * pTail;
      int numElements;
      //Private Class
      class Node;

   public:
      //Constructors & Destructor
      list() : pHead(NULL), pTail(NULL), numElements(0) {}
      list(const list<T> &rhs);
      ~list() { clear();}

      //overloaded operator
      list &operator=(const list &rhs);

      //Standard container interfaces
      bool empty() { return pHead == NULL; }
      int size() const { return numElements; }
      void clear();

      //List specific interfaces
      void push_back(T t);
      void push_front(T t);
      void pop_back(T t);
      void pop_front(T t);

      //Setters & Getters
      T & front();
      const T & front() const;
      T & back();
      const T & back() const;

      //Iterator
      class iterator;

      iterator begin() { return iterator(pHead); }
      iterator end() { return iterator(NULL); }
      iterator find(const T &element);
      void erase(iterator & it);
      iterator insert(iterator & it, const T & element);
   };


}

#endif //CS235_LIST_H
