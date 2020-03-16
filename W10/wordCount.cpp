/***********************************************************************
 * Module:
 *    Week 10, WORD COUNT
 *    Brother Helfrich, CS 235
 * Author:
 *    Coby Jenkins
 *    Michael Gibson
 * Summary:
 *    This program will implement the wordCount() function
 ************************************************************************/

#include <string>
#include <fstream>
#include <iostream>
#include "map.h"       // for MAP
#include "wordCount.h" // for wordCount() prototype
using namespace std;
using namespace custom;

/***************************************************
 * readFile() : Read the file and store into map
 **************************************************/
void readFile(map <string, int> & counts, const string & fileName)
{
   string words;

   ifstream fin;
   fin.open(fileName);

   if (fin.fail())
   {
      cout << "Unable to open the file" << endl;
      return;
   }

   while (fin >> words)
   {
      counts[words]++;

   }
}

/*****************************************************
 * WORD COUNT
 * Prompt the user for a file to read, then prompt the
 * user for words to get the count from
 *****************************************************/
void wordCount()
{
   map <string, int> counts;
   string fileName;
   string userInput;

   cout << "What is the filename to be counted? ";
   cin >> fileName;

   readFile(counts, fileName);

   cout << "What word whose frequency is to be found. Type ! when done" << endl;
   cout << "> ";
   cin >> userInput;

   while (userInput != "!")
   {
      cout << "\t" << userInput << " : " << counts[userInput] << endl;
      cout << "> ";
      cin >> userInput;
   }

}
