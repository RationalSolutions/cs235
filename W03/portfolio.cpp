//
// Created by coby on 1/25/2020.
//

#include "portfolio.h"  // for the class definition
#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
using namespace std;

/***********************************************************************
 * PORTFOLIO :: CONSTRUCTOR
 * default constructor
 ************************************************************************/
Portfolio::Portfolio()
{
   totalProfits = 0;
}

/***********************************************************************
 * PORTFOLIO :: DESTRUCTOR
 * default constructor
 ************************************************************************/
Portfolio::~Portfolio()
{}

/***********************************************************************
* PORTFOLIO :: BUY
* buys stocks as a transaction and adds it to the purchases queue
************************************************************************/
void Portfolio :: buy(int numShares, Dollars price)
{
   Transaction buy = Transaction(numShares, price, 0);
   purchases.push(buy);
}

/***********************************************************************
 * PORTFOLIO :: SELL
 * Sells stocks and updates the portfolio accordingly.
 ************************************************************************/
void Portfolio :: sell(int numShares, Dollars price)
{
   while ((numShares > 0) && (!purchases.empty()))
   {
      Transaction sale = purchases.front().sellShares(numShares, price);
      numShares -= sale.getShareCount();
      totalProfits += sale.getProfit();
      sales.push(sale);

      if (purchases.front().getShareCount() == 0)
         purchases.pop();
   }
}

/***********************************************************************
 * PORTFOLIO :: DISPLAY
 * Displays the portfolio and is only called by the overloaded insertion
 * operator.
 ************************************************************************/
void Portfolio :: display(ostream & out) const
{
   if (!purchases.empty())
   {
      out << "Currently held:\n";
      custom::queue <Transaction> p = purchases;

      while (!p.empty())
      {
         out << p.front();
         p.pop();
      }
   }

   if (!sales.empty())
   {
      out << "Sell History:\n";
      custom::queue<Transaction> s = sales;

      while (!s.empty())
      {
         out << s.front();
         s.pop();
      }

   }
   out << "Proceeds: " << totalProfits << endl;
}

/***********************************************************************
 * PORTFOLIO INSERTION OPERATOR
 * Allows data to be outputted to the screen without the std library. this
 * resolved some issues I was having with compiling
 ************************************************************************/
ostream & operator << (ostream & out, const Portfolio & rhs)
{
   rhs.display(out);
   return out;
}