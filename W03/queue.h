/***********************************************************************
 * Header:
 *    Queue
 * Summary:
 *    This class contains the notion of an queue. This acts like the
 *    standard library queue class and is generic, meaning it accepts
 *    any data-type. (First In, First Out)
 *
 *    This will contain the class definition of:
 *       queue             : similar to std::queue
 * Author
 *    Coby Jenkins
 *    Michael Gibson
 ************************************************************************/

#ifndef CS235_QUEUE_H
#define CS235_QUEUE_H

#include <cstddef> // allows NULL
#include <new> // allows bad_alloc
#include <cassert>

namespace custom
{
/************************************************
* QUEUE
* A data structure designed to operate first in
* first out (FIFO). Elements are inserted in the
* rear and get removed from the front. Elements on
* both ends of the structure can be manipulated. Elements
* between the front and back cannot be touched. The only
* element that can be removed is the front.
***********************************************/
template <class T>
class queue
{
private:
   T * data;
   int numPush;
   int numPop;
   int numCapacity;

   void resize(int newCapacity);
   int iHead() const { return numPop % numCapacity;}
   int iTail() const { return (numPush - 1) % numCapacity;}

public:
   // constructors and destructors
   queue(): numCapacity(0), numPop(0), numPush(0), data(NULL){};
   queue(int numCapacity);
   queue(const queue <T> & rhs);
   ~queue()
   {
      data = NULL;
      delete []data;
   }

   // assignment operator
   queue & operator = (const queue & rhs);

   // standard container interfaces
   bool empty() const { return size() == 0;}
   int size() const { return numPush - numPop;}
   void clear() {numPop = 0; numPush = 0;}
   int capacity() const { return numCapacity;}
   void push(const T &t);
   void pop() {if (!empty ()) numPop++;}
   T & front();
   T & front() const;
   T & back();
   T & back() const;
};


/********************************************
* QUEUE :: PUSH
* pushes an element into the last position in
* the queue. Determines if the capacity allows
* for the additional data. 
********************************************/
template <class T>
void queue <T> :: push (const T &t)
   {
      // does the capacity allow for additional data?
      if(this->numCapacity == 0)
         resize(1);

      if(this->size() == this->numCapacity)
         resize(this->numCapacity*2);

      // adds the data to the array
      numPush++;
      data[iTail()] = t;
   }

/********************************************
* QUEUE :: FRONT
* accesses the first element in the queue
* read/write capable
********************************************/
template <class T>
T & queue <T> :: front ()
   {
      if(empty ())
         throw "ERROR: attempting to access an element in an empty queue";
      else
         return data[iHead()];
   }

/********************************************
* QUEUE :: FRONT CONSTANT
* accesses the first element in the queue
* read only.
********************************************/
template <class T>
T & queue <T> :: front () const
{
   if(empty ())
      throw "ERROR: attempting to access an element in an empty queue";
   else
      return data[iHead()];
}

/********************************************
* QUEUE :: BACK
* accesses the last element in the queue
* read/write capable
********************************************/
template <class T>
T & queue <T> :: back ()
   {
      if(empty ())
         throw "ERROR: attempting to access an element in an empty queue";
      else
         return data[iTail()];
   }

/********************************************
* QUEUE :: BACK CONSTANT
* accesses the last element in the queue
* read only.
********************************************/
template <class T>
T & queue <T> :: back () const
{
   if(empty ())
      throw "ERROR: attempting to access an element in an empty queue";
   else
      return data[iTail()];
}

/***************************************************
* QUEUE :: resize
* Increases the capacity of the data array
**************************************************/
template <class T>
void queue <T> :: resize(int newCapacity)
{
    // initialize temporary variables
    T * newData;
    int rhsNumPush = numPush;
    int rhsNumPop = numPop;

    // reset numPop and numPush for new array
    numPop = numPush = 0;

    // allocate memory for new array
    try
    {
       newData = new T[newCapacity];
    }
    catch (std::bad_alloc)
    {
       throw "ERROR: Unable to allocate a new buffer for queue";
    }

    // iterate through old queue to copy data to
    // temporary array
    for (int i = rhsNumPop; i < rhsNumPush; ++i)
    {
       newData[numPush] = data[i % numCapacity];
       numPush++;
    }

    // delete information from old and move new data
    // to data and set numCapacity to match new buffer.
    delete []data;
    data = newData;
    numCapacity = newCapacity;
}

/*******************************************
* QUEUE :: Assignment
* copies one queue to another queue. determines
* and sets buffer requirements. moves data into
* the new queue starting in position [0].
*******************************************/
   template <class T>
   queue <T> & queue <T> ::operator=(const custom::queue<T> &rhs)
   {
      this->numPush = 0;
      this->numPop = 0;

      if(rhs.capacity() == 0)
      {
         this->numCapacity = 0;
         this->data = NULL;
         return *this;
      }

      try
      {
         this->data = new T[rhs.size()];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for queue";
      }

      if(this->capacity() < rhs.size())
      {
         this->resize(rhs.size());
      }

      for (int i = rhs.numPop; i < rhs.numPush; ++i)
      {
         this->push(rhs.data[i % rhs.numCapacity]);
      }

      return *this;
   }

/*******************************************
* QUEUE :: COPY CONSTRUCTOR
* Creates a new queue as a copy of an old queue.
* determines buffer size requirements, moves data
* into new queue starting in position [0]
*******************************************/
   template <class T>
   queue <T>::queue(const custom::queue<T> &rhs)
   {
      this->numPush = 0;
      this->numPop = 0;

      if(rhs.capacity() == 0)
      {
         this->numCapacity = 0;
         this->data = NULL;
      }

      try
      {
         this->data = new T[rhs.size()];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for queue";
      }

      if(this->capacity() < rhs.size())
      {
         this->resize(rhs.size());
      }

      for (int i = rhs.numPop; i < rhs.numPush; ++i)
      {
         this->push(rhs.data[i % rhs.numCapacity]);
      }
   }

/**********************************************
* QUEUE : NON-DEFAULT CONSTRUCTOR
* Preallocate the queue to "capacity"
**********************************************/
   template <class T>
   queue <T>::queue(int numCapacity)
   {
      try
      {
         this->data = new T[numCapacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for queue";
      }

      this->numCapacity = numCapacity;
      this->numPop = 0;
      this->numPush = 0;
   }


}; //namespace custom
#endif //CS235_QUEUE_H