/********************************************************
 * STUDENT
 * Methods used by the student class
 * Author
 *    Coby Jenkins
 *    Michael Gibson
 ********************************************************/

#include "student.h"
#include <string>
#include <iostream>        // for ISTREAM, OSTREAM, CIN, and COUT

using namespace std;

/*****************************************************************
 * STUDENT - CONSTRUCTOR - non-default
 * creates a student object with all data
 *****************************************************************/
student :: student(string name, string classNumber, int minutes, bool emergent)
{
    this->name = name;
    this->classNumber = classNumber;
    this->minutes = minutes;
    this->emergent = emergent;
}

/*******************************************************************
 * STUDENT - COPY CONSTRUCTOR
 * copies elements from one student object to a new student object
 *******************************************************************/
student :: student(const student & rhs)
{
    this->name = rhs.name;
    this->classNumber = rhs.classNumber;
    this->minutes = rhs.minutes;
    this->emergent = rhs.emergent;
}

/******************************************************************
 * ASSIGNMENT
 * copies the right hand side student values to the left hand side student
 *******************************************************************/
student & student :: operator = (const student & rhs)
{
    this->name = rhs.name;
    this->classNumber = rhs.classNumber;
    this->minutes = rhs.minutes;
    this->emergent = rhs.emergent;

    return *this;
}

/****************************************************************
 * DECREMENTTIME
 * if minutes is greater than zero, decreases minutes by one.
 ***************************************************************/
void student :: decrementTime()
{
    if(minutes > 0){
       minutes--;
    }
}

/*****************************************************************
 * INSERTION
 * overload the insertion operator to work with a student object
 * different insertion based on whether it is an emergency.
 ****************************************************************/
 ostream & operator << (ostream & out, student & rhs)
 {
    if(rhs.isEmergent())
    {
        out << "\tEmergency for " << rhs.getName()
            << " for class " << rhs.getClassNumber()
            << ". Time left: " << rhs.getTime() << endl;
    }
    else
    {
        out << "\tCurrently serving " << rhs.getName()
            << " for class " << rhs.getClassNumber()
            << ". Time left: " << rhs.getTime() << endl;
    }
         
    return out;
 }