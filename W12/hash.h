#ifndef HASH_H
#define HASH_H


#include <iostream>
#include <string>
#include "list.h"

using namespace custom;
/*****************************************************
* HASH
******************************************************/
template <class T>
class Hash
{
public:
   //constructors & destructors
	Hash() : sizeInt(0), bucketSize(0), table(NULL){}
	Hash(int buckets) : sizeInt(0), bucketSize(buckets)
	{
		table = new list <T>[buckets];
	}
   Hash(const Hash & rhs)
   {
      if(rhs.size() == 0)
      {
         sizeInt = 0;
         bucketSize = rhs.bucketSize;
         table = NULL;
         return;
      } else
      {
         table = new list<T>[rhs.bucketSize];
      }

      this->bucketSize = rhs.bucketSize;
      this->sizeInt = rhs.sizeInt;

      for (int i = 0; i < bucketSize; i++)
      {
         this->table[i] = rhs.table[i];
      }
   }
	~Hash(){ clear();}

	//assignment operator
	Hash &operator=(const Hash & rhs);

   //standard interfaces
	bool empty() { return (sizeInt == 0);}
	int size() const { return sizeInt;}
	int capacity() const	{ return bucketSize;}
	void clear() { sizeInt = 0;}
	bool find(const T & t);
	void insert(const T & t);

	//This is a pure virtual function taking an element as a parameter and returning an index into the underlying array.
	virtual int hash(const T & value) const = 0;

private:
	int sizeInt;
	int bucketSize;
	list<T> * table;

};

/*****************************************************
* HASH : ASSIGNMENT OPERATOR
******************************************************/
template <class T>
Hash<T> &Hash<T>::operator=(const Hash &rhs)
{
   if(rhs.size() == 0)
   {
      sizeInt = 0;
      bucketSize = rhs.bucketSize;
      table = NULL;
      return *this;
   } else
   {
      table = new list<T>[rhs.bucketSize];
   }

   this->sizeInt = rhs.sizeInt;
   this->bucketSize = rhs.bucketSize;

   for (int i = 0; i < bucketSize; ++i)
   {
      table[i] = rhs.table[i];
   }

   return *this;
}

/*****************************************************
* HASH : INSERT
******************************************************/
template <class T>
void Hash<T>::insert(const T &t)
{
   int i = hash(t);
   table[i].push_back(t);
   sizeInt++;
}

/*****************************************************
* HASH : FIND
******************************************************/
template <class T>
bool Hash<T>::find(const T &t)
{
   int i = hash(t);

   if(table[i].find(t) == NULL)
   {
      return false;
   } else
   {
      return true;
   }
}

#endif