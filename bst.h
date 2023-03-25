#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    void clearHelp(Node<Key, Value>* node);
    int height(const Node<Key, Value>* node) const;
    bool checkBalance(const Node<Key, Value>* node) const;

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if (current_ == rhs.current_){
        return true;
    }
    return false;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if (current_ != rhs.current_){
        return true;
    }
    return false;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    if (current_->right_ != NULL){
        current_ = current_->right_;
        while (current_->left_ != NULL){
            current_ = current_->left_;
        }
    }
    else {
        Node<Key, Value>* temp = current_->parent_;
        while (temp!= NULL && current_ == temp->right_){
            current_ = temp;
            temp = temp->parent_;
        }
        current_ = temp;
    }
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    this->root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    Node<Key, Value>* node = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);

    Node<Key, Value>* curr = root_;
    Node<Key, Value>* parent = NULL;

    while (curr != NULL){
        parent = curr;

        if (node->item_.first < curr->item_.first){
            curr = curr->left_;
        }
        else if (node->item_.first > curr->item_.first){
            curr = curr->right_;
        }
        else {
            curr->item_.second = node->item_.second;
            delete node;
            return;
        }
    }
        
    node->parent_ = parent;

    if (parent == NULL){
        root_ = node;
    }
    else if (node->item_.first < parent->item_.first){
        parent->left_ = node;
    }
    else {
        parent->right_ = node;
    }

}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{

    //find the node to remove
    Node<Key, Value>* node = internalFind(key);

    //if key is not already in tree, do nothing
    if (node == NULL){
        return;
    }

    //if node has 2 children, swap with predecessor
    if (node->left_ != NULL && node->right_ != NULL){
        Node<Key, Value>* pred = predecessor(node);
        nodeSwap(node,pred);
    }

    //if node has no children, remove it
    if (node != NULL && node->left_ == NULL && node->right_ == NULL){
        if (node == root_){
            root_ = NULL;
        }
        else {
            if (node == (node->parent_)->left_){
                (node->parent_)->left_ = NULL;
            }
            else {
                (node->parent_)->right_ = NULL;
            }
        }
        // break connection with parent node
        (node->parent_) = NULL;
        delete node;
        return;
    }

    /*
    //if node has 2 children, swap with predecessor
    if (node->left_ != NULL && node->right_ != NULL){
        Node<Key, Value>* pred = predecessor(node);
        nodeSwap(node,pred);
        
        if (node == (node->parent_)->left_){
            (node->parent_)->left_ = NULL;
            node->parent_ = NULL;
        }
        else if (node == (node->parent_)->right_){
            (node->parent_)->right_ = NULL;
            node->parent_ = NULL;
        }

        delete node;
        return;
    }
    */


    //if node has only one child, promote the child
    Node<Key, Value>* child = NULL;
    if (node != NULL && node->left_ != NULL){
        child = node->left_;
        if (node == root_){
            root_ = child;
        }
        else if (node->parent_ != NULL && node == (node->parent_)->left_){
            (node->parent_)->left_ = child;
        }
        else if (node->parent_  != NULL && node == (node->parent_)->right_){
            (node->parent_)->right_ = child;
        }
        child->parent_ = node->parent_;
        delete node;
        return;
    }
    else if (node != NULL && node->right_ != NULL){
        child = node->right_;
        if (node == root_){
            root_ = child;
        }
        else if (node->parent_ != NULL && node == (node->parent_)->left_){
            (node->parent_)->left_ = child;
        }
        else if (node->parent_  != NULL && node == (node->parent_)->right_){
            (node->parent_)->right_ = child;
        }
        child->parent_ = node->parent_;
        delete node;
        return;
    }
    
    //1
    /*
    Node<Key, Value>* temp = internalFind(key);

    if (temp == NULL){
        return;
    }
    if (temp->getLeft() == NULL && temp->getRight() == NULL){
        if (temp == root_){
            root_ = NULL;
        }
        else {
            Node<Key, Value>* parent = temp->getParent();
            if (parent->getLeft() == temp){
                parent->setLeft(NULL);
            }
            else {
                parent->setRight(NULL);
            }
        }
        delete temp;
    }
    else if (temp->getLeft() == NULL || temp->getRight() == NULL){
        Node<Key, Value>* child;
        if (temp->getLeft() != NULL){
            child = temp->getLeft();
        }
        else {
            child = temp->getRight();
        }

        if (temp == root_){
            root_ = child;
        }
        else {
            Node<Key, Value>* parent = temp->getParent();
            if (parent->getLeft() == temp){
                parent->setLeft(child);
            }
            else {
                parent->setRight(child);
            }
            child->setParent(parent);
        }
        delete temp;
    }
    else {
        Node<Key, Value>* predecessor = BinarySearchTree<Key, Value>::predecessor(temp);
        nodeSwap(temp, predecessor);
        remove(key);
    }
    */

    //2
    /*
    Node<Key, Value>* temp = internalFind(key);

    if (temp == NULL){
        return;
    }

    if (temp->getLeft() != NULL && temp->getRight() != NULL){
        Node<Key, Value>* predecessor = temp->getLeft();
        while (predecessor->getRight() != NULL){
            predecessor = predecessor->getRight();
        }
        nodeSwap(temp, predecessor);
        temp = predecessor;
    }

    Node<Key, Value>* child = NULL;
    if (temp->getLeft() != NULL){
        child = temp->getLeft();
    }
    else {
        child = temp->getRight();
    }

    if(temp->getParent() == NULL){
        root_ = child;
    }
    else {
        if (temp == (temp->getParent())->getLeft()){
            (temp->getParent())->setLeft(child);
        }
        else {
            (temp->getParent())->setRight(child);
        }
    }

    if (child != NULL){
        child->setParent(temp->getParent());
    }

    delete temp;
    */

    //3
    /*
    Node<Key, Value>* temp = internalFind(key);

    //not in tree
    if (temp == NULL){
        return;
    }

    //has 2 children
    if (temp->getLeft() != NULL && temp->getRight() != NULL){
        Node<Key, Value>* predecessor = temp->getLeft();
        while (predecessor->getRight() != NULL){
            predecessor = predecessor->getRight();
        }
        nodeSwap(temp, predecessor);
        temp = predecessor;
    }

    Node<Key, Value>* child = NULL;
    if (temp->getLeft() != NULL){
        child = temp->getLeft();
    }
    else {
        child = temp->getRight();
    }

    if(child != NULL){
        child->setParent(temp->getParent());
        if (temp->getParent() == NULL){
            root_ = child;
        }
        else if (temp == (temp->getParent())->getLeft()){
            (temp->getParent())->setLeft(child);
        }
    }
    else{
        if (temp->getParent() == NULL){
            root_ = NULL;
        }
        else if(temp == (temp->getParent())->getLeft()){
            (temp->getParent())->setLeft(NULL);
        }
        else {
            (temp->getParent())->setRight(NULL);
        }
    }

    delete temp;
    */

   /*
    Node<Key, Value>* node = internalFind(key);

    //if key is not already in tree, do nothing
    if (node == NULL){
        return;
    }

    //if node has 2 children, swap with predecessor
    if (node->left_ != NULL && node->right_ != NULL){
        Node<Key, Value>* pred = predecessor(node);
        nodeSwap(node,pred);
        node = pred;
    }

    //if 0 or 1 child
    Node<Key,Value>* child;
    if (node->left_ != NULL){
        child = node->left_;
    }
    else {
        child = node->right_;
    }

    if (child != NULL){
        nodeSwap (node, child);
    }
    else {
        if (node == root_){
            root_ = NULL;
        }
        else {
            if (node == (node->parent_)->left_){
                (node->parent_)->left_ = NULL;
            }
            else {
                (node->parent_)->right_ = NULL;
            }
        }
        delete node;
    }
    */
    
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    
    /*
    if (current == NULL){
    return NULL;
   }

    if ((current->left_) != NULL){
        while (current->parent_ != NULL && current == (current->parent_)->left_){
            current = current->parent_;
        }
        return current->parent_;
    }
    else {
        Node<Key,Value>* pred = current->left_;
        while (pred->right_ != NULL){
            pred = pred->right_;
        }
        return pred;
    }
    */

   
   if (current == NULL){
    return NULL;
   }
   else if (current->left_ != NULL){
        Node<Key, Value>* predecessor = current->left_;
        while (predecessor->right_ != NULL){
            predecessor = predecessor->right_;
        }
        return predecessor;
    }
    else {
        Node<Key,Value>* parent = current->parent_;
        while(parent != NULL && current == parent->left_){
            current = parent;
            parent = parent->parent_;
        }
        return parent;
    }
    
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    clearHelp(root_);
    root_ = NULL;
    return;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelp(Node<Key,Value>* node){
    if (node == NULL){
        return;
    }
    clearHelp(node->getLeft());
    clearHelp(node->getRight());
    delete node;
    return;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    if (root_ == NULL){
        return NULL;
    }

    Node<Key, Value>* curr = root_;
    while (curr -> getLeft() != NULL){
        curr = curr->getLeft();
    }

    return curr;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    Node<Key, Value>* curr = root_;
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

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    return checkBalance(root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::checkBalance(const Node<Key, Value>* node) const{
    if (node == NULL){
        return true;
    }
    int left = height(node->getLeft());
    int right = height(node->getRight());
    if(abs(left - right) > 1){
        return false;
    }
    return (checkBalance(node->getLeft()) && checkBalance(node->getRight()));
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height(const Node<Key, Value>* node) const{
    if (node == NULL){
        return -1;
    }
    return 1 + std::max(height(node->left_),height(node->right_));
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
