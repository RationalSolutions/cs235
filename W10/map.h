/***********************************************************************
 * Component:
 *    Assignment 10, Map
 *    Brother Kirby, CS 235
 * Author:
 *    Coby Jenkins
 *    Michael Gibson
 * Summary: 
 *    Ths class captures the notion of a map, an associative container
 *    using a key value and a data value. The key value uniquely identifies
 *    a given data value; however, both the key and data values can be
 *    any data type.
 ************************************************************************/

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include "bst.h"
#include "pair.h"

namespace custom
{
/**************************************************************************
 * MAP class an associative container formed by combining a key value and a
 * mapped value. The key value is used to sort and uniquely identify the 
 * elements. The mapped values store content associated with the key. 
 ***************************************************************************/
template <class K, class V>
class map
{
private:
   BST<pair<K, V> > bst;

public:
    //constructors & destructors
    map(){}
    map(const map<K, V> &rhs)
    {
       try
       {
          this->bst = rhs.bst;
       }
       catch (std::bad_alloc)
       {
          throw "ERROR: Unable to allocate a node";
       }
    }

    ~map() { clear(); }

    // nested classes
    class iterator;
    class reverse_iterator;

    //operator overloading
    map<K, V> &operator=(const map<K, V> &rhs)
    {
       this->bst = rhs.bst;
       return *this;
    }

   friend std::ostream &operator<<(std::ostream &out, map<K, V> &pMap)
   {
      typename BST<pair <K, V> >::iterator it;
      out << "{  ";
      for(it = pMap.bst.begin();it != pMap.bst.end();++it)
      {
         out << (*it).getSecond() << "  ";
      }
      out << "}";
      return out;
   }

    V & operator[] (const K & k);
    const V operator[] (const K & k) const;

    // standard interfaces
    int size() { return bst.size(); }
    bool empty() { return bst.empty(); }
    void clear() { bst.clear(); }

    // specific interfaces
    void insert(const pair <K, V> & input);
    void insert(const K & k, const V & v);
    iterator find(const K &k)
    {
       pair<K, V> newPair(k, V());
       typename BST<pair<K, V> >:: iterator it = bst.find(newPair);
       iterator it1=it;
       return it1;
    }

    // iterators
    iterator begin()
    {
       typename BST<pair<K, V> >::iterator it = bst.begin();
       iterator it1(it);
       return it1;
    }

    iterator end()
    {
       typename BST<pair<K, V> >::iterator it = bst.end();
       iterator it1(it);
       return it1;
    }

    reverse_iterator rbegin()
    {
       typename BST<pair<K, V> >::iterator it = bst.rbegin();
       iterator it1(it);
       return it1;
    }

    reverse_iterator rend()
    {
       typename BST<pair<K, V> >::iterator it = bst.rend();
       iterator it1(it);
       return it1;
    }

};

/***********************************************************************
 * MAP :: ACCESS OPERATOR
 * overloads the access operator "[]" to work with the map class
 ***********************************************************************/
template <class K, class V>
V & map<K, V>::operator[](const K & k)
{
    pair<K, V> newPair(k, V());
    typename BST<pair<K, V> >::iterator it = bst.find(newPair);

    if(it != NULL)
    {
        return (*it).second;
    }
    else
    {
        bst.insert(newPair);
        return (*bst.find(newPair)).second;
    }
}

/***********************************************************************
 * MAP :: ACCESS OPERATOR : CONSTANT
 * overloads the access operator "[]" to work with the map class
 ***********************************************************************/
template <class K, class V>
const V map <K, V> :: operator[] (const K & k) const
{
   pair<K, V> newPair(k, V());
   typename BST<pair<K, V> >::iterator it = bst.find(newPair);

   if(it != NULL)
   {
   return (*it).second;
   }
   else
   {
   bst.insert(newPair);
   return (*bst.find(newPair)).second;
   }
}

/***********************************************************************
 * MAP :: INSERT
 * Searches for the existence of a node with the K value and inserts a new
 * value into the V value or creates a new node for the new pair. 
 ***********************************************************************/
template <class K, class V>
void map <K, V> :: insert(const pair <K, V> & input)
{
    typename BST<pair<K, V> >::iterator it = bst.find(input);
    if(it != NULL)
    {
        *it = input;
    }
    else
    {
        bst.insert(input);
    }
}

/***********************************************************************
 * MAP :: INSERT
 * Searches for the existence of a node with the K value and inserts a new
 * value into the V value or creates a new node for the new pair. 
 ***********************************************************************/
template <class K, class V>
void map <K, V> :: insert(const K & k, const V & v)
{
   pair<K, V> newPair(k, v);

   bst.insert(newPair);
}

/***********************************************************************
 * MAP :: ITERATOR
 * provides an iterator class for the Map class
 ***********************************************************************/
template <class K, class V>
class map <K, V> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator() : it(NULL) {}
   iterator(typename BST<pair<K, V> >::iterator itBST): it(itBST){}
   iterator(const iterator &rhs)
   {
      *this = rhs;
   }

   iterator &operator=(const iterator &rhs)
   {
      this->it = rhs.it;
      return *this;
   }

   // equals, not equals operator
   bool operator!=(const iterator &rhs) const { return rhs.it != this->it; }
   bool operator==(const iterator &rhs) const { return rhs.it == this->it; }

   // dereference operator
   pair<K,V> &operator*() { return (*it); }
   const pair<K, V> &operator*() const { return (*it); }

   // prefix increment
   iterator &operator++()
   {
      ++it;
      return *this;
   }

   // prefix decrement
   iterator &operator--()
   {
      --it;
      return *this;
   }

   // postfix increment
   iterator operator++(int postfix)
   {
      iterator tmp = *this;
      ++(*this);
      return tmp;
   }

   // postfix decrement
   iterator operator--(int postfix)
   {
      iterator tmp = *this;
      --(*this);
      return tmp;
   }

private:
   typename BST<pair<K, V>>::iterator it; // an iterator from the BST class
};

/***********************************************************************
 * MAP :: REVERSE ITERATOR
 * provides a reverse iterator class for the Map class
 ***********************************************************************/
template <class K, class V>
class map <K, V> :: reverse_iterator
{
public:
   // constructors, destructors, and assignment operator
   reverse_iterator() : it(NULL) {}
   reverse_iterator(typename BST<pair<K, V> >::reverse_iterator itBST): it(itBST){}
   reverse_iterator(const reverse_iterator &rhs)
   {
      *this = rhs;
   }

   reverse_iterator &operator=(const reverse_iterator &rhs)
   {
      this->it = rhs.it;
      return *this;
   }

   // equals, not equals operator
   bool operator!=(const reverse_iterator &rhs) const { return rhs.it != this->it; }
   bool operator==(const reverse_iterator &rhs) const { return rhs.it == this->it; }

   // dereference operator
   pair<K,V> &operator*() { return (*it); }
   const pair<K, V> &operator*() const { return (*it); }

   // prefix increment
   reverse_iterator &operator++()
   {
      ++it;
      return *this;
   }

   // prefix decrement
   reverse_iterator &operator--()
   {
      --it;
      return *this;
   }

   // postfix increment
   reverse_iterator operator++(int postfix)
   {
      reverse_iterator tmp = *this;
      ++(*this);
      return tmp;
   }

   // postfix decrement
   reverse_iterator operator--(int postfix)
   {
      reverse_iterator tmp = *this;
      --(*this);
      return tmp;
   }

private:
   typename BST<pair<K, V>>::iterator it; // an iterator from the BST class
};

} // namespace custom

#endif // MAP_H