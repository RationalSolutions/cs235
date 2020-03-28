/***********************************************************************
 * Module:
 *    Week 11, Sort Insertion
 *    Brother Helfrich, CS 235
 * Author:
 *    Michael Gibson
 * Summary:
 *    This program will implement the Insertion Sort
 ************************************************************************/

#ifndef SORT_INSERTION_H
#define SORT_INSERTION_H

#include <cassert>

/*****************************************************************
 * BINARY SEARCH (recursive)
 * returns the location of iInsert, the index location of where 
 * valuePivot goes if everything has slid.
 ******************************************************************/
template <class T>
int binarySearch(T array[], T search, int iBegin, int iEnd)
{
    // useful variables
    int iMiddle;
    int iTarget;

    // find middle element of the array segment
    iMiddle = (iBegin + iEnd) / 2;

    // return iBegin if it is larger than iEnd
    if (iBegin > iEnd){
        iTarget = iBegin;
    }
    // return iMiddle if the iMiddle element matches search value
    if (array[iMiddle] == search){
        iTarget = iMiddle;
    }
    // if the search value is larger than the element iMiddle,
    // search elements between iMiddle and iEnd, otherwise search
    // elements between iMiddle and iBegin.
    else if (search > array[iMiddle]){
        iTarget = binarySearch(array, search, iMiddle + 1, iEnd);
    } else {
        iTarget = binarySearch(array, search, iBegin, iMiddle - 1);
    }

    return iTarget;
}

/*****************************************************
 * SORT INSERTION
 * Perform the insertion sort
 ****************************************************/
template <class T>
void sortInsertion(T array[], int num)
{
    // useful variables
    int iPivot;
    T valuePivot; // temporary holding variable for array element
    int iInsert;
    int iShift;

    /* I was unable to get the sorting algorithm based on the text to move
       any elements. I reviewed the text over and over, thinking there may
       have been a typo I adjusted both this code and in the binarySearch().
       I referenced other binary search algorithms online, which were
       nearly identical to this one. 

    for (iPivot = num - 2; iPivot == 0; iPivot--){
        valuePivot = array[iPivot];
        iInsert = binarySearch(array, valuePivot, iPivot + 1, num - 1);
        iInsert--;
        
        for(iShift = iPivot; iShift == iInsert; iShift++){
            array[iShift] = array[iShift + 1];
        }
        array[iShift] = valuePivot;
    } */

    // This sort does not take advantage of a search algorithm to establish
    // an insertion point. The O is therefore greater than O(n^2).
    for(iPivot = 1; iPivot < num; iPivot++){
        valuePivot = array[iPivot];
        iInsert = iPivot - 1;

        /* slide elements of the array that are greater than
           valuePivot one position */
        while (iInsert >= 0 && array[iInsert] > valuePivot){
            array[iInsert + 1] = array[iInsert];
            iInsert = iInsert - 1;
        }
        // place valuePivot into the correct position
        array[iInsert + 1] = valuePivot;
    }
}

#endif // SORT_INSERTION_H
