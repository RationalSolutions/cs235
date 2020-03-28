/***********************************************************************
 * Module:
 *    Week 11, Sort Select
 *    Brother Helfrich, CS 235
 * Author:
 *    Michael Gibson
 * Summary:
 *    This program will implement the Selection Sort
 ************************************************************************/

#ifndef SORT_SELECTION_H
#define SORT_SELECTION_H

/*****************************************************
 * SORT SELECTION
 * Perform the selection sort
 ****************************************************/
template <class T>
void sortSelection(T array[], int num)
{
    // useful variables
    int iPivot;
    int iCheck;
    int iLargest;

    // start with the far right (last) element in array then iterate back
    // through the array.
    for(iPivot = num - 1; iPivot > 0; --iPivot){
        // largest element found so far (initially set to first element)
        iLargest = 0;

        // Check unsorted side for largest element
        for(iCheck = 1; iCheck < iPivot; ++iCheck){
            if(array[iLargest] < array[iCheck] || 
               array[iLargest] == array[iCheck]){
                iLargest = iCheck;
            }
             // swap element in iLargest with element in iPivot
             // if iLargest is greater tha iPivot
            if(array[iLargest] > array[iPivot]){ 
                T temp = array[iLargest];
                array[iLargest] = array[iPivot];
                array[iPivot] = temp;
            }
        }
    }

   return;
}


#endif // SORT_SELECTION_H
