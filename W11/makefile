###############################################################
# Program:
#     Assignment 11, Sorts
#     Brother Kirby, CS235
# Author:
#     Coby Jenkins
#     Michael Gibson
# Summary:
#     six of seven different sort algorithms taking advantage of different
#     solutions for sorting. This includes Binary Sort, Bubble Sort, Insertion
#     Sort, Merge Sort, Quick Sort and Selection Sort.
# Time:
#     Coby: I spent 10 hrs getting the Quick and Merge sorts working properly.
#          I struggled most figuring out how the Merge sort to work beyond
#          what was in the psuedocode
#     Michael: Total time => 8 hours. I started on the Heap class but moved to
#          doing the other sorts and never came back to the Heap. I struggled
#          to get the insertion sort to work using the binarySearch() function.
#          I don't know what I was missing, but the sort didn't move any elements.
#          I created an insertion sort that didn't take advantage of the
#          binarySearch(). It works but is not as efficient. The bubble sort was
#          rather easy as I have used it many times in other projects.
#          Selection sort fell into place following the psuedocode with little
#          adjustment. I struggled a little with the binary sort because our
#          binary search tree doesn't allow for duplicate values. I made an 
#          adjustment to the bst that would add duplicate values and the sort
#          worked.
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

