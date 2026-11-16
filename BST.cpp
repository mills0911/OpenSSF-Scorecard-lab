#include "BST.h"
#include <iostream>

// Creation
BST::BST(){
    this->root = nullptr;
    this->size = 0;
}
// Deletion
void BST::deleteTree(Node* root){
    if (root !=nullptr){
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}
BST::~BST(){
    deleteTree(root);
}

// Helper functions
Node* BST::findParentForInsert(int num) {return findParentForInsert(root, num);}
void BST::printInOrder() {printInOrder(root);std::cout << std::endl;}
void BST::printPreOrder() {printPreOrder(root);std::cout << std::endl;}
void BST::printPostOrder() {printPostOrder(root);std::cout << std::endl;}


// Function for finding parents of number
Node* BST::findParentForInsert(Node* curr, int num){ // Get the parent of the number to add        
    if (curr == nullptr) {
        return nullptr;
    }
    if (curr->data == num){      // check equal
        return curr;
    }
    else if ((curr->data > num)) {     // check left node, 
        if (curr->left == nullptr){ 
            return curr; 
        }
        return findParentForInsert(curr->left, num);
    }
    else {     // go right
        if (curr->right == nullptr){
            return curr; 
        }
        return findParentForInsert(curr->right, num);
    }

    return nullptr;
}

// TREE FOLLOWING FUNCTIONS MUST BE CHECKED
    //prints BST In-order.
void BST::printInOrder(Node* root) {
    if (root == nullptr) {
        return;
    }
    printInOrder(root->left);
    std::cout <<root->data <<" ";
    printInOrder(root->right);
}

    //prints BST on pre-order
void BST::printPreOrder(Node* root) {
    if (root == nullptr) {
        return;
    }
    std::cout<<root->data<<" ";
    printPreOrder(root->left);
    printPreOrder(root->right);
}



    //prints BST on post-order
void BST::printPostOrder(Node* root) {
    if (root == nullptr) {
        return;
    }
    printPostOrder(root->left);
    printPostOrder(root->right);
    std::cout<<root->data<<" ";
}



void BST::add(int numToAdd){
    // Check if it's the first add 
    if (root == nullptr){
        root = new Node(numToAdd);
        size++;
        return;
    }
    // if it is not root then find where to add and add
    Node* parent = findParentForInsert(numToAdd);
    if (parent->data == numToAdd) { // check if parent is duplicate
        std::cout<<"Duplicate Detected"<<std::endl;
        parent->frequency++;
        return;
    } 
    else if (parent->data > numToAdd){ // check if add node to left
        parent->left = new Node(numToAdd);
    }
    else{ // add node to right
        parent->right = new Node(numToAdd);
    }
    
    size++;
}
