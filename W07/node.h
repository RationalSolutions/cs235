/***********************************************************************
 * Header:
 *    Node
 * Summary:
 *    Node struct
 *

 * Author
 *    Coby Jenkins
 *    Michael Gibson
 ************************************************************************/

#ifndef CS235_NODE_H
#define CS235_NODE_H

/***********************************************************************
 * NODE
 * Linked list node.
 ***********************************************************************/
template <class T>
class Node
{
public:
   T data;
   Node * pPrev;
   Node * pNext;
   
   //Default Constructor
   Node() : data(0), pNext(NULL), pPrev(NULL) {}
   
   //Non Default Constructor
   Node(const T &t) : data(t), pPrev(NULL), pNext(NULL) {}
};

/*************************************************************
 * COPY
 * Takes a pointer to a Node as a parameter and returns a newly
 * created linked-list containing a copy of the nodes below the
 * list represented by the parameter.
 *************************************************************/
template <class T>
Node <T> * copy(const Node <T> * pSource)
{
    Node<T> * pNewHead = new Node<T> (pSource->data);
    Node<T> * pNew = pNewHead;

    // insert nodes from source list to new list
    for (Node <T> * p = pSource->pNext; p; p = p->pNext){
        pNew = insert(pNew, p->data, true);
    }

    // return new head of the copy node
    return pNewHead;
}

/****************************************************************
 * INSERT
 * Inserts a new Node into the current linked-list. The first
 * parameter is the reference Node next to which the new Node is
 * to be inserted. The second parameter is the valude to be inserted
 * into the new node. The default will insert the new node before
 * the reference node, leaving the third parameter optional. This
 * parameter, if true, will set the new node to insert after the
 * referenced node.
 ***************************************************************/
template <class T>
Node <T> * insert(Node <T> * pNode, const T & t, bool after = false)
{
    // initialize new node
    Node <T> *pNew = new Node <T> (t);

    // reference node is null, no other nodes to point to
    if(pNode == NULL){
        // return pointer to new node
        return pNew;
    }
    
    // insert after reference node and set node pointers
    if(after){
        pNew->pNext = pNode->pNext;
        pNew->pPrev = pNode;

        // if an existing node comes after reference node
        if(pNode->pNext){
            pNode->pNext->pPrev = pNew;
        }

        pNode->pNext = pNew;

    }
    else {  // insert before reference node and set pointers
        pNew->pNext = pNode;
        pNew->pPrev = pNode->pPrev;

        // if an existing node comes before reference node
        if(pNode->pPrev){
            pNode->pPrev->pNext = pNew;
        }

        pNode->pPrev = pNew;
    }

    // return pointer to new node
    return pNew;
}

/*****************************************************************
 * FIND
 * Find the Node corresponding to the value passed from a given
 * linked list. The first parameter is the point to the front of the list.
 * The second parameter is the value to be found. The return value
 * is a pointer to the item, if it exists.
 *******************************************************************/
template <class T>
Node <T> * find(Node <T> * pHead, const T & t)
{
    // search through the list starting with first node,
    // comparing value to data in linked list
    for(Node <T> * p = pHead; p ; p = p->pNext){
        if(p->data == t){
           // return a pointer to the node containing the found element
           return p;
        }
    }
    // element not found
    return NULL;
}

/******************************************************************
 * FREEDATA
 * Release all the memory contained in a given linked-list. A single
 * parameter points to the head of the list.
 *******************************************************************/
template <class T>
void freeData(Node <T> * & pHead)
{
    // deletes each node in the list starting with the first node
    while(pHead != NULL){
        Node <T> * p = pHead->pNext;
        delete pHead;
        pHead = p;
    }
    return;
}

/*****************************************************************
 * REMOVE
 * Removes a node from the linked-list. A single parameter points
 * to the node that needs to be removed. If there is a node leading
 * the referenced node, it returns a pointer that node. Otherwise,
 * it returns a pointer to the node that follows the referenced node
 *****************************************************************/
template <class T>
Node <T> * remove(const Node <T> * pRemove)
{
    Node <T> * pRef;

    // if the list is empty
    if(pRemove == NULL){
        std::cout << "The list is empty";
    }

    // change pNext from previous node to point to leading node
    if(pRemove->pPrev){
        pRemove->pPrev->pNext = pRemove->pNext;
    }

    // change pPrev from leading node to point to the following node
    if(pRemove->pNext){
        pRemove->pNext->pPrev = pRemove->pPrev;
    }

    // if there is a leading node to reference, set pRef to that node.
    // Otherwise, set it to the node that follows.
    pRef = pRemove->pPrev ? pRemove->pPrev : pRemove->pNext;

    // clean up
    delete pRemove;

    // returns pointer to specified node (leading, following, or NULL)
    return pRef;
}

/*****************************************************************
 * INSERTION OPERATOR OVERLOAD (<<)
 * Display contents of a linked-list.
 ****************************************************************/
template <class T>
std :: ostream & operator << (std :: ostream & out, const Node <T> * pHead)
{
    // iterate through and display the linked-list
    for(const Node <T> * p = pHead; p; p = p->pNext) {
        if(p->pNext != NULL){
            out << p->data << ", ";
        }
        else {
            out << p->data;
        }
    }
    return out;
}

#endif // CS235_NODE_H