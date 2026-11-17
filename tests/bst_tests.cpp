#include "BST.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

namespace {
int failures = 0;

void expectEqual(const std::string& label, const std::string& actual,
                 const std::string& expected) {
    if (actual != expected) {
        std::cerr << "FAIL " << label << "\nExpected: [" << expected
                  << "]\nActual:   [" << actual << "]\n";
        ++failures;
    }
}

// Redirect the BST's console output while maintaining exception-safe cleanup.
class CaptureStdout {
public:
    CaptureStdout() : previous_(std::cout.rdbuf(capture_.rdbuf())) {}
    ~CaptureStdout() { std::cout.rdbuf(previous_); }
    CaptureStdout(const CaptureStdout&) = delete;
    CaptureStdout& operator=(const CaptureStdout&) = delete;
    std::string text() const { return capture_.str(); }
private:
    std::ostringstream capture_;
    std::streambuf* previous_;
};

void testEmptyTree() {
    BST tree;
    CaptureStdout capture;
    tree.printInOrder();
    tree.printPreOrder();
    tree.printPostOrder();
    expectEqual("empty tree traversals", capture.text(), "\n\n\n");
}

void testBalancedTree() {
    BST tree;
    for (int value : {8, 3, 10, 1, 6}) tree.add(value);
    CaptureStdout capture;
    tree.printInOrder();
    tree.printPreOrder();
    tree.printPostOrder();
    expectEqual("three traversal orders", capture.text(),
                "1 3 6 8 10 \n8 3 1 6 10 \n1 6 3 10 8 \n");
}

void testDuplicateTree() {
    BST tree;
    CaptureStdout capture;
    for (int value : {4, 4, 2, 6, 4}) tree.add(value);
    tree.printInOrder();
    expectEqual("duplicates tracked without extra nodes", capture.text(),
                "Duplicate Detected\nDuplicate Detected\n2 4 6 \n");
}

void testSingleAndSkewedTrees() {
    BST tree;
    tree.add(7);
    {
        CaptureStdout capture;
        tree.printInOrder();
        tree.printPreOrder();
        tree.printPostOrder();
        expectEqual("single node", capture.text(), "7 \n7 \n7 \n");
    }
    for (int value : {8, 9, 6, 5}) tree.add(value);
    CaptureStdout capture;
    tree.printInOrder();
    tree.printPreOrder();
    tree.printPostOrder();
    expectEqual("left and right insertions", capture.text(),
                "5 6 7 8 9 \n7 6 5 8 9 \n5 6 9 8 7 \n");
}

void testExtremeValues() {
    BST tree;
    tree.add(0);
    tree.add(std::numeric_limits<int>::min());
    tree.add(std::numeric_limits<int>::max());
    CaptureStdout capture;
    tree.printInOrder();
    expectEqual("integer boundaries", capture.text(),
                std::to_string(std::numeric_limits<int>::min()) +
                " 0 " + std::to_string(std::numeric_limits<int>::max()) + " \n");
}
} // namespace

int main() {
    testEmptyTree();
    testBalancedTree();
    testDuplicateTree();
    testSingleAndSkewedTrees();
    testExtremeValues();
    if (failures != 0) {
        std::cerr << failures << " BST unit test(s) failed.\n";
        return 1;
    }
    std::cout << "All BST unit tests passed.\n";
    return 0;
}
