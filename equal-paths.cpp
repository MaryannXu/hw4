#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <stdlib.h>
#include <algorithm>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here
/*
bool isHeightBalancedHelper(Node * node, int& height);

bool equalPaths(Node * root) {
    int height = 0;
    return isHeightBalancedHelper(root, height);
}

bool isHeightBalancedHelper(Node * node, int& height) {
    if (node == NULL) {
        // Empty tree is height balanced by definition
        height = 0;
        return true; 
    }
    else {
        // Recursively check if left and right subtrees are height balanced
        int leftHeight = 0;
        int rightHeight = 0;
        bool leftBalanced = isHeightBalancedHelper(node->left, leftHeight);
        bool rightBalanced = isHeightBalancedHelper(node->right, rightHeight);
        if (leftBalanced == false) {
            // If any subtree is not height balanced, return false
            return false;
        }
        if (rightBalanced == false) {
            return false;
        }
        // Check if the height of left and right subtrees differ by at most 1
        if (abs(leftHeight - rightHeight) > 1) {
            return false;
        }
        // Compute the height of the current node
        height = max(leftHeight, rightHeight) + 1;
        return true;
    }
}
*/


int checkPath(Node * root);

bool equalPaths(Node * root)
{
    // Add your code below
    int result = checkPath(root);
    return (result != -1);
}

int checkPath(Node * root){
    if (root == NULL){
        return 0;
    }
    else {
    int left = checkPath(root->left);
    int right = checkPath(root->right);

    if (left == -1 || right == -1){
        return -1;
    }
    else if (root->left != NULL && root->right != NULL){
        if (abs(left - right) > 0){
            return -1;
        }
    }
    return max(left,right) + 1;
    }
}

