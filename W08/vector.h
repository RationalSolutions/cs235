/***********************************************************************
 * Header:
 *    Vector
 * Summary:
 *    This class contains the notion of a vector: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *       array             : similar to std::array
 *       array :: iterator : an iterator through the array
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef CS235_VECTOR_H
#define CS235_VECTOR_H

// a little helper macro to write debug code
#ifdef NDEBUG
#define Debug(statement)
#else
#define Debug(statement) statement
#endif // !NDEBUG

namespace custom{


/************************************************
* VECTOR
* A class that holds stuff
***********************************************/
   template <class T>
   class vector
   {
   private:
      T * data;
      int numElements;
      int numCapacity;

      void resize(int newCapacity);
      bool inBounds(int index) const {return ((index >= 0) && (index <= size()-1));}

   public:
      // constructors and destructors
      vector(): numElements(0), numCapacity(0) {data = NULL;}
      vector(int size) ;
      vector(const vector <T> & rhs) ;
      ~vector()
      {
         data = NULL;
         delete []data;
      }
      vector & operator = (const vector & rhs);

      // standard container interfaces
      int size() const { return numElements;}
      int capacity() const { return numCapacity;}
      bool empty() const { return numElements == 0;}
      void clear() {numElements = 0;}
      void push_back(const T & t) ;

      T & operator [] (int index)
      {
         if (!inBounds(index))
         {
            throw "ERROR: Invalid index";
         }

         return data[index];
      }
      const T & operator [] (int index) const
      {
         if (!inBounds(index))
         {
            throw "ERROR: Invalid index";
         }

         return data[index];
      }


      class iterator;
      iterator begin();
      iterator end();

      class const_iterator;
      const_iterator cbegin() const;
      const_iterator cend()   const;

      // a debug utility to display the array
      // this gets compiled to nothing if NDEBUG is defined
      void display() const;
   };

/**************************************************
* VECTOR ITERATOR
* An iterator through a vector
*************************************************/
   template <class T>
   class vector <T> :: iterator
   {
   private:
      T * p;

   public:
      iterator()      : p(NULL)      {              }
      iterator(T * p) : p(p)         {              }
      iterator(const iterator & rhs) { *this = rhs; }
      iterator & operator = (const iterator & rhs)
      {
         this->p = rhs.p;
         return *this;
      }

      // equals, not equals operator
      bool operator != (const iterator & rhs) const { return rhs.p != this->p; }
      bool operator == (const iterator & rhs) const { return rhs.p == this->p; }

      // dereference operator
            T & operator * ()       { return *p; }
      const T & operator * () const { return *p; }

      // prefix increment
      iterator & operator ++ ()
      {
         p++;
         return *this;
      }

      // postfix increment
      iterator operator ++ (int postfix)
      {
         iterator tmp(*this);
         p++;
         return tmp;
      }
   };

/**************************************************
* VECTOR CONST_ITERATOR
* An iterator through a vector
*************************************************/
   template <class T>
   class vector <T> :: const_iterator
   {
   private:
      T * p;

   public:
      // constructors, destructors, and assignment operator
      const_iterator()      : p(NULL)      {              }
      const_iterator(T * p) : p(p)         {              }
      const_iterator(const const_iterator & rhs) { *this = rhs; }
      const_iterator & operator = (const const_iterator & rhs)
      {
         this->p = rhs.p;
         return *this;
      }

      // equals, not equals operator
      bool operator != (const const_iterator & rhs) const { return rhs.p != this->p; }
      bool operator == (const const_iterator & rhs) const { return rhs.p == this->p; }

      // dereference operator
      const T & operator * () const { return *p; }

      // prefix increment
      const_iterator & operator ++ ()
      {
         p++;
         return *this;
      }

      // postfix increment
      const_iterator operator ++ (int postfix)
      {
         const_iterator tmp(*this);
         p++;
         return tmp;
      }

   };

/********************************************
* VECTOR :: PUSH_BACK
* inserts an element in the collection and doubles the object`s capacity when necessary.
********************************************/
   template <class T>
   void vector <T> :: push_back(const T &t)  
   {
      if(this->numCapacity == 0)
         resize(1);

      if(this->numElements == this->numCapacity)
         resize(this->numCapacity*2);

      data[numElements++] = t;
   }

/*******************************************
* VECTOR :: Assignment
*******************************************/
   template <class T>
   vector <T> & vector <T> ::operator=(const custom::vector<T> &rhs) 
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
         throw "ERROR: Unable to allocate a new buffer for vector";
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

/***************************************************
* Vector :: resize
* Increases the capacity of the data array
**************************************************/
   template <class T>
   void vector <T>::resize(int newCapacity)
   {
      T * newData;

      try
      {
         newData = new T[newCapacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for vector";
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
* Vector :: COPY CONSTRUCTOR
*******************************************/
   template <class T>
   vector <T>::vector(const custom::vector<T> &rhs) 
   {
      if(rhs.capacity() == 0)
      {
         this->numElements = 0;
         this->numCapacity = 0;
         this->data = NULL;
         return;
      }

      try
      {
         this->data = new T[rhs.capacity()];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for vector";
      }

      this->numElements = rhs.size();
      this->numCapacity = rhs.capacity();

      for (int i = 0; i < this->size(); ++i)
      {
         this->data[i] = rhs.data[i];
      }
   }

/**********************************************
* VECTOR : NON-DEFAULT CONSTRUCTOR
* Preallocate the vector to "capacity"
**********************************************/
   template <class T>
   vector <T>::vector(int numElements)
   {
      try
      {
         this->data = new T[numElements];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for vector";
      }

      this->numElements = numElements;
      this->numCapacity = numElements;
   }

/********************************************
 * VECTOR : DISPLAY
 * A debug utility to display the contents of the array
 *******************************************/
   template <class T>
   void vector <T> :: display() const
   {
#ifndef NDEBUG
      std::cerr << "vector<T>::display()\n";
      std::cerr << "\tnumElements = " << size() << "\n";
      for (int i = 0; i < size(); i++)
         std::cerr << "\tdata[" << i << "] = " << data[i] << "\n";
#endif // NDEBUG
   }

/********************************************
* VECTOR :: END
* Note that you have to use "typename" before the return value type
********************************************/
   template <class T>
   typename vector <T> :: iterator vector <T> :: end()
   {
      return iterator(data + numElements);
   }

/********************************************
* VECTOR :: BEGIN
* Note that you have to use "typename" before the return value type
********************************************/
   template <class T>
   typename vector <T> :: iterator vector <T> :: begin()
   {
      return iterator (data);
   }

/********************************************
* VECTOR :: CBEGIN
* Note that you have to use "typename" before the return value type
********************************************/
   template <class T>
   typename vector <T> :: const_iterator vector <T> :: cbegin() const
   {
      return const_iterator(data);
   }

/********************************************
* VECTOR :: CEND
* Note that you have to use "typename" before the return value type
********************************************/
   template <class T>
   typename vector <T> :: const_iterator vector <T> :: cend() const
   {
      return const_iterator(data + numElements);
   }
};
#endif //CS235_VECTOR_H
