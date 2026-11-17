#ifndef BST_H
#define BST_H

#include "node.h"

class BST {
private:
    Node* root;
    int size;
    void deleteTree(Node* root);

#ifndef NDEBUG
    // Debug-only structural checks; excluded from optimized release builds.
    bool validateSubtree(const Node* current, const Node* lower,
                         const Node* upper, int& visited) const;
    void assertInvariants() const;
#endif

    //Helper Functions
    void printInOrder(Node* root);
    void printPreOrder(Node* root);
    void printPostOrder(Node* root);
    Node* findParentForInsert(Node* curr, int num);

    // Function for Add
    Node* findParentForInsert(int num); 

public:
    BST();
    ~BST();
    void printInOrder();
    void printPreOrder();
    void printPostOrder();
    void add(int numToAdd);
};

#endif
