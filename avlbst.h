#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void rotateLeft(AVLNode<Key,Value>* node);
    void rotateRight(AVLNode<Key,Value>* node);
    AVLNode<Key,Value>* predecessor(AVLNode<Key, Value>* current);
    void insertFix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node);
    void removeFix(AVLNode<Key,Value>* parent, int diff);
    AVLNode<Key, Value>* internalFind(const Key& key) const;
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */


template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    AVLNode<Key, Value>* node = new AVLNode<Key,Value>(new_item.first,new_item.second,NULL);

    //tree is empty, make the new node the root
    if(this->root_ == NULL){
        this->root_ = node;
        node->setBalance(0);
        return;
    }

    //find insertion point in the tree
    AVLNode<Key, Value>* parent = NULL;
    AVLNode<Key,Value>* curr = static_cast<AVLNode<Key,Value>*>(this->root_);
    while (curr != NULL){
        parent = curr;
        if(node->getKey() < curr->getKey()){
            curr = curr->getLeft();
        }
        else if (node->getKey() > curr->getKey()){
            curr = curr->getRight();
        }
        else {
            //if key already exists, overwrite the value and return
            curr->setValue(new_item.second);
            delete node;
            return;
        }
    }

    //attach new node to parent
    if (node->getKey() < parent->getKey()){
        parent->setLeft(node); //insert at left
    }
    else if (node->getKey() > parent->getKey()){
        parent->setRight(node); //insert at right
    }
    node->setParent(parent); //set parent
    node->setBalance(0);

    
    if(parent->getBalance() == -1){
        parent->setBalance(0);
        return;
    }
    
    if (parent->getBalance() == 1){
        parent->setBalance(0);
        return;
    }

    if (parent->getBalance() == 0){
        //update balance of parent
        if (node == parent->getLeft()){
            parent->updateBalance(-1);
        }
        else if (node == parent->getRight()){
            parent->updateBalance(1);
        }
        insertFix(parent,node);
        return;
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* parent, AVLNode<Key,Value>* node){
    if (parent == NULL){
        return;
    }

    if (parent->getParent() == NULL){
        return;
    }

    AVLNode<Key, Value>* grandparent = parent->getParent();

    if (parent == grandparent->getLeft()){
        grandparent->updateBalance(-1);
        if (grandparent->getBalance()==0){
            return;
        }
        else if (grandparent->getBalance() == -1){
            insertFix(grandparent,parent);
        }
        else if (grandparent->getBalance() == -2){
            if (node == parent->getLeft()){
                rotateRight(grandparent);
                parent->setBalance(0);
                grandparent->setBalance(0);
            }
            else {
                rotateLeft(parent);
                rotateRight(grandparent);
                if (node->getBalance() == -1){
                    parent->setBalance(0);
                    grandparent->setBalance(1);
                    node->setBalance(0);
                }
                else if (node->getBalance() == 0){
                    parent->setBalance(0);
                    grandparent->setBalance(0);
                    node->setBalance(0);
                }
                else if (node->getBalance() == 1){
                    parent->setBalance(-1);
                    grandparent->setBalance(0);
                    node->setBalance(0);
                }
            }
            
        }
    }
    else if (parent == grandparent->getRight()){
        grandparent->updateBalance(1);
        if (grandparent->getBalance()==0){
            return;
        }
        else if (grandparent->getBalance() == 1){
            insertFix(grandparent,parent);
        }
        else if (grandparent->getBalance() == 2){
            if (node == parent->getRight()){
                rotateLeft(grandparent);
                parent->setBalance(0);
                grandparent->setBalance(0);
            }
            else {
                rotateRight(parent);
                rotateLeft(grandparent);
                if (node->getBalance() == 1){
                    parent->setBalance(0);
                    grandparent->setBalance(-1);
                    node->setBalance(0);
                }
                else if (node->getBalance() == 0){
                    parent->setBalance(0);
                    grandparent->setBalance(0);
                    node->setBalance(0);
                }
                else if (node->getBalance() == -1){
                    parent->setBalance(1);
                    grandparent->setBalance(0);
                    node->setBalance(0);
                }
            }
            
        }
    }
}


/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    
    AVLNode<Key, Value>* node = internalFind(key);
    AVLNode<Key,Value>* parent = NULL;
    int diff;
    if (node == NULL){
        return;
    }

    //if node has 2 children, swap with predecessor
    if (node->getLeft() != NULL && node->getRight() != NULL){
        AVLNode<Key, Value>* pred = predecessor(node);
        nodeSwap(node,pred);
        if (node == this->root_){
            this->root_ = pred;
        }
    }

    //if node has no children, remove it
    if (node != NULL && node->getLeft() == NULL && node->getRight() == NULL){
        if (node == this->root_){
            this->root_ = NULL;
        }
        else {
            //check here
            parent = node->getParent();
            if (parent != nullptr){
                if (node == parent->getLeft()){
                    diff = 1;
                    // parent->updateBalance(1);
                }
                else if (node == parent->getRight()){
                    diff = -1;
                    // parent->updateBalance(-1);
                }
            }

            if (node == (node->getParent())->getLeft()){
                (node->getParent())->setLeft(NULL);
            }
            else {
                (node->getParent())->setRight(NULL);
            }
        }
        
        // break connection with parent node
        node->setParent(NULL);
        // delete node;
        // return;
    }

    //if node has only one child, promote the child
    AVLNode<Key, Value>* child;
    if (node != NULL && node->getLeft() != NULL){
        child = node->getLeft();
        if (node == this->root_){
            this->root_ = child;
        }
        else{
            // check here
            parent = node->getParent();
            if (parent != nullptr){
                if (node == parent->getLeft()){
                    diff = 1;
                    // parent->updateBalance(1);
                }
                else if (node == parent->getRight()){
                    diff = -1;
                    // parent->updateBalance(-1);
                }
            }

            if (node->getParent() != NULL && node == (node->getParent())->getLeft()){
                (node->getParent())->setLeft(child);
            }
            else if (node->getParent()  != NULL && node == (node->getParent())->getRight()){
                (node->getParent())->setRight(child);
            }
        }

        
        child->setParent(node->getParent());
    }
    else if (node != NULL && node->getRight() != NULL){
        child = node->getRight();
        if (node == this->root_){
            this->root_ = child;
        }
        else {
            // check here
            parent = node->getParent();
            if (parent != nullptr){
                if (node == parent->getLeft()){
                    diff = 1;
                    // parent->updateBalance(1);
                }
                else if (node == parent->getRight()){
                    diff = -1;
                    // parent->updateBalance(-1);
                }
            }

            if (node->getParent() != NULL && node == (node->getParent())->getLeft()){
                (node->getParent())->setLeft(child);
            }
            else if (node->getParent()  != NULL && node == (node->getParent())->getRight()){
                (node->getParent())->setRight(child);
            }
        }
        child->setParent(node->getParent());
    }


    // AVLNode<Key,Value>* parent = node->getParent();
    // int diff;
    // if (parent != NULL){
    //     if (node == parent->getLeft()){
    //         diff = 1;
    //         parent->updateBalance(1);
    //     }
    //     else if (node == parent->getRight()){
    //         diff = -1;
    //         parent->updateBalance(-1);
    //     }

        //update pointers
        // if (node == parent->getLeft()){
        //     if (node->getLeft() != NULL){
        //         parent->setLeft(node->getLeft());
        //         node->getLeft()->setParent(parent);
        //     }
        //     else if (node->getRight() != NULL){
        //         parent->setLeft(node->getRight());
        //         node->getRight()->setParent(parent);
        //     }
        // }
        // else if (node == parent->getRight()){
        //     if (node->getLeft() != NULL){
        //         parent->setRight(node->getLeft());
        //         node->getLeft()->setParent(parent);
        //     }
        //     else if (node->getRight() != NULL){
        //         parent->setRight(node->getRight());
        //         node->getRight()->setParent(parent);
        //     }
        // }
    // }

    
    delete node;
    //node = NULL;
    removeFix(parent,diff);
    this->print();
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    AVLNode<Key,Value>* curr = static_cast<AVLNode<Key,Value>*>(this->root_);
    while (curr != NULL){
        if (key == curr->getKey()){
            return curr;
        }
        else if (key < curr->getKey()){
            curr = curr->getLeft();
        }
        else {
            curr = curr->getRight();
        }
    }
    return NULL;
}


template<class Key, class Value>
void AVLTree<Key, Value>:: removeFix(AVLNode<Key,Value>* parent, int diff)
{
    if (parent == NULL){
        return;
    }

    AVLNode<Key,Value>* p = parent->getParent();

    int ndiff;
    if (p != NULL && parent == p->getLeft()){
        ndiff = 1;
    }
    else if (p!= NULL && parent == p->getRight()){
        ndiff = -1;
    }

    if (diff == -1){
        if ((parent->getBalance() + diff) == -2){
            AVLNode<Key,Value>* c = parent->getLeft();
            if (c->getBalance() == -1){
                rotateRight(parent);
                parent->setBalance(0);
                c->setBalance(0);
                removeFix(p,ndiff);
            }
            else if (c->getBalance() == 0){
                rotateRight(parent);
                parent->setBalance(-1);
                c->setBalance(1);
                return;
            }
            else if (c->getBalance() == 1){
                AVLNode<Key,Value>* g = c->getRight();
                rotateLeft(c);
                rotateRight(parent);
                if (g->getBalance() == 1){
                    parent->setBalance(0);
                    c->setBalance(-1);
                    g->setBalance(0);
                    removeFix(p,ndiff);
                }
                else if (g->getBalance() == 0){
                    parent->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                    removeFix(p,ndiff);
                }
                else if (g->getBalance() == -1){
                    parent->setBalance(1);
                    c->setBalance(0);
                    g->setBalance(0);
                    removeFix(p,ndiff);
                }
            }
        }
        else if ((parent->getBalance() + diff) == -1){
            parent->setBalance(-1);
            return;
        }
        else if((parent->getBalance() + diff) == 0){
            parent->setBalance(0);
            removeFix(p,ndiff);
        }
    }
    
    if (diff == 1){
        if ((parent->getBalance() + diff) == 2){
            AVLNode<Key,Value>* c = parent->getRight();
            if (c->getBalance() == 1){
                rotateLeft(parent);
                parent->setBalance(0);
                c->setBalance(0);
                removeFix(p,ndiff);
            }
            else if (c->getBalance() == 0){
                rotateLeft(parent);
                parent->setBalance(1);
                c->setBalance(-1);
                return;
            }
            else if (c->getBalance() == -1){
                AVLNode<Key,Value>* g = c->getLeft();
                rotateRight(c);
                rotateLeft(parent);
                if (g->getBalance() == -1){
                    parent->setBalance(0);
                    c->setBalance(1);
                    g->setBalance(0);
                    removeFix(p,ndiff);
                }
                else if (g->getBalance() == 0){
                    parent->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                    removeFix(p,ndiff);
                }
                else if (g->getBalance() == 1){
                    parent->setBalance(-1);
                    c->setBalance(0);
                    g->setBalance(0);
                    removeFix(p,ndiff);
                }
            }
        }
        else if ((parent->getBalance() + diff) == 1){
            parent->setBalance(1);
            return;
        }
        else if((parent->getBalance() + diff) == 0){
            parent->setBalance(0);
            removeFix(p,ndiff);
        }
    }
    
}


template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* node){
    
    // AVLNode<Key, Value>* parent = node->getParent();
    // if (parent == NULL){
    //     return;
    // }
    // AVLNode<Key, Value>* g = parent->getParent();
    // AVLNode<Key, Value>* leftChild = node->getLeft();
    // //AVLNode<Key, Value>* rightChild = node->getRight();


    // if (g != NULL){
    //     if (parent == g->getLeft()){
    //         g->setLeft(node);
    //         node->setParent(g);
    //     }
    //     else {
    //         g->setRight(node);
    //         node->setParent(g);
    //     }
    // }
    // else {
    //     this->root_ = node;
    // }

    // node->setLeft(parent);
    // parent->setParent(node);

    // if (leftChild != NULL){
    //     parent->setRight(leftChild);
    // }
    // else {
    //     parent->setRight(NULL);
    // }

    AVLNode<Key, Value>* parent = node->getParent();
    AVLNode<Key, Value>* rightChild = node->getRight();
    if (rightChild == NULL){
        return;
    }
    AVLNode<Key, Value>* rightLeftChild = rightChild->getLeft();
    
    if (parent != NULL) {
        if (parent->getLeft() == node) {
            parent->setLeft(rightChild);
        } else {
            parent->setRight(rightChild);
        }
    } else {
        this->root_ = rightChild;
    }

    rightChild->setParent(parent);
    node->setParent(rightChild);
    rightChild->setLeft(node);
    node->setRight(rightLeftChild);

    if (rightLeftChild != NULL) {
        rightLeftChild->setParent(node);
    }
}

template<class Key, class Value>
void AVLTree<Key,Value>::rotateRight(AVLNode<Key,Value>* node){

    // AVLNode<Key, Value>* parent = node->getParent();
    // if (parent == NULL){
    //     return;
    // }
    // AVLNode<Key, Value>* g = parent->getParent();
    // //AVLNode<Key, Value>* leftChild = node->getLeft();
    // AVLNode<Key, Value>* rightChild = node->getRight();

    // if (g != NULL){
    //     if (parent == g->getLeft()){
    //         g->setLeft(node);
    //         node->setParent(g);
    //     }
    //     else {
    //         g->setRight(node);
    //         node->setParent(g);
    //     }
    // }
    // else {
    //     this->root_ = node;
    // }

    // node->setRight(parent);
    // parent->setParent(node);

    // if (rightChild != NULL){
    //     parent->setLeft(rightChild);
    // }
    // else {
    //     parent->setLeft(NULL);
    // }

    AVLNode<Key, Value>* parent = node->getParent();
    AVLNode<Key, Value>* leftChild = node->getLeft();
    if (leftChild == NULL){
        return;
    }
    AVLNode<Key, Value>* leftRightChild = leftChild->getRight();
    
    if (parent != NULL) {
        if (parent->getLeft() == node) {
            parent->setLeft(leftChild);
        } else {
            parent->setRight(leftChild);
        }
    } else {
        this->root_ = leftChild;
    }

    leftChild->setParent(parent);
    node->setParent(leftChild);
    leftChild->setRight(node);
    node->setLeft(leftRightChild);

    if (leftRightChild != NULL) {
        leftRightChild->setParent(node);
    }
}

template<class Key, class Value>
AVLNode<Key, Value>*
AVLTree<Key, Value>::predecessor(AVLNode<Key, Value>* current)
{

   if (current == NULL){
    return NULL;
   }
   else if (current->getLeft() != NULL){
        AVLNode<Key, Value>* predecessor = current->getLeft();
        while (predecessor->getRight() != NULL){
            predecessor = predecessor->getRight();
        }
        return predecessor;
    }
    else {
        AVLNode<Key,Value>* parent = current->getParent();
        while(parent != NULL && current == parent->getLeft()){
            current = parent;
            parent = parent->getParent();
        }
        return parent;
    }
    
}
#endif

// TODO
    //  AVLNode<Key,Value>* curr = static_cast<AVLNode<Key,Value>*>(this->root_);
    // while(curr != NULL){
    //     if (key < curr->getKey()){
    //         curr = curr->getLeft();
    //     }
    //     else if (key > curr->getKey()){
    //         curr = curr->getRight();
    //     }
    //     else{
    //         //found node to be removed
    //         AVLNode<Key,Value>* parent = curr->getParent();

//             if(curr->getLeft() == NULL && curr->getRight() == NULL){
//                 //leaf node, delete it
//                 if (parent == NULL){
//                     this->root_ = NULL;
//                 }
//                 else if (parent->getLeft() == curr){
//                     parent->setLeft(NULL);
//                 }
//                 else {
//                     parent->setRight(NULL);
//                 }
//                 delete curr;
//             }
//             else if (curr->getLeft() == NULL){
//                 //node only has right child, replace with it
//                     if (parent == NULL){
//                         this->root_ = curr->getRight();
//                     }
//                     else if (parent->getLeft() == curr){
//                         parent->setLeft(curr->getRight());
//                     }
//                     else {
//                         parent->setRight(curr->getRight());
//                     }
//                     curr->getRight()->setParent(parent);
//                     delete curr;
//                 }
//                 else if (curr->getRight() == NULL){
//                     //node only has left child, replace with it
//                     if (parent == NULL){
//                         this->root_ = curr->getLeft();
//                     }
//                     else if (parent->getLeft() == curr){
//                         parent->setLeft(curr->getLeft());
//                     }
//                     else {
//                         parent->setRight(curr->getLeft());
//                     }
//                     curr->getLeft()->setParent(parent);
//                     delete curr;
//                 }
//                 else {
//                     // node has two children, swap with predecessor and remove
//                     AVLNode<Key, Value>* pred = predecessor(curr);
//                     nodeSwap(curr,pred);
                    
//                     parent = curr->getParent();

//                     if (curr->getLeft() == NULL){
//                         //pred is a lead node
//                         if (parent == NULL){
//                             //delete this root
//                             this->root_ = NULL;
//                         }
//                         else if (parent->getLeft() == curr){
//                             parent->setLeft(NULL);
//                         }
//                         else {
//                             parent->setRight(NULL);
//                         }
//                         delete curr;
//                     }
//                     else {
//                         //predecessor has a left child
//                         if (parent == NULL){
//                             //delete this root
//                             this->root_ = curr->getLeft();
//                         }
//                         else if (parent->getLeft() == curr){
//                             parent->setLeft(curr->getLeft());
//                         }
//                         else {
//                             parent->setRight(curr->getLeft());
//                         }
//                         curr->getLeft()->setParent(parent);
//                         delete curr;
//                     }
//                 }
//                 //update balance factors and perform rotations
//                 AVLNode<Key,Value>* rebalance_node = parent;
//                 while(rebalance_node != NULL){
//                     int8_t balance = rebalance_node->getBalance();

//                 if (balance == -2){
//                     //left subtree is heavier
//                     AVLNode<Key,Value>* left = rebalance_node->getLeft();
//                     if (left->getBalance()<= 0){
//                         //left-left
//                         rotateRight(rebalance_node);
//                         if(left->getBalance() == 0){
//                             //height of left subtree decreased
//                             break;
//                         }
//                     }
//                     else {
//                         //left-right
//                         rotateLeft(left);
//                         rotateRight(rebalance_node);
//                     }
//                 }
//                 else if (balance == 2){
//                     //right subtree is heavier
//                     AVLNode<Key,Value>* right = rebalance_node->getRight();
//                     if(right->getBalance() >= 0){
//                         //right-right
//                         rotateLeft(rebalance_node);
//                         if(right->getBalance() == 0){
//                             //height of right subtree decreased
//                             break;
//                         }
//                     }
//                     else{
//                         //right-left case
//                         rotateRight(right);
//                         rotateLeft(rebalance_node);
//                     }
//                 }
//                 rebalance_node = rebalance_node->getParent();
//             }  
//         break;
//     }
// }


/*
    //update balance factors and perform rotations
    curr = node->getParent();
    while(curr != NULL){
        int8_t balance = curr->getBalance();
        if (curr->getLeft() == node){
            curr->updateBalance(-1);
        }
        else {
            curr->updateBalance(1);
        }

        if (balance == 0 && curr->getBalance() != 0){
            //height of current node increased by 1
            //go up tree, check balance factors, perform rotations if necessary
            node = curr;
            curr = curr->getParent();
        }
        else if (std::abs(curr->getBalance()) == 2){
            //tree is unbalanced at current node
            //perform rotations to balance and exit the loop
            AVLNode<Key,Value>* pivot;
            if (curr->getBalance() == 2 && curr->getRight()->getBalance() == 1){
                //right-right: single left rotation at current node
                rotateLeft(curr);
            }
            else if (curr->getBalance() == 2 && curr->getRight()->getBalance() == -1){
                //right-left: right rotation at current-> right and then left rotation at current node
                rotateRight(curr->getRight());
                rotateLeft(curr);
            }
            else if (curr->getBalance() == -2 && curr->getLeft()->getBalance() == -1){
                //left-left: single right rotation at current node
               rotateRight(curr);
            }
            else {
                //left-right: left rotation at current->left and then right rotation at current node
                rotateLeft(curr->getLeft());
                rotateRight(curr);
            }
            break;
        }
        else {
            //height of current node did not increase, no rotations needed
            break;
        }
    }
    */
