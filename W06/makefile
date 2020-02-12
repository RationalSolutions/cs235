###############################################################
# Program:
#     Assignment 06, NODE
#     Brother Kirby, CS235
# Author:
#     Coby Jenkins
#     Michael Gibson
# Summary:
#     Coby:
#         This assignment was pretty simple because I took Data Structures
#         for Java, so I looked at my work for insertion sorting and
#         converted to C++. I only spent about 2hrs working on this.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: node.h assignment06.o 
	g++ -o a.out assignment06.o -g
	tar -cf assignment06.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment06.o      : the driver program
#      <anything else?>
##############################################################
assignment06.o: node.h assignment06.cpp sortInsertion.h
	g++ -c assignment06.cpp -g 
