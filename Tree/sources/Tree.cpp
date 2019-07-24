// Copyright 2019 Grama Nicolae
#include "../headers/Tree.h"

int main() { 
    Tree<int> t;
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(5);
    t.insert(6);
    t.insert(7);
    t.insert(8);
    t.insert(9);
    t.insert(10);
    
    std::cout << t.traversal() << "\n";

    return 0; 
}
