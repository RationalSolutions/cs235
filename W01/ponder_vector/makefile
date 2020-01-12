###############################################################
# Program:
#     Assignment 01, Vector
#     Brother Kirby, CS235
# Author:
#     Coby Jenkins
# Summary:
#     My own implementation of the std::Vector data structure
# Time:
#     14 hrs
###############################################################

##############################################################
# The main rule
##############################################################
a.out: vector.h assignment01.o
	g++ -o a.out assignment01.o
	tar -cf assignment01.tar vector.h assignment01.cpp makefile

##############################################################
# The individual components
#      assignment01.o     : the driver program
##############################################################
assignment01.o: vector.h assignment01.cpp
	g++ -c assignment01.cpp

