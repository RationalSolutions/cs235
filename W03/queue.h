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

#include <cassert>

namespace custom
{
/************************************************
* QUEUE
* A class that holds stuff, first in first out
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
   queue(): numCapacity(0), numPop(0), numPush(0) {data = NULL;}
   queue(int numCapacity);
   queue(const queue <T> & rhs);
   ~queue()
   {
      data = NULL;
      delete []data;
   }
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
* inserts an element in the collection and doubles the object`s 
* capacity when necessary.
********************************************/
template <class T>
void queue <T> :: push (const T &t)
   {
      if(this->numCapacity == 0)
         resize(1);

      if(this->size() == this->numCapacity)
         resize(this->numCapacity*2);

      numPush++;
      data[iTail()] = t;
   }

/********************************************
* QUEUE :: FRONT
* accesses the top element on the queue
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
* accesses the top element on the queue
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
* accesses the top element on the queue
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
* accesses the top element on the queue
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
   T * newData;

   try
   {
      newData = new T[newCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for queue";
   }

   for (int i = numPop; i < numPush; ++i)
   {
      newData[i % numCapacity] = data[i % numCapacity];
   }

   delete []data;
   data = newData;
   numCapacity = newCapacity;
}

/*******************************************
* QUEUE :: Assignment
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