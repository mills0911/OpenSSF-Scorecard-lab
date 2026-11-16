// Imports
#include <iostream>
#include "BST.h"

void clearInput() { // Get Rid of trailing Newline
    std::cin.clear();
    while (std::cin.get() != '\n') {
    }
}

int getValidInt() { // Validates that the user enters an actual integer
    int value;
    while (!(std::cin >> value)) {
        std::cout << "Invalid input. Please enter an integer: ";
        clearInput();
    }
    return value;
}

// Main
int main(){
    int num_Elements = 0;
    int tree_node = 0;

    // make a pointer to a new bst to be able to use delete later
    BST* basic_bst = new BST();

    std::cout<<"Input number of Tree elements to be added: ";
    // Edge case & validation: size cannot be negative
    while (true) {
        num_Elements = getValidInt();
        if (num_Elements > 0) {
            break;
        }
        std::cout << "Count cannot be negative. Try again: ";
    }
    std::cout<<std::endl;


    // Inputing Numbers into Tree
    std::cout << "Enter numbers\n";
    for (int i=0; i<num_Elements; i++) {
        tree_node = getValidInt();
        basic_bst->add(tree_node);
    }

    // Output 
    std::cout <<std::endl<< "Traversal Type: In-Order"<<std::endl;
    basic_bst->printInOrder();
    std::cout <<std::endl<< "Traversal Type: Pre-Order"<<std::endl;
    basic_bst->printPreOrder();
    std::cout <<std::endl<< "Traversal Type: Post-Order"<<std::endl;
    basic_bst->printPostOrder();

    // Deletion
    delete basic_bst;

    return 0;
}
