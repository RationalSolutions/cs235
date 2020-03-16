###############################################################
# Program:
#     Assignment 09, Binary Search Tree
#     Brother Kirby, CS235
# Author:
#     Coby Jenkins
#     Michael Gibson
# Summary:
#     Implement a Binary Search Tree using the BNode implementation from last
#     week.
# Time:
#     Coby: I spent about 16 hrs total on this, working out the logic for the
#           erase function was the hardest part I was able to get some help with
#           it from a co-worker in figuring out the logic on that function.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment09.o
	g++ -o a.out assignment09.o -g
	tar -cf assignment09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment09.o     : the driver program
##############################################################
assignment09.o: bst.h assignment09.cpp
	g++ -c assignment09.cpp -g

