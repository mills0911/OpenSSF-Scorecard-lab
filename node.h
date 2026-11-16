#ifndef NODE_H
#define NODE_H

class Node {
public:
    int data;
    int frequency;
    Node* left;
    Node* right;

    Node(int num);
};

#endif