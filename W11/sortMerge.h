/***********************************************************************
 * Module:
 *    Week 11, Sort Merge
 *    Brother Helfrich, CS 235
 * Author:
 *    Coby Jenkins
 * Summary:
 *    This program will implement the Merge Sort
 ************************************************************************/

#ifndef SORT_MERGE_H
#define SORT_MERGE_H

using namespace std;

/*****************************************************
 * MERGE
 * Perform the merge for the merge sort method
 ****************************************************/
template <class T>
void merge(T destination[], T source1[], int size1, T source2[], int size2)
{
   int i1 = 0;
   int i2 = 0;

   for (int iDest = 0; iDest < (size1 + size2); iDest++)
   {
      if(i1 < size1 && (i2 == size2 || source1[i1] < source2[i2]))
      {
         destination[iDest] = source1[i1++];
      }
      else
      {
         destination[iDest] = source2[i2++];
      }
   }
}

/*****************************************************
 * SORT MERGE
 * Perform the merge sort
 ****************************************************/
template <class T>
void sortMerge(T array[], int num)
{

   T *source = array;
   T *destination = new T[num];

   // iterations counter
   int numIterations = 0;

   // Sub array indexes
   int iBegin2 = 0;
   int iEnd1 = 0;
   int iEnd2 = 0;

   do
   {
      T *pDest = destination;//the current position within the destination array
      numIterations = 0;
      int iBegin1 = 0;

      while (iBegin1 < num)
      {
         numIterations++;

         for (iEnd1 = iBegin1 + 1; iEnd1 < num && !(source[iEnd1 - 1] > source[iEnd1]); iEnd1++);

         iEnd1--;
         iBegin2 = iEnd1 + 1;

         for (iEnd2 = iBegin2 + 1; iEnd2 < num && !(source[iEnd2 - 1] > source[iEnd2]); iEnd2++);

         iEnd2--;

         if (iEnd1 - iBegin1 + 1 >= num) //sort is complete
         {
            numIterations = 0;
            std::swap(source, destination);
            break;
         }

         if (iBegin2 < num) //another subarray to sort
         {

            merge(pDest,
                  source + iBegin1, iEnd1 - iBegin1 + 1,
                  source + iBegin2, iEnd2 - iBegin2 + 1);

            pDest = pDest + (iEnd1 - iBegin1 + iEnd2 - iBegin2 + 2);
         }
         else
         {
            for (int i = 0; i <= iEnd1 - iBegin1; i++)
               pDest[i] = *(source + iBegin1 + i);

            iEnd2 = -1; //set to -1 so iBegin can return to zero
            std::swap(source, destination);

            pDest = destination;
         }

         iBegin1 = iEnd2 + 1;
      }

      std::swap(source, destination);
   } while (numIterations > 1);


   if (array != source)
   {
      for (int i = 0; i <= num - 1; i++)
         array[i] = source[i];
   }
}


#endif // SORT_MERGE_H
