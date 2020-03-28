###############################################################
# Program:
#     Assignment 12, Hash
#     Brother Kirby, CS235
# Author:
#     Coby Jenkins
#     Michael Gibson
# Summary:
#     implement a hash using a custom list data structure to implement a spellCheck
# Time:
#     Coby Jenkins - I spent 10hrs implementing application. I spent 7 of
#                    those hours working out the spellCheck functions to work
#                    properly.
#     Michael Gibson - Spent 5 hours on the hash.h
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment12.o spellCheck.o
	g++ -o a.out assignment12.o spellCheck.o -g 
	tar -cf assignment12.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment12.o     : the driver program
#      spellCheck.o       : the spell-check program and driver
##############################################################
assignment12.o: hash.h assignment12.cpp list.h
	g++ -c assignment12.cpp

spellCheck.o: hash.h spellCheck.h spellCheck.cpp
	g++ -c spellCheck.cpp -g

