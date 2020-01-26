//
// Created by coby on 1/25/2020.
//

#include "transaction.h"
#include <iostream>        // for ISTREAM, OSTREAM, CIN, and COUT
using namespace std;

/***********************************************************************
 * TRANSACTION :: CONSTRUCTOR
 * Creates a transaction that is either buying or selling based on the value
 * of the buy/sale value and the sold boolean value
 ************************************************************************/
Transaction::Transaction(int shareCount, Dollars buyPrice, Dollars salePrice)
{
   this->shareCount = shareCount;
   this->buyPrice = buyPrice;
   this->salePrice = salePrice;

   if(salePrice > 0)
      this->sold = true;
   else
      this->sold = false;
}

/***********************************************************************
 * TRANSACTION :: SELL SHARES
 * sells a number of shares from the transaction thus reducing the shares
 * available to sell in the future.
 ************************************************************************/
Transaction Transaction :: sellShares(int shareCount, Dollars salePrice)
{

   if (shareCount < 0)
      shareCount = 0;

   if (shareCount > this->shareCount)
      shareCount = this->shareCount;


   if (salePrice < 0)
      salePrice = 0;

   this->shareCount -= shareCount;

   Transaction saleTransaction(shareCount, this->buyPrice, salePrice);

   return saleTransaction;
}

/***********************************************************************
 * TRANSACTION :: GETPROFIT
 * If this was a sale, gets the profit, else gets 0
 ************************************************************************/
Dollars Transaction::getProfit() const
{
   if (sold)
      return (salePrice - buyPrice) * shareCount;
   else
      return Dollars(0);
}

/***********************************************************************
 * TRANSACTION :: DISPLAY
 * Displays the transaction as appropriate depending on whether it is
 * a sale or not also only called by overloaded operator
 ************************************************************************/
void Transaction :: display(ostream & out) const
{
   if (sold)
   {
      out << "\tSold " << shareCount << " shares at " << salePrice
          << " for a profit of " << getProfit() << endl;
   }
   else
   {
      out << "\tBought " << shareCount << " shares at " << buyPrice << endl;
   }
}

/***********************************************************************
 * OPERATOR << Transaction
 * Allows data to be outputted to the screen without the std library. this
 * resolved some issues I was having with compiling
************************************************************************/
ostream & operator << (ostream & out, const Transaction & rhs)
{
   rhs.display(out);
   return out;
}