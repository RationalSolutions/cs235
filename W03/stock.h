/***********************************************************************
 * Header:
 *    STOCK
 * Summary:
 *    This will contain just the prototype for stocksBuySell(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Coby Jenkins
 *    Michael Gibson
 ************************************************************************/

#ifndef STOCK_H
#define STOCK_H

#include "dollars.h"   // for Dollars defined in StockTransaction
#include "queue.h"     // for QUEUE
#include "portfolio.h" // for PORTFOLIO
#include <iostream>    // for ISTREAM and OSTREAM

using namespace std;

// the interactive stock buy/sell function
void stocksBuySell();

// additional support functions for guiding workflow
int getAction(const string option);
void unrecognized(const string response);

#endif // STOCK_H

