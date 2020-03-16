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

namespace custom
{
/********************************************************************
* LIST
* A doubly linked list class containing
*********************************************************************/
template <class T>
class list
{
public:
   //constructors and destructors
   list() : pHead(NULL), pTail(NULL), numElements(0) {}
   list(const list<T> &rhs);
   ~list() { clear();}

   //standard container interfaces
   bool empty() { return pHead == NULL; }
   int size() const { return numElements; }
   void clear();

   //nested classes
   class Node;
   class iterator;
   class reverse_iterator;
   class const_iterator;
   class const_reverse_iterator;

   //specific list interfaces
   void push_back(const T & t);
   void push_front(const T & t);
   void pop_back();
   void pop_front();

   T & front();
   const T & front() const;
   T & back();
   const T & back() const;

   iterator find(const T & t);
   void erase(iterator & it);
   iterator insert(iterator & it, const T & t);

   //iterator methods
   iterator begin() { return iterator(pHead); }
   iterator end() { return iterator(NULL); }
   reverse_iterator rbegin() { return reverse_iterator(pTail);}
   reverse_iterator rend() { return reverse_iterator(NULL); }
   const_reverse_iterator crbegin() const { return const_reverse_iterator(pTail);}
   const_reverse_iterator crend() const { return const_reverse_iterator(NULL);}
   const_iterator cbegin() const { return const_iterator(pHead);}
   const_iterator cend() const { return const_iterator(NULL);}

   //overloaded operator
   list &operator=(const list &rhs);   // assignment operator

private:
   Node * pHead;
   Node * pTail;
   int numElements;
};

/*************************************************************************
 * LIST : COPY CONSTRUCTOR
 * Creates a new list from an existing list
 *************************************************************************/
template <class T>
list<T>::list(const list<T> &rhs)
{
   // if the list is empty only initialize the list
   if(rhs.size() == 0)
   {
      pHead = NULL;
      pTail = NULL;
      numElements = 0;
   }
   else
   {
      // Copy the first node, its value and next node reference
      Node * currentNode = new Node(rhs.pHead->data);
      currentNode->pNext = rhs.pHead->pNext;
      // Set the first node as the head
      pHead = currentNode;
      numElements = 1;

      // If there is more than one node we need to copy the other nodes
      if(rhs.numElements > 1)
      {
         // go from the second node to the one before the last
         for (list<T>::iterator it = rhs.pHead->pNext; it != rhs.pTail; ++it)
         {
            // create new nodes, copy values and prev and next references
            Node * tempNode = new Node(*it);
            currentNode->pNext = tempNode;
            tempNode->pPrev = currentNode;

            // update the current node with the latest one created and increase the counter
            currentNode = tempNode;
            numElements++;
         }

         // copy the last element of the list and make it the tail node
         Node * tempNode = new Node(rhs.pTail->data);
         currentNode->pNext = tempNode;
         tempNode->pPrev = currentNode;
         pTail = tempNode;
         numElements++;
      }
         // otherwise make this only node the tail node
      else
      {
         pTail = currentNode;
      }
   }
}

/*******************************************
* LIST : CLEAR
* clear memory of all data, deleting nodes from list
*******************************************/
template <class T>
void list<T>::clear()
{
   // Starting from the head node delete each one
   while (pHead != NULL)
   {
      Node * pDelete = pHead;
      pHead = pHead->pNext;
      delete pDelete;
   }
   // Set list default values
   pTail = NULL;
   numElements = 0;
}

/*********************************************************************
* LIST :: PUSH_BACK
* Adds an node as the last node in the list
**********************************************************************/
template <class T>
void list<T>::push_back(const T & t)
{
   try
   {
      // New node created to be added to the linked list 
      Node * pNew = new Node(t);

      // If the list is empty, this first node is the head and tail
      if (numElements == 0)
      {
         pHead = pNew;
         pTail = pNew;
      }
         // Otherwise this new element will become the tail
      else
      {
         // Copy references from the existing tail node
         pTail->pNext = pNew;
         pNew->pPrev = pTail;
         pTail = pNew;
      }

      numElements++;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }

   return;
}

/*********************************************************************
* LIST :: PUSH_FRONT
* Adds an node as the first node in the list
**********************************************************************/
template <class T>
void list<T>::push_front(const T & t)
{
   try
   {
      // New node created to be added to the linked list 
      Node * pNew = new Node(t);

      // If the list is empty, this first node is the head and tail
      if (numElements == 0)
      {
         pHead = pNew;
         pTail = pNew;
      }
         // Otherwise this new element will become the tail
      else
      {
         // Copy references from the existing head node
         pHead->pPrev = pNew;
         pNew->pNext = pHead;
         pHead = pNew;
      }
      numElements++;
   }
   catch(std::bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
   return;

}

/*********************************************************************
* LIST :: POP_BACK
* Removes the last node in the list
**********************************************************************/
template <class T>
void list<T>::pop_back()
{
   if(!empty())
   {
      // Make the previous node the new tail node
      pTail->pPrev = pTail;
      numElements--;
   }

}

/*********************************************************************
* LIST :: POP_FRONT
* Removes the first node in the list
**********************************************************************/

template <class T>
void list<T>::pop_front()
{
   if(!empty())
   {
      // Make the previous node the new head node
      pHead->pNext = pHead;
      numElements--;
   }

}

/*********************************************************************
* LIST :: FRONT
* accesses the first element in the list read/write capable
**********************************************************************/
template <class T>
T & list<T>::front()
{
   if(!empty())
   {
      return pHead->data;
   }
   else
   {
      throw "ERROR: unable to access data from an empty list";
   }
}

/*********************************************************************
* LIST :: FRONT CONSTANT
* accesses the first element in the list read only.
**********************************************************************/
template <class T>
const T & list<T>::front() const
{
   if(!empty())
   {
      return pHead->data;
   }
   else
   {
      throw "ERROR: unable to access data from an empty list";
   }
}

/*********************************************************************
* LIST :: BACK
* accesses the last element in the list read/write capable
**********************************************************************/
template <class T>
T & list<T>::back()
{
   if(!empty())
   {
      return pTail->data;
   }
   else
   {
      throw "ERROR: unable to access data from an empty list";
   }
}
/*********************************************************************
* LIST :: BACK CONSTANT
* accesses the last element in the list read only.
**********************************************************************/
template <class T>
const T & list<T>::back() const
{
   if(!empty())
   {
      return pTail->data;
   }
   else
   {
      throw "ERROR: unable to access data from an empty list";
   }
}

/*********************************************************************
* LIST :: FIND
* Traverses the list, comparing search term to data in each node until
* the element is found. Returns an iterator of the found node. If search
* term is not found, returns end() iterator.
**********************************************************************/
template <class T>
typename list<T>::iterator list<T>::find(const T & t)
{
   //  Go through the complete linked list to find value
   for (list<T>::iterator it = begin(); it != end(); it++)
   {
      // If value is in the list return pointer otherwise return NULL
      if (*it == t)
         return it;
   }
   return end();
}

/*********************************************************************
* LIST :: INSERT
* inserts new node into list
**********************************************************************/
template <class T>
typename list<T>::iterator list<T>::insert(iterator & it, const T & t)
{
   // New node created to be added to the linked list 
   Node * pNew = new Node(t);

   // If the list is empty, this first node is the head and tail
   if (numElements == 0)
   {
      pHead = pNew;
      pTail = pNew;
   }

   // If the node after is not null
   if (it.p)
   {
      // the next node of pNew will be the current node
      pNew->pNext = it.p;
      // the previous node of pNew will be the previous to the current node
      pNew->pPrev = it.p->pPrev;
      // the previous node of current will be pNew
      it.p->pPrev = pNew;

      // if there is a node before pNew set pNew as the next node for it
      if (pNew->pPrev)
         pNew->pPrev->pNext = pNew;

      // if iterator pointing to the head node, make the new node the head
      if (it.p == pHead)
         pHead = pNew;
   }
      // If it is, then we are making a new tail node
   else
   {
      pTail->pNext= pNew;
      pNew->pPrev = pTail;
      pTail = pNew;
   }

   numElements++;
   return iterator(pNew);
}

/*********************************************************************
* LIST :: ERASE
* Removes a node from the list based on an iterator parameter.
**********************************************************************/
template <class T>
void list<T>::erase(iterator & it)
{
   // if the pointer is not null proceed with deletion
   if(it.p != NULL)
   {
      // if there is a previous node
      if(it.p->pPrev)
      {
         // Point that previous node to the one after the iterator
         it.p->pPrev->pNext = it.p->pNext;
      }
         // otherwise, make the next node the new head node
      else
      {
         pHead = it.p->pNext;
         pHead->pPrev = NULL;
      }

      // if there is a node after
      if(it.p->pNext)
      {
         // Point that next node to the one before the iterator
         it.p->pNext->pPrev = it.p->pPrev;
      }
         // otherwise, make the previous node the new tail node
      else
      {
         pTail = it.p->pPrev;
         pTail->pNext = NULL;
      }

      // Decrease node count and delete node
      numElements--;
      delete it.p;
   }
   return;
}

/************************************************************************
 * LIST : ASSIGNMENT OPERATOR
 * Overloaded = operator
 ***********************************************************************/
template <class T>
list<T> &list<T>::operator=(const list<T> &rhs)
{
   // If the list is empty, this first node is the head and tail
   if(rhs.size() == 0)
   {
      pHead = NULL;
      pTail = NULL;
      numElements = 0;
   }
   else
   {
      // Copy the first node, its value and next node reference
      Node * currentNode = new Node(rhs.pHead->data);
      currentNode->pNext = rhs.pHead->pNext;
      // Set the first node as the head
      pHead = currentNode;
      numElements = 1;

      // If there is more than one node we need to copy the other nodes
      if(rhs.numElements > 1)
      {
         // go from the second node to the one before the last
         for (list<T>::iterator it = rhs.pHead->pNext; it != rhs.pTail; ++it)
         {
            // create new nodes, copy values and prev and next references
            Node * tempNode = new Node(*it);
            currentNode->pNext = tempNode;
            tempNode->pPrev = currentNode;

            // update the current node with the lastest one created and 
            // increase the counter
            currentNode = tempNode;
            numElements++;
         }

         // copy the last element of the list and make it the tail node
         Node * tempNode = new Node(rhs.pTail->data);
         currentNode->pNext = tempNode;
         tempNode->pPrev = currentNode;
         pTail = tempNode;
         numElements++;
      }
         // otherwise make this only node the tail node
      else
      {
         pTail = currentNode;
      }


   }
   return *this;
}


/***********************************************************************
 * NODE
 * Linked list node.
 ***********************************************************************/
template <class T>
class list<T>::Node
{
public:
   // member variables
   T data;
   Node * pNext;
   Node * pPrev;

   // Default constructor
   Node() : pNext(NULL), pPrev(NULL), data(NULL) {};

   // Non-default constructor
   Node(const T & t) {
      data = t;
      pNext = NULL;
      pPrev = NULL;
   }
};

/***************************************************************************
 * LIST ITERATOR
 * An embedded class used to iterate through the List class
 ***************************************************************************/
template <class T>
class list<T>::iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator() : p(NULL) {}
   iterator(Node *p) : p(p) {}
   iterator(const iterator &rhs) { *this = rhs; }
   iterator &operator=(const iterator &rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator!=(const iterator &rhs) const { return rhs.p != this->p; }
   bool operator==(const iterator &rhs) const { return rhs.p == this->p; }

   // dereference operator
   T &operator*() { return p->data; }
   const T &operator*() const { return p->data;}

   // prefix increment
   iterator &operator++()
   {
      p = p->pNext;
      return *this;
   }

   // prefix decrement
   iterator &operator--()
   {
      p = p->pPrev;
      return *this;
   }

   // postfix increment
   iterator operator++(int postfix)
   {
      iterator tmp(*this);
      p = p->pNext;
      return tmp;
   }

   // postfix decrement
   iterator operator--(int postfix)
   {
      iterator tmp(*this);
      p = p->pPrev;
      return tmp;
   }
   // Friend classes from list, to allow direct usage of private
   // variables of the iterator
   friend iterator list<T>::insert(iterator & it, const T & t);
   friend void list<T>::erase(iterator & it);

private:
   Node *p; // pointer to Node
};

/***************************************************************************
 * LIST REVERSE ITERATOR
 * An embedded class used to reverse iterate through the List class
 ***************************************************************************/
template <class T>
class list<T>::reverse_iterator
{
public:
   // constructors, destructors, and assignment operator
   reverse_iterator() : p(NULL) {}
   reverse_iterator(Node *p) : p(p) {}
   reverse_iterator(const reverse_iterator &rhs) { *this = rhs; }
   reverse_iterator &operator=(const reverse_iterator &rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator!=(const reverse_iterator &rhs) const { return rhs.p != this->p; }
   bool operator==(const reverse_iterator &rhs) const { return rhs.p == this->p; }

   // dereference operator
   T &operator*() { return p->data; }
   const T &operator*() const { return p->data;}

   // prefix increment
   reverse_iterator &operator++()
   {
      p = p->pPrev;
      return *this;
   }

   // prefix decrement
   reverse_iterator &operator--()
   {
      p = p->pNext;
      return *this;
   }

   // postfix increment
   reverse_iterator operator++(int postfix)
   {
      reverse_iterator tmp(*this);
      p = p->pPrev;
      return tmp;
   }

   // postfix decrement
   reverse_iterator operator--(int postfix)
   {
      reverse_iterator tmp(*this);
      p = p->pNext;
      return tmp;
   }

private:
   Node *p; // pointer to Node
};

/***************************************************************************
 * LIST CONST ITERATOR
 * An embedded class used to iterate through the List class
 ***************************************************************************/
template <class T>
class list<T>::const_iterator
{
public:
   // constructors, destructors, and assignment operator
   const_iterator() : p(NULL) {}
   const_iterator(Node *p) : p(p) {}
   const_iterator(const iterator &rhs) { *this = rhs; }
   const_iterator &operator=(const const_iterator &rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator!=(const const_iterator &rhs) const { return rhs.p != this->p; }
   bool operator==(const const_iterator &rhs) const { return rhs.p == this->p; }

   // dereference operator
   T &operator*() { return p->data; }
   const T &operator*() const { return p->data;}

   // prefix increment
   const_iterator &operator++()
   {
      p = p->pNext;
      return *this;
   }

   // prefix decrement
   const_iterator &operator--()
   {
      p = p->pPrev;
      return *this;
   }

   // postfix increment
   const_iterator operator++(int postfix)
   {
      const_iterator tmp(*this);
      p = p->pNext;
      return tmp;
   }

   // postfix decrement
   const_iterator operator--(int postfix)
   {
      const_iterator tmp(*this);
      p = p->pPrev;
      return tmp;
   }

   // Friend classes from list, to allow direct usage of private
   // variables of the iterator
   friend const_iterator list<T>::insert(const_iterator & it, const T & t);
   friend void list<T>::erase(const_iterator & it);

private:
   Node *p; // pointer to Node
};

/***************************************************************************
 * LIST CONSTANT REVERSE ITERATOR
 * An embedded class used to reverse iterate through the List class
 ***************************************************************************/
template <class T>
class list<T>::const_reverse_iterator
{
public:
   // constructors, destructors, and assignment operator
   const_reverse_iterator() : p(NULL) {}
   const_reverse_iterator(Node *p) : p(p) {}
   const_reverse_iterator(const const_reverse_iterator &rhs) { *this = rhs; }
   const_reverse_iterator &operator=(const const_reverse_iterator &rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator!=(const const_reverse_iterator &rhs) const { return rhs.p != this->p; }
   bool operator==(const const_reverse_iterator &rhs) const { return rhs.p == this->p; }

   // dereference operator
   T &operator*() { return p->data; }
   const T &operator*() const { return p->data;}

   // prefix increment
   const_reverse_iterator &operator++()
   {
      p = p->pPrev;
      return *this;
   }

   // prefix decrement
   const_reverse_iterator &operator--()
   {
      p = p->pNext;
      return *this;
   }

   // postfix increment
   const_reverse_iterator operator++(int postfix)
   {
      const_reverse_iterator tmp(*this);
      p = p->pPrev;
      return tmp;
   }

   // postfix decrement
   const_reverse_iterator operator--(int postfix)
   {
      const_reverse_iterator tmp(*this);
      p = p->pNext;
      return tmp;
   }

private:
   Node *p; // pointer to Node
};
};
#endif //CS235_LIST_H
