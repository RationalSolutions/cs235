/***********************************************************************
 * Header:
 *    Deque
 * Summary:
 *    This class contains the notion of an deque. This acts like the
 *    standard library deque class and is generic, meaning it accepts
 *    any data-type. New data can be pushed or popped
 *    from either side as well. However, the elements between the
 *    first and last element cannot be touched. The order of these
 *    elements are maintained.
 *
 *    This will contain the class definition of:
 *       deque             : similar to std::deque
 * Author
 *    Coby Jenkins
 *    Michael Gibson
 ************************************************************************/

#ifndef CS235_DEQUE_H
#define CS235_DEQUE_H

#include <cstddef> // allows NULL
#include <new> // allows bad_alloc
#include <cassert>

namespace custom
{
/************************************************
* DEQUE
* A data structure that is a sequence containter
* that can be expanded or contracted on either
* end. Elements are inserted or removed from the
* rear or from the front. Both ends of the structure
* may be manipulated. However, elements between
* the front and rear elements may not be touched.
***********************************************/
template <class T>
class deque
{
private:
   T * data;
   int iFront;
   int iBack;
   int numCapacity;

   void resize(int newCapacity);
   int capacity() const { return numCapacity; }
   int iFrontNormalize() const { return iNormalize(iFront); }
   int iBackNormalize() const { return iNormalize(iBack); }
   int iNormalize(const int i) const;

public:
   // constructors and destructors
   deque(): numCapacity(0), iFront(0), iBack(-1), data(0){};
   deque(int numCapacity);
   deque(const deque <T> & rhs);
   ~deque()
   {
      data = NULL;
      delete []data;
   }

   // assignment operator
   deque & operator = (const deque & rhs);

   // standard container interfaces
   bool empty() const { return (size() == 0); }
   int size() const { return (iBack - iFront) + 1; }
   void clear() {iFront = 0; iBack = -1; }
   void push_front(T t);
   void push_back(T t);
   void pop_front();
   void pop_back();
   T & front();
   T front() const;
   T & back();
   T back() const;

};

/********************************************
* DEQUE :: POP_FRONT
* removes an element from the back of the array
********************************************/
template <class T>
void deque <T> ::pop_front()
   {
      if(empty())
      {
         return;
      }

      iFront++;
   }

/********************************************
* DEQUE :: POP_BACK
* removes an element from the back of the array
********************************************/
template <class T>
void deque <T> ::pop_back()
   {
      if(empty())
      {
         return;
      }

      iBack--;
   }

/********************************************
* DEQUE :: INORMALIZE
* Takes an index parameter and normalizes it
* to return an normalized index, meaning a
* number equal to or greater than zero and less
* than the capacity of the array.
********************************************/
template <class T>
int deque <T> :: iNormalize(const int i) const
{
   // we determined to use this algorithm to bring
   // the number to positive before applying mod
   int iTemp = i; 
   while(iTemp < 0){
      iTemp += capacity();
   }
   return iTemp % capacity();
   // this algorithm does the same thing only in
   // a different way.
   /*
   return ((i % capacity()) + capacity()) % capacity();
   */
}

/********************************************
* DEQUE :: PUSH_FRONT
* pushes an element before the first position in
* the deque. Determines if the capacity allows
* for the additional data. 
********************************************/
template <class T>
void deque <T> :: push_front (T t)
   {
      // does the capacity allow for additional data?
      if(size() == capacity())
      {
         resize(capacity() * 2);
      }

      // adds the data to the array
      iFront--;
      data[iFrontNormalize()] = t;
   }

/********************************************
* DEQUE :: PUSH_BACK
* pushes an element into the last position in
* the deque. Determines if the capacity allows
* for the additional data. 
********************************************/
template <class T>
void deque<T>::push_back(T t)
   {
      // does the capacity allow for additional data?
      if(size() == capacity())
      {
         resize(capacity() * 2);
      }

      // adds the data to the array
      iBack++;
      data[iBackNormalize()] = t;
   }

/********************************************
* DEQUE :: FRONT (pass by ref)
* accesses the first element in the deque
* read/write capable
********************************************/
template <class T>
T & deque<T>::front()
   {
      if(empty ())
      {
         throw "ERROR: unable to access data from an empty deque";
      }

      return data[iFrontNormalize()];
   }

/********************************************
* DEQUE :: FRONT CONSTANT (pass by value)
* accesses the first element in the deque
* read only.
********************************************/
template <class T>
T deque <T>::front() const
   {
      if(empty ())
      {
         throw "ERROR: unable to access data from an empty deque";
      }

      return data[iFrontNormalize()];
   }

/********************************************
* DEQUE :: BACK (pass by ref)
* accesses the last element in the deque
* read/write capable
********************************************/
template <class T>
T & deque <T> :: back ()
   {
      if(empty ())
         throw "ERROR: unable to access data from an empty deque";
      else
         return data[iBackNormalize()];
   }

/********************************************
* DEQUE :: BACK CONSTANT (pass by value)
* accesses the last element in the deque
* read only.
********************************************/
template <class T>
T deque <T> :: back () const
{
   if(empty ())
      throw "ERROR: unable to access data from an empty deque";
   else
      return data[iBackNormalize()];
}

/***************************************************
* DEQUE :: resize
* Increases the capacity of the deque array
**************************************************/
template <class T>
void deque <T> :: resize(int newCapacity)
{
   if (newCapacity == 0)
   {
      numCapacity = ++newCapacity;
      data = new T[numCapacity];
      return;
   }

   // allocate memory for new array
   T* newData;
   try
   {
      newData = new T[newCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for deque";
   }

   // copy the data
   int dest = 0;
   for (int source = iFront; source <= iBack; source++)
      newData[dest++] = data[iNormalize(source)];

   // set the new capacity, iBack, and iFront
   numCapacity = newCapacity;
   iFront = 0;
   iBack = dest - 1;
   
   // delete information from old and move new data
   delete []data;
   data = newData;
}

/*******************************************
* DEQUE :: Assignment
* copies one deque to another deque. determines
* and sets buffer requirements. moves data into
* the new deque starting in position [0].
*******************************************/
   template <class T>
   deque <T> & deque <T>::operator=(const deque &rhs)
   {
      try
      {
         // delete existing data 
         clear();

         // check capacity
         if(this->capacity() < rhs.size())
         {
            resize(rhs.size());
         }

         // copy rhs data into lhs
         for (int i = rhs.iFront; i <= rhs.iBack; i++)
         {
            this->push_back(rhs.data[iNormalize(i)]);
         }

         return *this;

      // if there is an error allocating a new buffer
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for deque";
      }
   }

/*******************************************
* DEQUE :: COPY CONSTRUCTOR
* Creates a new deque as a copy of an old deque.
* determines buffer size requirements, moves data
* into new deque starting in position [0]
*******************************************/
   template <class T>
   deque <T>::deque(const custom::deque<T> &rhs)
   {
      // set first and last position variables
      this->iFront = 0;
      this->iBack = -1;
      
      // if we're copying an empty deque, we're done
      if(rhs.capacity() == 0)
      {
         this->numCapacity = 0;
         this->data = NULL;
      }

      // allocate the buffer for the new array
      try
      {
         this->data = new T[rhs.capacity()];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for deque";
      }

      // copy array data to the new array
      if(this->capacity() < rhs.size())
      {
         this->resize(rhs.size());
      }

      this->numCapacity = rhs.numCapacity;

      for (int i = rhs.iFront; i <= rhs.iBack; i++)
      {
         this->push_back(rhs.data[iNormalize(i)]);
      }
   }

/**********************************************
* DEQUE : NON-DEFAULT CONSTRUCTOR
* Preallocate the deque to "capacity"
**********************************************/
   template <class T>
   deque <T>::deque(int numCapacity)
   {
      // allocate buffer for new array
      try
      {
         this->data = new T[numCapacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for deque ";
      }
      
      // establish deque variables ready for data
      this->numCapacity = numCapacity;
      this->iFront = 0;
      this->iBack = -1;
   }


}; //namespace custom
#endif //CS235_DEQUE_H
