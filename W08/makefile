###############################################################
# Program:
#     Assignment 08, Binary Tree
#     Brother Kirby, CS235
# Author:
#     Coby Jenkins
#     Michael Gibson
# Summary:
#     Build a template for a binary tree, and implement it
#	  by creating a class to handle Huffman codes.
# Time:
#     Coby: I spent 3 hours working out the BNode adt the most difficult part
#           was the << operator overloading to work the way text has the
#           psuedocode for the LVR display.
#     Michael: The huffman aspect of the project proved to be rather 
#           challenging. I spent 10 hours working on different algorithms
#           that would work to help me create the huffman code. I am
#           pretty certain there are ways to do this project that are
#           cleaner. I struggled with the sort algorithm causing problems
#           with the huffman2.txt. I tried doing different adjustments to
#           the bubble sort and how to handle == elements but I didn't find
#           a solution.
#
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment08.o huffman.o 
	g++ -o a.out assignment08.o huffman.o -g
	tar -cf assignment08.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment08.o : the driver program
#      huffman.o      : the logic for the huffman code program
##############################################################
assignment08.o: bnode.h huffman.h assignment08.cpp
	g++ -c assignment08.cpp -g

huffman.o: bnode.h vector.h huffman.h huffman.cpp
	g++ -c huffman.cpp -g

