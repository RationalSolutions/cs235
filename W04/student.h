/***********************************************************************
 * Header:
 *    Student
 * Summary:
 *    This class contains the definition of a student, which includes their
 *    name, the class they need help in, the time required for their
 *    help, and whether it is an emergency. It also includes an overloaded
 *    insertion operator, overloaded assignment operator and support methods.
 *
 * Author
 *    Coby Jenkins
 *    Michael Gibson
 ************************************************************************/

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
using namespace std;

/************************************************
* STUDENT
* A simple data type containing two strings and 
* an int ( student name, class number, and time
* in minutes). 
***********************************************/
class student
{
private:
   string name;
   string classNumber;
   int minutes;
   bool emergent;

public:
   // constructors and destructors
   student(): name(""), classNumber(""), minutes(0), emergent(false) {};
   student(string name, string classNumber, int minutes, bool emergent);
   student(const student & rhs);

   // assignment operator
   student & operator = (const student & rhs);
   
   // standard container interfaces
   int getTime() { return minutes; }
   string getName() { return name; }
   string getClassNumber() { return classNumber; }
   bool isEmergent() { return emergent; }
   void setName(string name) { this->name = name; }
   void setClassNumber(string classNumber) { this->classNumber = classNumber; }
   void setMinutes(int minutes) { this->minutes = minutes; }
   void setEmergent(bool emergent) { this->emergent = emergent; }

   void decrementTime();

};

ostream & operator << (ostream & out, student & rhs);

#endif //STUDENT_H
