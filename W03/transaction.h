//
// Created by coby on 1/25/2020.
//

#ifndef CS235_TRANSACTION_H
#define CS235_TRANSACTION_H

#include "dollars.h"       // for DOLLARS defined in StockTransaction
#include <iostream>        // for ISTREAM, OSTREAM, CIN, and COUT

class Transaction
{
private:
   int shareCount;    // number of shares in transaction
   bool  sold;        // if shares are sold set true
   Dollars buyPrice;  // amount shares were bought at
   Dollars salePrice; // amount shares were sold at

public:
   Transaction(): shareCount(0), sold(0), buyPrice(0), salePrice(0){};
   Transaction(int shareCount, Dollars buyPrice, Dollars salePrice);


   int getShareCount() const { return shareCount; } // Gets the count of remaining shares bought in this transaction;
   Dollars getSharePrice() const { return buyPrice; } // Get share price (share price can't be changed once set at creation time)
   Dollars getSoldPrice() const { return salePrice; } // Get sold price (sold price can't be changed once set)
   Dollars getProfit() const; // Gets the profit for this transaction
   Transaction sellShares(int in_sellCount, Dollars in_salePrice); // Sells a subset of the shares, reducing the share count by the amount old; returns the number of shares sold - in case a caller tries to sell more shares than available
   void display(std::ostream & out) const; // Displays the transaction had to overload the << operator to resolve some compilation issues
};

std::ostream & operator << (std::ostream & out, const Transaction & rhs);

#endif //CS235_TRANSACTION_H
