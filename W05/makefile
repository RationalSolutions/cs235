###############################################################
# Program:
#     Assignment 05, SET
#     Brother Kirby, CS235
# Author:
#     Coby Jenkins
#     Michael Gibson
# Summary:
#     Implement a custom version of the std::set data structure and implement
#     the body of the goFish game.
# Time:
#     Coby: I spent about 5 hours on the set.h file and about 2 hours on the
#           goFish.cpp files. My struggle was getting the set.h file to
#           compile because I was missing a method implementation. Thankfully
#           Michael was able to identify my mistake and got it working.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment05.o goFish.o card.o
	g++ -o a.out assignment05.o goFish.o card.o
	tar -cf assignment05.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment05.o : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
assignment05.o: set.h goFish.h assignment05.cpp
	g++ -c assignment05.cpp

goFish.o: set.h goFish.h goFish.cpp card.h
	g++ -c goFish.cpp

card.o: card.h card.cpp
	g++ -c card.cpp
