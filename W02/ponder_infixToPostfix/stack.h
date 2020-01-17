#ifndef CS235_STACK_H
#define CS235_STACK_H

namespace custom
{
/************************************************
* STACK
* A class that holds stuff
***********************************************/
template <class T>
class stack
{
private:
   T * data;
   int numElements;
   int numCapacity;

   void resize(int newCapacity);

public:
   // constructors and destructors
   stack(): numElements(0), numCapacity(0) {data = NULL;}
   stack(int size) ;
   stack(const stack <T> & rhs) ;
   ~stack()
   {
      data = NULL;
      delete []data;
   }
   stack & operator = (const stack & rhs);

   // standard container interfaces
   int size() const { return numElements;}
   int capacity() const { return numCapacity;}
   bool empty() const { return numElements == 0;}
   void clear() {numElements = 0;}
   void push(const T &t);
   void pop() {if (!empty ()) --numElements;}
   T & top();
   T top() const;
};

/********************************************
* STACK :: PUSH
* inserts an element in the collection and doubles the object`s capacity when necessary.
********************************************/
template <class T>
void stack <T> ::push (const T &t)
   {
      if(this->numCapacity == 0)
         resize(1);

      if(this->numElements == this->numCapacity)
         resize(this->numCapacity*2);

      data[numElements++] = t;
   }

/********************************************
* STACK :: TOP
* accesses the top element on the stack
********************************************/
template <class T>
T & stack ::top ()
   {
      if(empty ())
         throw " ERROR: Unable to reference the element from an empty stack";
      else
         return data[size () - 1];
   }

/********************************************
* STACK :: TOP CONSTANT
* accesses the top element on the stack
********************************************/
template <class T>
T stack :: top () const
{
   if(empty ())
      throw " ERROR: Unable to reference the element from an empty stack";
   else
      return data[size () - 1];
}
/***************************************************
* Vector :: resize
* Increases the capacity of the data array
**************************************************/
template <class T>
void stack <T> :: resize(int newCapacity)
{
   T * newData;

   try
   {
      newData = new T[newCapacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for stack";
   }

   for (int i = 0; i < numElements; ++i)
   {
      newData[i] = data[i];
   }

   delete []data;
   data = newData;
   numCapacity = newCapacity;
}

/*******************************************
* STACK :: Assignment
*******************************************/
   template <class T>
   stack <T> & stack <T> ::operator=(const custom::stack<T> &rhs)
   {
      this->numElements = 0;

      if(rhs.capacity() == 0)
      {
         this->numCapacity = 0;
         this->data = NULL;
         return *this;
      }

      try
      {
         this->data = new T[rhs.numCapacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for stack";
      }

      if(this->capacity() < rhs.numElements)
      {
         this->resize(rhs.numElements);
      }

      this->numElements = rhs.numElements;

      for (int i = 0; i < this->numElements; ++i)
      {
         this->data[i] = rhs.data[i];
      }

      return *this;
   }

}; //namespace custom
#endif //CS235_STACK_H
