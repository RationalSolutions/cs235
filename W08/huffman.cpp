/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Kirby, CS235
 * Author:
 *    Coby Jenkins
 *    Michael Gibson
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include <iostream>        // for CIN and COUT
#include <fstream>         // for IFSTREAM
#include <cassert>         // for ASSERT
#include <string>          // for STRING: binary representation of codes
#include "bnode.h"         // for BINARY_NODE class definition
#include "vector.h"        // for VECTOR container
#include "pair.h"          // for PAIR container
#include "huffman.h"       // for HUFFMAN() prototype

#define MAX_TREE_HT 100 

using std::cout;
using std::cin;
using std::ifstream;
using std::endl;
using std::string;
using std::bad_alloc;
using namespace custom;

typedef BNode<custom::pair<float, string> > hTree;
typedef BNode<custom::pair<string, string> > dTree;
typedef custom::pair<float, string> elementPair;
typedef custom::pair<string, string> dataPair;

void readFile(vector<hTree*> & treeVector, string fileName);
bool isSizeOne(const vector<hTree*> treeVector);
void bubbleSort(vector<hTree*> & treeVector, int size);
void swap(hTree* *h1, hTree* *h2);
hTree* popBNode(vector<hTree*> & treeVector);
string setHuffCode(int arr[], int n);
bool isLeaf(const hTree* root);
void setCodes(hTree* & root, int arr[], int top,
                vector<dTree*> & dataVector);
vector<dTree*> compVector(vector<hTree*> & treeVector,
                vector<dTree*> & dataVector);

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(const string & fileName)
{
   vector<hTree*> treeVector;

   readFile(treeVector, fileName);

   // begin building binary tree
   vector<hTree*> bTreeVector;

   for(int i = 0; i < treeVector.size(); i++){
      bTreeVector.push_back(treeVector[i]);
   }

   while(!isSizeOne(bTreeVector))
   {
      // sort vector by freqency
      bubbleSort(bTreeVector, bTreeVector.size());
      hTree* child1 = new hTree();
      hTree* child2 = new hTree();

      // extract first two elements from the sorted vector (least freequent)
      child1 = copyBTree(popBNode(bTreeVector));
      child2 = copyBTree(popBNode(bTreeVector));

      // create a parent with frequency based on sum of child frequency
      // $ is just a place holder for non-used character
      elementPair p1(child1->data.first + child2->data.first, "$");

      hTree* parent = new hTree(p1);
      addLeft(parent, child1);
      addRight(parent, child2);

      // insert parent into vector
      bTreeVector.push_back(parent);
   }

   hTree* root = new hTree();

   root = copyBTree(bTreeVector[0]);

	// traverse the binary tree to assign huffman codes, create vector with
   // final data set.
   vector<dTree*> dataVector;
   vector<dTree*> finVector;

	int arr[MAX_TREE_HT], top = 0; 
	setCodes(root, arr, top, dataVector);

   // compare vectors to transfer huffman codes to original vector
   finVector = compVector(treeVector, dataVector);

   // Display treeVector contents
   for(int i = 0; i < finVector.size(); ++i){
      cout << finVector[i]->data.second << " = " 
           << finVector[i]->data.first << endl;
   }

   return;
}

/*****************************************************************
 * HUFFMAN : READFILE
 * takes in a filename containing a set of values
 * and puts them into a vector of bNode trees
 *****************************************************************/
void readFile(vector<hTree*> & treeVector, string fileName)
{
   // Element parts, first and second piece of the pair   
   float pair1;
   string pair2;

   ifstream fin(fileName);

   // check for read failure
   if (fin.fail()){
      cout << "Could not read file.\n";
      return;}
   
   // read the file into a vector of bNode pairs
   while(fin >> pair2 >> pair1){
         elementPair p1(pair1, pair2);
         hTree* h1 = new hTree(p1);
         treeVector.push_back(h1);
   }

   fin.close();

   return;
}


/*************************************************************
 * HUFFMAN : ISSIZEONE
 * Is the vector size one bNode
 ************************************************************/
bool isSizeOne(const vector<hTree*> treeVector)
{
   // is there just a single bNode left in the vector?
   return treeVector.size() == 1;
}


/***************************************************************
 * HUFFMAN : BUBBLESORT
 * Sort the vector by frequency (pair1)
 *************************************************************/
void bubbleSort(vector<hTree*> & treeVector, int size)
{
   // if there is only one bNode, nothing to sort
   if (size == 1) 
        return;
   
   // One pass of the bubble sort. Largest number is moved to end
   for(int i = 0; i < size - 1; i++)
   {
      if(treeVector[i]->data.first > treeVector[i + 1]->data.first){
         swap(treeVector[i], treeVector[i + 1]);
      }
   }
   // recursive sort through entire vector
   bubbleSort(treeVector, size - 1);

   return;
}

/*********************************************************
 * HUFFMAN : SWAP
 * swap bNodes
 ***********************************************************/
void swap(hTree* *h1, hTree* *h2)
{  
   // create temporary bNode
   hTree* temp = new hTree();
   temp = copyBTree(*h1);
   
   // copy h2 to h1
   *h1 = copyBTree(*h2);
   
   // copy temp to h2
   *h2 = copyBTree(temp); 

   return;
} 

/*********************************************************
 * HUFFMAN : POPBNODE
 * removes the first bNode from the Vector returns bNode to
 * the caller
 *********************************************************/
hTree* popBNode(vector<hTree*> & treeVector)
{
   // create temporary bNode
   hTree* temp = new hTree();
   temp = copyBTree(treeVector[0]);

   // create tempVector to hold all but first bNode
   vector<hTree*> tempVector;

   // copy all but first bNode to temp vector
   for(int i = 1; i < treeVector.size(); i++){
      tempVector.push_back(treeVector[i]);
   }

   // assign tempVector to treeVector leaving it without first bNode
   treeVector = tempVector;

   return temp;
}

/*********************************************************
 * HUFFMAN : SETCODES
 * traverses the binary tree and replaces the frequency with
 * huffman code.
 *********************************************************/
void setCodes(hTree* & root, int arr[], int top,
               vector<dTree*> & dataVector)
{ 

	// Assign 0 to left edge and recur 
	if (root->pLeft) { 
		arr[top] = 0; 
		setCodes(root->pLeft, arr, top + 1, dataVector); 
	} 

	// Assign 1 to right edge and recur 
	if (root->pRight) { 
		arr[top] = 1; 
		setCodes(root->pRight, arr, top + 1, dataVector); 
	} 

	// If this is a leaf node, it contains original data.
   // set new huffman codes and insert into vector
	if (isLeaf(root)) { 
		string first = setHuffCode(arr, top);
      dataPair p1(first, root->data.second);
      dTree* d1 = new dTree(p1);
      dataVector.push_back(d1);
	} 
}

/*********************************************************
 * HUFFMAN : ISLEAF
 * returns true when we've reached the end of the tree (LEAF)
 *********************************************************/
bool isLeaf(const hTree* root)
{
   return !(root->pLeft) && !(root->pRight);
}

/*********************************************************
 * HUFFMAN : SETHUFFCODE
 * Combines the left and right edges zeros and ones to create the 
 * huffman code for each bNode.
 *********************************************************/
string setHuffCode(int arr[], int n) 
{
   int code;
   string tempStr = "";

	for (int i = 0; i < n; ++i){ 
		code = arr[i];
      tempStr = tempStr + std::to_string(code);
   }

	return tempStr; 
}

/*********************************************************
 * HUFFMAN : COMPVECTOR
 * traverses the data vector to finalize the treeVector with
 * the huffman code.
 *********************************************************/
vector<dTree*> compVector(vector<hTree*> & treeVector,
                            vector<dTree*> & dataVector)
{
   vector<dTree*> tempVector;

   for(int i = 0; i < treeVector.size(); i++){
      for(int j = 0; j < dataVector.size(); j++){
         if(treeVector[i]->data.second == dataVector[j]->data.second){
            string second  = treeVector[i]->data.second;
            string first = dataVector[j]->data.first;
            dataPair p1(first, second);
            dTree* d1 = new dTree(p1);
            tempVector.push_back(d1);
         }
      }
   }
   return tempVector;
}