/***********************************************************************
 * Module:
 *    Assignment 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "spellCheck.h"
#include "hash.h"
#include "list.h"
using namespace std;
using namespace custom;
/*****************************************
* S HASH : simple hash of strings
******************************************/
class sHash : public Hash<string>
{
public:
   sHash(int bucketSize) : Hash<string>(bucketSize) {}
   sHash(const sHash & rhs) : Hash<string>(rhs) {}

   int hash(const string & value) const
   {
      int sum = 0;
      for (const char * w = value.c_str(); *w ; w++)
      {
         sum += *w;
      }

      return sum % this->capacity();
   }
};

/*****************************************************
* TO LOWER : takes a string and sets all chars to lower case
******************************************************/
string stringToLower(string & word)
{
   for(string::iterator iterator = word.begin(); iterator != word.end(); ++iterator)
   {
      *iterator = tolower(*iterator);
   }

   return word;
}

/*****************************************************
* POPULATE DICTIONARY HASH : reads the dictionary file and populates the hash
******************************************************/
void populateDictionaryHash(sHash & sHash)
{
   string word;
   ifstream fin;

   fin.open("/home/cs235/week12/dictionary.txt");
   if(fin.fail())
   {
      cout << "Unable to open dictionary file." << endl;
      return;
   }

   while (fin >> word)
   {
      sHash.insert(word);
   }

   fin.close();
}

/*****************************************************
* READ FILE : reads the file and determines spelling errors
******************************************************/
void readFile(string & fileName, sHash dictionaryHash)
{
   string word;
   list<string> misspelledWords;
   ifstream fin;

   fin.open(fileName);
   if(fin.fail())
   {
      cout << "Unable to open file." << endl;
      return;
   }

   while (fin >> word)
   {
      string tempString = word;
      if(!(dictionaryHash.find(stringToLower(tempString))))
         misspelledWords.push_back(word);
   }

   if(misspelledWords.empty())
   {
      cout << "File contains no spelling errors" << endl;
   } else
   {
      cout << "Misspelled: ";
      for (custom::list<string>::iterator iterator = misspelledWords.begin();
      iterator != misspelledWords.end(); ++iterator)
      {
         cout << (iterator == misspelledWords.begin() ? "" : ", ");
         cout << *iterator;
      }

      cout << endl;
   }

}

/*****************************************
* SPELL CHECK : Prompt the user for a file to spell-check
*****************************************/
void spellCheck()
{
   string fileName;
   sHash dictionaryHash(3000);
   populateDictionaryHash(dictionaryHash);

   cout << "What file do you want to check? ";
   cin >> fileName;
   readFile(fileName, dictionaryHash);

}
