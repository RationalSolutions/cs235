###############################################################
# Program:
#     Assignment 03, QUEUE
#     Brother Kirby, CS235
# Author:
#     Coby Jenkins
#     Michael Gibson
# Summary:
#     Using a custom queue data type, this program can be used
#     to track stock purchases and sales along with the associated
#     profit or loss. Queue is a template class able to take any
#     type of data.
# Time:
#     <how long did it take to complete this program>?
#     Implementation of the resize() function was tricky. This
#     was one of the elements of the project that did not have
#     significant information, which required us to determine 
#     the logic on our own. After struggling with the lgic for
#     a while, we took a break and as we were focused on other
#     things, the realization that the resize() was very similar
#     to copy, placing the first element at [0] again (numPop).
#
#     Coby: 6hrs
#       Struggled getting some compilation errors when I enabled the
#           portfolio class so I had to add some imports to the queue class.
#       Struggled with needing to overload the << operator on the transaction
#           class to get the display to work properly. ended up adding it to
#           the portfolio class as well just to be safe.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: queue.h assignment03.o dollars.o stock.o transaction.o portfolio.o
	g++ -o a.out assignment03.o dollars.o stock.o transaction.o portfolio.o
	tar -cf assignment03.tar *.h *.cpp makefile

dollarsTest: dollars.o dollarsTest.cpp
	g++ -o dollarsTest dollars.o dollarsTest.cpp

##############################################################
# The individual components
#      assignment03.o : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
#      transaction.o  : the logic for how a transaction works
#      portfolio.o    : the logic for the management of the portfolio
##############################################################
assignment03.o: queue.h assignment03.cpp
	g++ -c assignment03.cpp

dollars.o: dollars.h dollars.cpp
	g++ -c dollars.cpp

stock.o: stock.h stock.cpp queue.h
	g++ -c stock.cpp

transaction.o: transaction.h transaction.cpp dollars.h
	g++ -c transaction.cpp

portfolio.o: portfolio.h portfolio.cpp queue.h dollars.h transaction.h
	g++ -c portfolio.cpp
