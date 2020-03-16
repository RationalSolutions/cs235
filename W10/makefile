###############################################################
# Program:
#     Assignment 10, Map
#     Brother Kirby, CS235
# Author:
#     Coby Jenkins
#     Michael Gibson
# Summary:
#     Implement a map using the BST/Bnode classes previously implemented and
#     use it to count the frequency of words in a provided file
# Time:
#     Coby: I spent 15 hours ironing out the Red-Black trees and balancing as
#           well as implementing the wordCount code. The last 5 hrs was spent
#           reviewing and ironing out the iterators and access problems Michael was
#           experiencing with the map.h class.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment10.o wordCount.o
	g++ -o a.out assignment10.o wordCount.o -g
	tar -cf assignment10.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment10.o : the driver program
#      wordCount.o    : the wordCount() function
##############################################################
assignment10.o: pair.h map.h bst.h assignment10.cpp
	g++ -c assignment10.cpp -g

wordCount.o: map.h bst.h wordCount.h wordCount.cpp 
	g++ -c wordCount.cpp -g
