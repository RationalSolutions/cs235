###############################################################
# Program:
#     Assignment 04, DEQUE
#     Brother Kirby, CS235
# Author:
#     Coby Jenkins
#     Michael Gibson
# Summary:
#     This is a custom deque style data type which takes any type
#     of data and stores it in an array that is accessible from 
#     both ends of the array. New data can be pushed or popped
#     from either side as well. However, the elements between the
#     first and last element cannot be touched. The order of these
#     elements are maintained. Included is a program to simulate
#     a system to assist sutdents getting help in a computer lab.
#     Students enter their request in order and that order is 
#     maintained as First In First Out. An additional feature allows
#     for emergency cases to be pushed to the front of the line,
#     taking precedence over those who may have come first.
# Time:
#     Coby: The process of figuring out the issues with the deque.h 
#	    file was quite frustrating, mainly because I was not really
#	    paying much attention to the incrementing of our i variable
#	    in our for loops. They needed to be i++ instead of ++i.
#	    Debugging this issue took me 6 hrs.            
#     Mike: The first steps in the project was creating the deque
#           class which seemed to go pretty smoothly until it was
#           submitted to testBed. We spent many hours scouring the
#           code looking for the problem, since it would not track
#           the push, pop, or display properly.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h assignment04.o nowServing.o student.o
	g++ -o a.out assignment04.o nowServing.o student.o
	tar -cf assignment04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment04.o : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
assignment04.o: deque.h assignment04.cpp
	g++ -c assignment04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h student.h
	g++ -c nowServing.cpp

student.o: student.h student.cpp
	g++ -c student.cpp