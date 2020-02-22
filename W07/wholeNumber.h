/***********************************************************************
 * Implementation:
 *    WholeNumber
 * Summary:
 *    Contain the prototypes & implementation for the WholeNumber class
 * Author
 *    Coby Jenkins
 *    Michael Gibson
 **********************************************************************/

#ifndef CS235_WHOLENUMBER_H
#define CS235_WHOLENUMBER_H

#include <iomanip> //needed for commas and set spacing
#include "list.h"

class WholeNumber
{
private:
   list<int> periods; //list of ints upto 3 digits long. The digits between commas are called periods

public:
   //constructors / destructor
   WholeNumber();
   WholeNumber(int number) {periods.push_front(number);}
   ~WholeNumber(){}

   //overloaded operators
   WholeNumber &operator = (const WholeNumber & rhs);
   WholeNumber &operator += (WholeNumber & rhs);

   //friend allows the access of private members
   friend std::ostream & operator << (std::ostream & out, WholeNumber & rhs)
   {
      list<int>::iterator it;

      //goes through the list of periods and adds commas and fills in 0's where needed
      for (it = rhs.periods.begin(); it != rhs.periods.end() ; ++it)
      {
         if(it != rhs.periods.begin())
         {
            out << "," << std::setfill('0') << std::setw(3);
         }
         out << *it;
      }

      return out;
   }
};


#endif //CS235_WHOLENUMBER_H
