###############################################################
# Program:
#     Assignment 02, STACK
#     Brother Kirby, CS235
# Author:
#     Coby Jenkins
#     Michael Gibson
# Summary:
#     Create a personal version of the stack class. This class
#     maintains the same functionality of the standard template
#     library. This is a template class able to accept any number
#     of values in any data-type. Also included is Infix to Postfix.
# Time:
#     <how long did it take to complete this program>?
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h assignment02.o infix.o 
	g++ -o a.out assignment02.o infix.o 
	tar -cf assignment02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment02.o : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
assignment02.o: stack.h infix.h assignment02.cpp
	g++ -c assignment02.cpp  

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp 

