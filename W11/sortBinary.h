/***********************************************************************
 * Module:
 *    Week 11, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Michael Gibson
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include <cassert>

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num)
{
    //useful variables
    custom :: BST <T> bst;

    // insert the array into a bst, which creates a sorted
    // binary tree.
    for(int i = 0; i < num; ++i){
        bst.insert(array[i]);
    }

    // copy the bst back into the array as a sorted array.
    int i = 0;
    typename custom :: BST <T> :: iterator it = bst.begin();
    for (; it != bst.end(); ++it){
            array[i++] = *it;
    }
}


#endif // SORT_BINARY_H
