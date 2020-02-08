/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    <your names here>
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include "set.h"
#include "card.h"
#include "goFish.h"
#include <fstream>
#include <sstream>

using namespace std;
using namespace custom;

/**********************************************************************
* LOADHAND
* Takes a string for the file path/name and then loads a set based on the
* elements in the first line.
***********************************************************************/
set<Card> loadHand(string file)
{
   set<Card> handSet;
   ifstream hand(file);

   string line;
   getline(hand, line);
   stringstream ss(line);

   do
   {
      char cardName[256];
      ss >> cardName;
      Card card(cardName);
      handSet.insert(card);
   }while (ss);

   return handSet;
}

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
   int matches = 0;
   string file = "/home/cs235/week05/hand.txt";
   set<Card> hand = loadHand(file);

   cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand\n";

   for (int i = 0; i < 5; i++)
   {
      char userInput[265];
      int round = i + 1;

      cout << "round " << round << ": ";

      cin >> userInput;

      set<Card>::iterator it = hand.find(Card(userInput));

      if(it == hand.end())
         cout << "\tGo Fish!" << endl;
      else
      {
         cout << "\tYou got a match!" << endl;
         hand.erase(it);
         matches++;
      }
   }

   cout << "You have " << matches << " matches!" << endl;
   cout << "The remaining cards: ";

   int a = hand.size();
   set<Card>::iterator it;
   int b = 0;

   for (it = hand.begin(); it != hand.end(); ++it)
   {
      cout << *it;
      b++;
      if (b < a)
         cout << ", ";
   }
   cout << endl;

   return ;
}
