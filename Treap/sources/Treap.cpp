// Copyright 2019 Grama Nicolae

#include "../headers/Treap.h"

int main() {
    Treap<int> t;

    t.insert(1);
    t.insert(7);
    t.insert(5);
    t.insert(2);
    t.insert(4);
    t.insert(3);
    t.insert(6);

    t.inorder();
    std::cout << "\n\n";

    t.remove(1);
    t.remove(3);

    t.inorder();
    std::cout << "\n\n";

    std::cout << "Tree contains 1 : " << t.search(1) << "\n";
    std::cout << "Tree contains 5 : " << t.search(5) << "\n";

    return 0;
}
