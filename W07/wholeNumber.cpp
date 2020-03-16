/***********************************************************************
 * Implementation:
 *    WholeNumber
 * Summary:
 *    Contain the implementation for the WholeNumber class
 * Author
 *    Coby Jenkins
 *    Michael Gibson
 **********************************************************************/

#include "wholeNumber.h"

/***********************************************************************
 * operator =
 * Assignment operator
 ***********************************************************************/
WholeNumber & WholeNumber::operator=(const WholeNumber & rhs)
{
   periods = rhs.periods;
   return *this;
}

/***********************************************************************
 * operator +=
 * Add and assign the sum
 ***********************************************************************/
WholeNumber & WholeNumber::operator+=(WholeNumber & rhs)
{
    list<int>::reverse_iterator it = periods.rbegin(); //reverse iteration through current number list
    list<int>::reverse_iterator itRhs = rhs.periods.rbegin(); //reverse iteration through numbers to add
    list<int> completeNumber; //hold the sum of numbers

    int c = 0; //carry over for the summation
    int l = 0; //left hand side value
    int r = 0; //right hand side value
    int t = 0; //total of the l & r values
    int v = c + l + r; // value of the carry, left & right used to determine new total and carry

    while((it != periods.rend()) || (itRhs != rhs.periods.rend())) //reverse iterates until end
    {
       if(it != periods.rend()) //sets left hand value for addition
       {
          l = *it;
          it++;
       }else //if tis is the end set to 0
       {
          l = 0;
       }

       if(itRhs != rhs.periods.rend()) //sets right hand value for addition
       {
          r = *itRhs;
          itRhs++;
       }else //if tis is the end set to 0
       {
          r = 0;
       }

       v = c + l + r; //this is adding all the values to figure out carry & total
       t = v % 1000; //ensures that values are no more than 3 digits long
       c = v / 1000; //determines new carry value

       completeNumber.push_front(t); //builds the sum pushing values to the right
    }

    if(c > 0)
    {
       completeNumber.push_front(c);
    }

    periods = completeNumber;
   return *this;
}