#include "node.h"

Node::Node(int num) {
    data = num;
    frequency = 1;
    left = nullptr;
    right = nullptr;
}