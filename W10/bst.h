/***********************************************************************
 * Component:
 *    Assignment 09, Binary Search Tree (BST)
 *    Brother Kirby, CS 235
 * Author:
 *    Coby Jenkins
 *    Michael Gibson
 * Summary:
 *    Create a binary search tree
 ************************************************************************/
#include <cassert>

#ifndef BST_H
#define BST_H

namespace custom
{
/*********************************************
* BST class - Binary Search Tree structure
*
* Collection of items implemented using
* Binary tree nodes.
 *********************************************/
template <class T>
class BST
{
public:
   //constructors & destructors
   BST(): root(NULL), numElements(0) {};
   BST(const BST<T> & rhs);
   ~BST() { clear(); }

   //nested classes
   class BNode;
   class iterator;
   class reverse_iterator;

   //standard interfaces
   int   size()  { return numElements; };
   bool  empty() { return numElements == 0; }      
   void  clear();
   BNode * getRoot() { return root; };

   //specific iterfaces
   void  insert(const T & t);
   iterator find(const T & t);
   void erase(iterator & it);

   // iterators
   iterator begin();
   iterator end() { return iterator (NULL); }
   iterator rbegin();
   iterator rend() { return iterator (NULL); }

   //overloaded operators
   BST <T> & operator = (const BST <T> & rhs);

   friend std::ostream & operator << (std::ostream & out, BST <T> & bst) //insert for BST
   {
      out << "{  ";
      if(bst.root != NULL)
      {
         out << bst.root;
      }
      out << "}";
      return out;
   }
   
   friend std::ostream & operator << (std::ostream & out, BNode * pNode) //insert for BNode
   {
      if(pNode == NULL)
      {
         return out;
      }

      out << pNode->pLeft;        //L
      out << pNode->data << "  "; //V
      out << pNode->pRight;       //R

      return out;
   }

   friend std::ostream & operator << (std::ostream & out, BNode & rhs)
   {
      out << rhs.data;
      
      return out;
   }

private:
   //member variables
   BNode * root;
   int numElements;     // size
   
   //private methods
   void deleteNode(BNode * pNode, bool right);
   void deleteBinaryTree(BNode * node);
   BNode * copyBinaryTree(const BNode * pSrc)
   {
      if (pSrc == NULL)
      {
         return NULL;
      }

      // create new node
      BNode * destination = new BNode(pSrc->data);
      
      // copies the left sub-trees
      destination->pLeft = copyBinaryTree(pSrc->pLeft);
      if (destination->pLeft != NULL)
      {
         destination->pLeft->pParent = destination;
      }
      
      // copies the right sub-trees
      destination->pRight = copyBinaryTree(pSrc->pRight);
      if (destination->pRight != NULL)
      {
         destination->pRight->pParent = destination;
      }

      return destination;
   }

}; // BST class


/***********************************************************************
 * CLASS BNODE : binary tree node.
 ***********************************************************************/
template <class T>
class BST <T> :: BNode
{
public:
   T data;
   BNode * pParent;
   BNode * pLeft;
   BNode * pRight;
   bool isRed;
   
   //Default Constructor
   BNode() : data(NULL), pParent(NULL), pLeft(NULL), pRight(NULL), isRed(true) {}
   
   //Non Default Constructor
   BNode(const T & t) : data(t), pParent(NULL), pLeft(NULL), pRight(NULL), isRed(true) {}

   BNode & add(const T & t);
   void balance()
   {
      if(pParent != NULL)
      {
         if(!pParent->isRed)
         {
            isRed = true;
         }
         if(pParent->pParent != NULL)
         {
            if ((pParent->pParent->pLeft != NULL) && (pParent->pParent->pRight
                                                      != NULL))
            {
               if ((pParent->pParent->pLeft->isRed) &&
                   (pParent->pParent->pRight->isRed) && (!pParent->pParent->isRed))
               {
                  isRed = true;
                  pParent->pParent->pLeft->isRed = false;
                  pParent->pParent->pRight->isRed = false;
                  pParent->pParent->isRed = true;
               }
            }
         }
      }
   }
   
   // equals, not equals operator
   bool operator != (const BNode & rhs) const { return rhs.data != this->data; }
   bool operator == (const BNode & rhs) const { return rhs.data == this->data; }
   
private:
   bool verifyRedBlack(int depth);
   bool verifyBTree() const ;
   int findDepth() const ;
};

/******************************************************************************
 * BST :: ADD
 ******************************************************************************/
template <class T>
typename BST <T> :: BNode & BST <T> :: BNode :: add(const T & t)
{
   if (data == t) 
   {
      return *this;
   }
   
   // check if value smaller / to place on the correct side
   if (data > t && pLeft != NULL)
   {
      return pLeft->add(t);
   }
   
   // check if value larger / to place on the correct side   
   if (data < t && pRight != NULL)
   {
      return pRight->add(t);
   }
   
   // set parent/child relationships
   BNode * newNode = new BNode(t);
   if (data > t)
   {
      this->pLeft = newNode;
      this->pLeft->pParent = this;
   } 
   else
   {
      this->pRight = newNode;
      this->pRight->pParent = this;
   }
   
   return * newNode;
}

/******************************************************************************
 * BST :: verifyRB - (Same Number of Black Nodes)
 * Recursive, useful for verifying property 
 * "d" of a red-black tree.
 ******************************************************************************/
template <class T>
bool BST <T> :: BNode :: verifyRedBlack(int depth)
{
   depth -= (isRed == false) ? 1 : 0;

   // Rule a) Every node is either red or black
   assert(isRed == true || isRed == false); // this feels silly

   // Rule b) The root is black
   if (pParent == NULL)
      assert(isRed == false);

   // Rule c) Red nodes have black children
   if (isRed == true)
   {
      if (pLeft != NULL)
         assert(pLeft->isRed == false);
      if (pRight != NULL)
         assert(pRight->isRed == false);
   }

   // Rule d) Every path from a leaf to the root has the same # of black nodes
   if (pLeft == NULL && pRight && NULL)
      assert(depth == 0);
   if (pLeft != NULL)
      pLeft->verifyRedBlack(depth);
   if (pRight != NULL)
      pRight->verifyRedBlack(depth);
}

/******************************************************************************
 * BST :: verifyBST -  Ensures that the subtree under a given node 
 * is a valid BST .
 ******************************************************************************/
template <class T>
bool BST <T> :: BNode :: verifyBTree() const
{
   // check parent
   if (pParent)
      assert(pParent->pLeft == this || pParent->pRight == this);

   // check left
   if (pLeft)
   {
      assert(pLeft->data <= data);
      assert(pLeft->pParent == this);
      pLeft->verifyBTree();
   }

   // check right
   if (pRight)
   {
      assert(pRight->data >= data);
      assert(pRight->pParent == this);
      pRight->verifyBTree();
   }
}

/******************************************************************************
 * BST :: findDepth -  Find the depth of the black nodes. This is useful for
 * verifying that a given red-black tree is valid
 ******************************************************************************/
template <class T>
int BST <T> :: BNode ::findDepth() const
{
   // if there are no children, the depth is ourselves
   if (pRight == NULL && pLeft == NULL)
      return (isRed ? 0 : 1);

   // if there is a right child, go that way
   if (pRight != NULL)
      return (isRed ? 0 : 1) + pRight->findDepth();
   else
      return (isRed ? 0 : 1) + pLeft->findDepth();
}


/******************************************************************************
 * BST :: COPY CONSTRUCTOR : creates a new BST from an existing BST
 ******************************************************************************/
template <class T>
BST <T> :: BST (const BST <T> & rhs)
{
   try{
      this->root = this->copyBinaryTree(rhs.root); 
      this->numElements = rhs.numElements;
   }
   catch (std::bad_alloc){
      throw "ERROR: Unable to allocate a node";
   }
}

/******************************************************************************
 * BST :: CLEAR : removes all nodes from BST
 ******************************************************************************/
template <class T>
void BST <T> :: clear()
{
   if (numElements > 0)
   {
      deleteBinaryTree(root);
      root = NULL;
   }
    
   numElements = 0;
}

/******************************************************************************
 * BST :: begin the left outermost value
 ******************************************************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: begin()
{
   if(root != NULL)
   {
      BNode * leftMost = root;

      while (leftMost->pLeft)
      {
         leftMost = leftMost->pLeft;
      }

      return iterator(leftMost);
   }
   else
   {
      return iterator();
   }
}

/******************************************************************************
 * BST :: RBEGIN - the right outmost value
 ******************************************************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: rbegin()
{
   if(root != NULL)
   {
      BNode * rightMost = root;

      while (rightMost->pRight)
      {
         rightMost = rightMost->pRight;
      }

      return iterator(rightMost);
   }
   else
   {
      return iterator();
   }
}

/******************************************************************************
 * BST :: INSERT : inserts a node into the existing BST in the correct location
 ******************************************************************************/
template <class T>
void BST <T> :: insert(const T & t)
{
   try
   {
      BNode *newNode = new BNode(t);

      if (numElements == 0)
      {
         root = newNode;
         numElements++;
         newNode->isRed = false;
         return;
      }
      else
      {
         BNode *pNext = root;

         while (pNext)
         {
            if (t <= pNext->data)
            {
               if (pNext->pLeft == NULL)
               {
                  pNext->pLeft = newNode;
                  newNode->pParent = pNext;
                  pNext = NULL;
                  newNode->balance();
                  root->isRed = false;
               }
               else
               {
                  pNext = pNext->pLeft;
               }
            }
            else
            {
               if (pNext->pRight == NULL)
               {
                  pNext->pRight = newNode;
                  newNode->pParent = pNext;
                  pNext = NULL;
                  newNode->balance();
                  root->isRed = false;
               }
               else
               {
                  pNext = pNext->pRight;
               }
            }
         }
      }
      numElements++;
   }
   catch (const std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a node";
   }
}

/******************************************************************************
 * BST :: FIND : returns an iterator with the location of the element
 ******************************************************************************/
template <class T>
typename BST <T> :: iterator BST <T> :: find(const T & t)
{
   if(empty())
   {
      return end();
   }

   iterator it = iterator(this->root);
   
   // if iterator.data is greater than t decrement the iterator
   while (*it > t)
   {
      it--;
      if (it == NULL)
         return end();
   }
   
   // if iterator.data is lesser than t increment the iterator
   while (*it < t)
   {
      it++;
      if (it == NULL)
         return end();
   }
   
   // found the matching data
   if (*it == t)
   {
      return it;
   }

   // not found
   return iterator();
}

/***********************************************************************
 * BST :: ERASE : iterates through the tree and removes it based on the how
 *              many children it has if any
 ***********************************************************************/
template <class T>
void BST <T> :: erase(BST <T> :: iterator & it)
{

   //no children
   if (it.p->pRight == NULL && it.p->pLeft == NULL)
   {
      if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)
      {
         it.p->pParent->pRight = NULL;
      }
      if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)
      {
         it.p->pParent->pLeft = NULL;
      }
      deleteNode(it.p, false);
      return;
   }
   //one child
   if (it.p->pRight == NULL && it.p->pLeft != NULL) // if the left child exists and right child doesn't exist
   {
      it.p->pLeft->pParent = it.p->pParent;
      if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)
      {
         it.p->pParent->pRight = it.p->pLeft;
      }
      if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)
      {
         it.p->pParent->pLeft = it.p->pLeft;
      }
      deleteNode(it.p, false);
      return;
   }
   if (it.p->pLeft == NULL && it.p->pRight != NULL) // if the right child exists and left child doesn't exist
   {
      it.p->pRight->pParent = it.p->pParent;
      if (it.p->pParent != NULL && it.p->pParent->pRight == it.p)
      {
         it.p->pParent->pRight = it.p->pRight;
      }
      if (it.p->pParent != NULL && it.p->pParent->pLeft == it.p)
      {
         it.p->pParent->pLeft = it.p->pRight;
      }
      deleteNode(it.p, true);
      return;
   }
   else if (it.p->pLeft != NULL && it.p->pRight != NULL) //two children
   {
      BNode *successor = it.p;
      if (successor->pRight != NULL)
      {
         successor = successor->pRight;
         while (successor->pLeft != NULL)
         {
            successor = successor->pLeft;
         }
         it.p->data = successor->data;
         successor->pParent->pLeft = NULL;
         if (successor->pRight != NULL)
         {
            successor->pRight->pParent = successor->pParent;
            successor->pParent->pLeft = successor->pRight;
            successor->pRight = NULL;
         }
         delete successor;
         successor = NULL;
      }
   }
   return;
}

/***********************************************************************
 * BST :: ASSIGNMENT : overloaded = operator
 ***********************************************************************/
template <class T>
BST <T> & BST <T> :: operator = (const BST <T> & rhs)
{
   this->root = this->copyBinaryTree(rhs.root);   
   this->numElements = rhs.numElements;
   
   return *this;
}

/***********************************************************************
 * BST :: DELETENODE :  BNode - recursive function where the children
 * nodes are deleted before deleting the parent node.
 ***********************************************************************/
template <class T>
void BST<T> :: deleteNode(BNode *pNode, bool right)
{
   //if right then pNext is pRight else it is pLeft
   BNode * pNext = (right ? pNode->pRight : pNode->pLeft);

   if(pNode != root)
   {
      if(pNode->pParent->pLeft == pNode)
      {
         pNode->pParent->pLeft = pNext;
      }
      else
      {
         pNode->pParent->pRight = pNext;
      }
   }
   else
   {
      root = pNext;
      pNext->pParent = NULL;
   }
   delete pNode;
}

/***********************************************************************
 * BST :: DELETEBINARYTREE : BST - recursive function where the children
 * nodes are deleted before deleting the parent node.
 ***********************************************************************/
template <class T>
void BST <T> :: deleteBinaryTree(BNode * pNode)
{
   if (pNode == NULL)
   {
      return;
   }
   
   // delete children
   deleteBinaryTree(pNode->pLeft);
   deleteBinaryTree(pNode->pRight);

   // then delete self
   delete pNode;
   pNode = NULL; 
}

/***********************************************************************
 * BST :: ITERATOR
 * provides an iterator class for the BST class
 ***********************************************************************/
template <class T>
class BST <T> :: iterator
{
public:
   // constructors, destructors, and assignment operator
   iterator() : p(NULL) {}
   iterator(BNode *p) : p(p) {}
   iterator(const iterator &rhs) { *this = rhs; }
   iterator &operator=(const iterator &rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator!=(const iterator &rhs) const { return rhs.p != this->p; }
   bool operator==(const iterator &rhs) const { return rhs.p == this->p; }

   // dereference operator
   T &operator*() { return p->data; }
   const T &operator*() const { return p->data; }

   // prefix increment
   iterator &operator++();

   // prefix decrement
   iterator &operator--();

   // postfix increment
   iterator operator++(int postfix)
   {
      iterator tmp = *this;
      ++(*this);
      return tmp;
   }

   // postfix decrement
   iterator operator--(int postfix)
   {
      iterator tmp = *this;
      --(*this);
      return tmp;
   }

   // Friend classes from list, to allow direct usage of private variables of the iterator
   friend void BST<T>::erase(iterator &it);

private:
   BNode *p; // pointer to Node
};

/***********************************************************************
* BST :: REVERSE_ITERATOR
* provides an iterator class for the BST class
***********************************************************************/
template <class T>
class BST <T> :: reverse_iterator
{
public:
   // constructors, destructors, and assignment operator
   reverse_iterator() : p(NULL) {}
   reverse_iterator(BST<T>::BNode *p) : p(p) {}
   reverse_iterator(const reverse_iterator &rhs) { *this = rhs; }
   reverse_iterator &operator=(const reverse_iterator &rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // equals, not equals operator
   bool operator!=(const reverse_iterator &rhs) const { return rhs.p != this->p; }
   bool operator==(const reverse_iterator &rhs) const { return rhs.p == this->p; }

   // dereference operator
   T &operator*() { return p->data; }
   const T &operator*() const { return p->data; }

   // prefix increment
   reverse_iterator &operator++()
   {
      --p;
      return *this;
   }

   // prefix decrement
   reverse_iterator &operator--()
   {
      ++p;
      return *this;
   }

   // postfix increment
   reverse_iterator operator++(int postfix)
   {
      reverse_iterator tmp = *this;
      --p;
      return tmp;
   }

   // postfix decrement
   reverse_iterator operator--(int postfix)
   {
      reverse_iterator tmp = *this;
      ++p;
      return tmp;
   }

private:
   BNode *p; // pointer to Node
};

/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 *************************************************/
template <class T>
typename BST <T> :: iterator & BST <T> :: iterator :: operator ++ ()
{
   // do nothing if we have nothing
   if (NULL == p)
   {
      return *this;
   }

   // if there is a left node, take it
   if (NULL != p->pRight)
   {
      // go right
      p = p->pRight;

      // jig left - there might be more right-most children
      while (p->pLeft)
      {
         p = p->pLeft;
      }
      return *this;
   }

   // there are no left children, the right are done
   assert(NULL == p->pRight);
   BNode *pSave = p;

   // go up
   p = p->pParent;

   // if the parent is the NULL, we are done!
   if (NULL == p)
   {
      return *this;
   }

   // if we are the right-child, got to the parent.
   if (pSave == p->pLeft)
   {
      return *this;
   }

   // we are the left-child, go up as long as we are the left child!
   while (NULL != p && pSave == p->pRight)
   {
      pSave = p;
      p = p->pParent;
   }

   return *this;
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 *     advance by one.
 * Author:      Br. Helfrich
 * Performance: O(log n) though O(1) in the common case
 *************************************************/
template <class T>
typename BST<T>::iterator &BST<T>::iterator ::operator--()
{
   // do nothing if we have nothing
   if (NULL == p)
      return *this;

   // if there is a left node, take it
   if (NULL != p->pLeft)
   {
      // go left
      p = p->pLeft;

      // jig right - there might be more right-most children
      while (p->pRight)
         p = p->pRight;
      return *this;
   }

   // there are no left children, the right are done
   assert(NULL == p->pLeft);
   BNode *pSave = p;

   // go up
   p = p->pParent;

   // if the parent is the NULL, we are done!
   if (NULL == p)
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == p->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (NULL != p && pSave == p->pLeft)
   {
      pSave = p;
      p = p->pParent;
   }

   return *this;
}

} // namespace custom

#endif // BST_H
