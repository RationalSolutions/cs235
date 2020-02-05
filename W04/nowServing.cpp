/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Coby Jenkins
 *    Michael Gibson
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <sstream>     // for STRINGSTREAM
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // declare variables
   string response;                   // users entry
   int time = 0;                      // simulated time starts at zero
   string first;
   string classNumber;
   string name;
   int minutes = 0;
   custom::deque <student> studentQ;  // line of students waiting
   student current;                   // current student being helped

   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here
   cin.ignore();

   cout << "<" << time << "> ";
   getline(cin, response);


   // run until the client enters "finished"
   while(response != "finished")
   {
      // "none" means there is no additional data to use.
      if(response != "none")
      {     
         stringstream ss;
         ss.str(response);

         ss >> first;

         // if the queue is empty and there is no one being helped
         // goes immediately to being served
         if(studentQ.empty() && current.getTime() == 0)
         {
            if(first == "!!")
            {
               ss >> classNumber >> name >> minutes;
               current.setEmergent(true);
               current.setClassNumber(classNumber);
               current.setName(name);
               current.setMinutes(minutes);
            }
            else
            {
               ss >> name >> minutes;
               current.setEmergent(false);
               current.setClassNumber(first);
               current.setName(name);
               current.setMinutes(minutes);
            }
         }
         else // when waiting for an open tutor
         {
            if(first == "!!") // emergency goes to head of line
            {
               ss >> classNumber >> name >> minutes;
               student tempStud(name, classNumber, minutes, true);
               studentQ.push_front(tempStud);   
            }
            else             // non-emergent goes to back of line
            {
               ss >> name >> minutes;
               student tempStud(name, first, minutes, false);
               studentQ.push_back(tempStud);
            }
         }
      }

      // update current student when previous student's time
      // has elapsed and if there are students in line.
      if(current.getTime() == 0 && !studentQ.empty())
      {
         current = studentQ.front();
         studentQ.pop_front();
      }

      // only display current student if time left has not reached zero
      if(current.getTime() != 0)
      {
         cout << current;
      }

      // advance one minute
      current.decrementTime();
      time++;

      // next minute
      cout << "<" << time << "> ";
      getline(cin, response);
   }
   // end
   cout << "End of simulation\n";
}


