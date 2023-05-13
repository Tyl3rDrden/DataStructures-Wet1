#include "AVLTREE.h"
#include <iostream>

struct GreaterThan {
    bool operator()(const int& a, const int& b) const {
        return b >= a;
    }
};

int main() {
    GreaterThan gt;
    AVLTREE<int, GreaterThan> tree(gt);
    tree.InsertElement(std::make_shared<int>(1));
    tree.InsertElement(std::make_shared<int>(2));
    tree.InsertElement(std::make_shared<int>(3));
    tree.InsertElement(std::make_shared<int>(4));
    tree.InsertElement(std::make_shared<int>(5));
    tree.InsertElement(std::make_shared<int>(6));
    tree.InsertElement(std::make_shared<int>(7));
    tree.InsertElement(std::make_shared<int>(8));
    tree.InsertElement(std::make_shared<int>(9));
    tree.printVisual();
    //tree.InsertElement(std::make_shared<int>(40));
    return 0;
}