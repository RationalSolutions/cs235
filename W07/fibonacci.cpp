/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    Coby Jenkins
 *    Michael Gibson
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
#include "wholeNumber.h"
using namespace std;


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;
   WholeNumber var1(0);
   WholeNumber var2(1);
   WholeNumber var3(1);


   int i = 0;
   while(i < number)
   {
      var3 = var1;
      var3 += var2;
      var1 = var2;
      var2 = var3;
      cout << "\t" << var1 << endl;
      i++;
   }


   i = 0;
   WholeNumber var4(0);
   WholeNumber var5(1);
   WholeNumber var6(1);


   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;
   // your code to display the <number>th Fibonacci number
   while(i < number)
   {
      var6 = var4;
      var6 += var5;
      var4 = var5;
      var5 = var6;
      i++;
   }
   cout << "\t" << var4 << endl;
}


