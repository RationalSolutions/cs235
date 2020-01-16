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
   void push(T t);
   void pop();
   T & top();
   T top() const;
};

/********************************************
* STACK :: PUSH
* inserts an element in the collection and doubles the object`s capacity when necessary.
********************************************/

}; //namespace custom
#endif //CS235_STACK_H
