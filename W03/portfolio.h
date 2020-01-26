//
// Created by coby on 1/25/2020.
//

#ifndef CS235_PORTFOLIO_H
#define CS235_PORTFOLIO_H

#include "queue.h"         // for QUEUE
#include "transaction.h"   // for TRANSACTIONS
#include "dollars.h"       // for DOLLARS defined in StockTransaction
#include <iostream>        // for ISTREAM, OSTREAM, CIN, and COUT

class Portfolio
{

private:
   custom::queue <Transaction> purchases;
   custom::queue <Transaction> sales;
   Dollars totalProfits;

public:
   Portfolio();
   ~Portfolio();

   void buy(int numShares, Dollars price);
   void sell(int numShares, Dollars price);
   void display(std::ostream & out) const;
};

std::ostream & operator << (std::ostream & out, const Portfolio & rhs);

#endif //CS235_PORTFOLIO_H
