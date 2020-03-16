/***********************************************************************
 * Header:
 *    BNode
 * Summary:
 *    Node struct
 *
 * Author
 *    Coby Jenkins
 *    Michael Gibson
 ************************************************************************/

#ifndef CS235_BNODE_H
#define CS235_BNODE_H
/***********************************************************************
 * BNODE
 * binary tree node.
 ***********************************************************************/
template <class T>
class BNode
{
public:
   //member variables
   T data;
   BNode * pLeft;
   BNode * pRight;
   BNode * pParent;

   //constructors
   BNode(): pLeft(NULL), pRight(NULL), pParent(NULL){}
   BNode(const T & t): data(t), pLeft(NULL), pRight(NULL), pParent(NULL){}
};

/***********************************************************************
 * ADDLEFT : existing node added to left
 ***********************************************************************/
template <class T>
void addLeft(BNode <T> * pNode, BNode <T> * pAdd)
{
   if(pAdd != NULL)
   {
      pAdd->pParent = pNode; //sets parent node of pAdd to current node
   }

   pNode->pLeft = pAdd; //sets pLeft node of current node to point to pAdd
}

/***********************************************************************
 * ADDLEFT : creates new node with template value and adds to left
 ***********************************************************************/
template <class T>
void addLeft(BNode <T> * pNode, const T & t)
{
   BNode <T> * pAdd = new BNode<T>(t); //creates new node
   pAdd->pParent = pNode; //sets parent node of pAdd to current node
   pNode->pLeft = pAdd; //sets pLeft node of current node to point to pAdd
}

/***********************************************************************
 * ADDRIGHT : existing node added to right
 ***********************************************************************/
template <class T>
void addRight(BNode <T> * pNode, BNode <T> * pAdd)
{
   if(pAdd != NULL)
   {
      pAdd->pParent = pNode; //sets parent node of pAdd to current node
   }

   pNode->pRight = pAdd; //sets pRight node of current node to point to pAdd
}

/***********************************************************************
 * ADDRIGHT : creates new node with template value and adds to right
 ***********************************************************************/
template <class T>
void addRight(BNode <T> * pNode, const T & t)
{
   BNode <T> * pAdd = new BNode<T>(t); //creates new node
   pAdd->pParent = pNode; //sets parent node of pAdd to current node
   pNode->pRight = pAdd; //sets pRight node of current node to point to pAdd
}

/***********************************************************************
 * SIZE : recursive function where the size of the sub-tree under L and R + 1
 ***********************************************************************/
template <class T>
int sizeBTree(const BNode <T> * pRoot)
{
   if(pRoot == NULL)
   {
      return 0;
   } else
   {
      return sizeBTree(pRoot->pLeft) + 1 + sizeBTree(pRoot->pRight);
   }
}

/***********************************************************************
 * DELETE : recursive function where the children nodes are deleted before
 *          deleting the parent node.
 ***********************************************************************/
template <class T>
void deleteBTree(BNode <T> * & pNode)
{
   if(pNode == NULL)
   {
      return;
   }
   //delete children
   deleteBTree(pNode->pLeft);
   deleteBTree(pNode->pRight);
   //deletes self
   delete pNode;
   pNode = NULL;
}

/***********************************************************************
 * COPY : recursive function where the children nodes are created and copied
 *        and added to the parent node after the parent node has been created and
 *        copied
 ***********************************************************************/
template <class T>
BNode <T> * copyBTree(const BNode <T> * pSrc)
{
   if(pSrc == NULL)
   {
      return NULL;
   }
   //creates new node
   BNode <T> * destination = new BNode <T> (pSrc->data);
   //copies the left sub-trees
   destination->pLeft = copyBTree(pSrc->pLeft);
   if(destination->pLeft != NULL)
   {
      destination->pLeft->pParent = destination;
   }
   // copies the right sub-trees
   destination->pRight = copyBTree(pSrc->pRight);
   if(destination->pRight != NULL)
   {
      destination->pRight->pParent = destination;
   }

   return destination;
}

/***********************************************************************
 * DISPLAY : overloading the ostream output operator <<
 ***********************************************************************/
template <class T>
std::ostream & operator << (std::ostream & out, BNode <T> * pHead)
{
   if(pHead == NULL)
   {
      return out;
   }

   out << pHead->pLeft;       //L
   out << pHead->data << " "; //V
   out << pHead->pRight;      //R

   return out;
}
#endif //CS235_BNODE_H
