###############################################################
# Program:
#     Assignment 11, Sorts
#     Brother XXXXX, CS235
# Author:
#     Coby Jenkins
# Summary:
#     <put a description here>
# Time:
#     Coby: I spent 10 hrs getting the Quick and Merge sorts working properly.
#          I struggled most figuring out how the Merge sort to work beyond
#          what was in the psuedocode
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment11.o
	g++ -o a.out assignment11.o -g
	tar -cf assignment11.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment11.o     : the driver program
##############################################################
assignment11.o: assignment11.cpp sortValue.h \
		sortBinary.h sortInsertion.h sortHeap.h sortBubble.h \
		sortSelection.h sortMerge.h sortQuick.h
	g++ -c assignment11.cpp -g

