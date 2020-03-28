/***********************************************************************
 * Module:
 *    Week 11, Sort Bubble
 *    Brother Helfrich, CS 235
 * Author:
 *    Michael Gibson
 * Summary:
 *    This program will implement the Bubble Sort
 ************************************************************************/

#ifndef SORT_BUBBLE_H
#define SORT_BUBBLE_H

/*****************************************************
 * SORT BUBBLE
 * Perform the bubble sort
 ****************************************************/
template <class T>
void sortBubble(T array[], int num)
{
    // useful variables
    bool swapped = false;
    int iPivot;

    // start with the far right (last) element in array
    for(iPivot = num - 1; iPivot > 0; --iPivot){
        swapped = false;

        // check every element for the largest element and
        // move it into the last position in the unsorted side
        for(int iCheck = 0; iCheck < iPivot; ++iCheck){
            if(array[iCheck] > array[iCheck + 1]){
                T temp = array[iCheck];
                array[iCheck] = array[iCheck + 1];
                array[iCheck + 1] = temp;
                swapped = true;
            }
            if(swapped = false){ // if everything is in order stop
                return;
            }
        }
    }

   return;
}

#endif // SORT_BUBBLE_H
