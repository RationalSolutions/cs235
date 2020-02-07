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

namespace custom
{
/*********************************************************
 * SET
 * A data structure that is an abstract data type container,
 * representing a collection of unique elements. The Set can
 * be accessed either sequentially or by search. It expands to
 * meet the needs of the client.
 * *********************************************************/
   template<class T>
   class set
   {
   private:
      T *data;
      int numElements;
      int numCapacity;

      void resize(int newCapacity);
      int capacity() const { return numCapacity; }
      const int findIndex(const T t);
      void reallocateData(int numCapacity);

   public:
      // constructors and destructors
      set() : numCapacity(0), numElements(0), data(NULL){};
      set(int numCapacity);
      set(const set<T> &rhs);
      ~set()
      {
         data = NULL;
         delete[]data;
      }

      // overload operators
      set &operator=(const set &rhs);  // assignment
      set operator||(const set &rhs); // union
      set operator&&(const set &rhs); // intersection

      // standard container interfaces
      int size() const { return numElements; }
      bool empty() const { return (size() == 0); }
      void clear()
      {
         numElements = 0;
         data = NULL;
      }
      void insert(const T t);

      // iterator interfaces
      class iterator;
      iterator begin() { return iterator(data); }
      iterator end();
      iterator find(T t);
      iterator erase(iterator it);
   };

/**************************************************
 * SET ITERATOR
 * An iterator through set
 *************************************************/
   template<class T>
   class set<T>::iterator
   {
   public:
      // constructors, destructors, and assignment operator
      iterator() : p(NULL){}
      iterator(T *p) : p(p){}
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
      T &operator*() { return *p; }
      const T &operator*() const { return *p; }

      // prefix increment
      iterator &operator++()
      {
         p++;
         return *this;
      }

      // postfix increment
      iterator operator++(int postfix)
      {
         iterator tmp(*this);
         p++;
         return tmp;
      }

   private:
      T *p;
   };

/********************************************
* SET ITERATOR :: END
* Note that you have to use "typename" before the return value type
********************************************/
   template<class T>
   typename set<T>::iterator set<T>::end()
   {
      return iterator(data + numElements);
   }

/********************************************
* SET ITERATOR :: FIND
* Note that you have to use "typename" before the return value type
********************************************/
   template<class T>
   typename set<T>::iterator set<T>::find(T t)
   {
      for (iterator it = begin(); it != end(); it++)
      {
         if (*(it) == t)
            return it;
      }

      return end();
   }

/********************************************
* SET ITERATOR :: ERASE
* Note that you have to use "typename" before the return value type
********************************************/
   template<class T>
   typename set<T>::iterator set<T>::erase(iterator it)
   {
      int index = findIndex(*(it++));

      int a = 0;
      T *tempData = new T[numCapacity];

      for (int i = 0; i < numElements - 1; i++)
      {
         if (a == index)
         {
            ++a;
         }

         tempData[i] = data[a++];
      }

      reallocateData(numCapacity);
      for (int i = 0; i < numElements; i++)
      {
         data[i] = tempData[i];
      }

      delete[] tempData;
      numElements--;

      return it;
   }

/**********************************************
* SET : NON-DEFAULT CONSTRUCTOR
* Preallocate the deque to "capacity"
**********************************************/
   template<class T>
   set<T>::set(int numCapacity)
   {
      // allocate buffer for new array
      reallocateData(numCapacity);
      // assign default values for set
      this->numCapacity = numCapacity;
      numElements = 0;
   }

/*******************************************
* SET :: COPY CONSTRUCTOR
*******************************************/
   template<class T>
   set<T>::set(const set<T> &rhs)
   {
      reallocateData(rhs.numCapacity);
      numCapacity = rhs.numCapacity;
      numElements = rhs.numElements;

      // copy the items over one at a time using the assignment operator
      for (int i = 0; i < numCapacity; i++)
         data[i] = rhs.data[i];
   }

/*******************************************
* SET :: OVERLOADED = OPERATOR
*******************************************/
   template<class T>
   set<T> &set<T>::operator=(const set<T> &rhs)
   {
      try
      {
         if (numCapacity < rhs.numCapacity)
         {
            resize(rhs.numCapacity);
         }

         for (int i = 0; i < this->numElements; ++i)
         {
            this->data[i] = rhs.data[i];
         }

         numElements = rhs.numElements;

         return *this;
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for set";
      }
   }

/*******************************************
* SET :: OVERLOADED && OPERATOR
*******************************************/
   template<class T>
   set<T> set<T>::operator&&(const set &rhs)
   {
      set<T> tempSet(1);

      for (int i = 0; i < rhs.numElements - 1; i++)
      {
         iterator it = find(rhs.data[i]);

         if (it == end())
         {
            continue;
         }

         tempSet.insert(rhs.data[i]);
      }

      return tempSet;
   }

/*******************************************
* SET :: OVERLOADED || OPERATOR
*******************************************/
   template<class T>
   set<T> set<T>::operator||(const set &rhs)
   {
      set<T> tempSet(1);

      tempSet = *this;

      for (int i = 0; i < rhs.numElements; i++)
      {
         tempSet.insert(rhs.data[i]);
      }

      return tempSet;
   }

/*******************************************
* SET :: INSERT
*******************************************/
   template<class T>
   void set<T>::insert(T t)
   {
      int index = findIndex(t);

      if (index >= 0)
      {
         return;
      }

      //reverse compliment
      index = -1 + -index;

      if (numCapacity == numElements)
      {
         resize(numCapacity * 2);
      }

      int a = 0;
      T *tempData = new T[numCapacity];

      // copy the data
      for (int i = 0; i < numElements; i++)
         tempData[i] = data[i];

      for (int i = 0; i < numElements + 1; i++)
      {
         if (index == i)
         {
            data[i] = t;
         } else
         {
            data[i] = tempData[a++];
         }
      }

      delete[] tempData;
      numElements++;
   }

/*******************************************
* SET :: FINDINDEX
*******************************************/
   template<class T>
   const int set<T>::findIndex(const T t)
   {
      int iFirst = 0;
      int iLast = numElements - 1;

      while (iFirst <= iLast)
      {
         int iMiddle = (iFirst + iLast) / 2;

         if (data[iMiddle] == t)
            return iMiddle;
         if (data[iMiddle] > t)
            iLast = iMiddle - 1;
         else
            iFirst = iMiddle + 1;
      }

      return -1 - iFirst; // not found! Return two's compliment
   }

/*******************************************
* SET :: REALLOCATEARRAY
*  Used to reduce the number of times this is written
*******************************************/
   template<class T>
   void set<T>::reallocateData(int numCapacity)
   {
      try
      {
         data = new T[numCapacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for set";
      }
   }

} //namespace custom
#endif //CS235_SET_H