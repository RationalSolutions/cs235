/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num)
{

   //inserting @ head
   Node <T>* headNode = NULL;
   headNode = insert(headNode, array[0]);

   for (int i = 1; i < num; i++)
   {
      T indexData = array[i];
      Node <T>* newNode = headNode;
      Node <T>* tempNode;
      bool notInserted = true;

      //determines placement of new nodes in list
      for (newNode = headNode; newNode; newNode = newNode->pNext)
      {
         if (notInserted)
         {
            if (indexData < newNode->data)
            {
               tempNode = newNode;
               if (newNode->pPrev == NULL)
               {
                  headNode = insert(headNode, indexData, false);
               }
               else
               {
                  tempNode = insert(tempNode, indexData, false);
               }
               notInserted = false;
            }
            else
            {
               tempNode = newNode;
            }
         }
      }
      if (notInserted)
      {
         insert(tempNode, indexData, true);
      }
   }

   //copys linked list into array
   Node <T>* newNode = headNode;
   for (int i = 0; i < num; i++)
   {
      array[i] = newNode->data;
      newNode = newNode->pNext;
   }
}

#endif // INSERTION_SORT_H

