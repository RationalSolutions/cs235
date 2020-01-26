/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include <sstream>     // for STRINGSTREAM
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
using namespace std;

/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   // declare variables
   string response;
   string option;
   int shares;
   Dollars price;
   Portfolio book;
   int action;

   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   // A while loop that allows for multiple responses until client enters quit
   while(response != "quit"){
      cout << "> ";
      cin.ignore();
      getline(cin, response);

      stringstream ss;
      ss.str(response);

      ss >> option;

      action = getAction(option);

      switch(action)
      {
         case 1:
            ss >> shares >> price;
            book.buy(shares, price);
            break;
         case 2:
            ss >> shares >> price;
            book.sell(shares, price);
            break;
         case 3:
            cout << book;
            break;
         default:
            unrecognized(response);
      }

   }
}

/*************************************************************
 * getAction
 * based on the first word in user command, returns 1, 2, or 3
 * which is used to determine whether to buy, sell, or display
 * respectively.
 ************************************************************/
int getAction(const string option)
{
   if(option == "buy" || option == "Buy"){
      return 1;
   }
   else if(option == "sell" || option == "Sell"){
      return 2;
   }
   else if(option == "display" || option == "Display"){
      return 3;
   }

   return 0;
}

/************************************************************
 * Unrecognized
 * the response from the user was not a valid option.
 ***********************************************************/
void unrecognized(const string response)
{
   if(response[0] == 'q' || response[0] =='Q'){
      return;
   } else
   {
      cout << "\"" << response << "\"" 
           << " is not a valid command.\n";
   }

   return;
}
