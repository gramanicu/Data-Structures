// Copyright 2019 Grama Nicolae

#include "../headers/BST.h"

int main() {
    BST<int> b;
    b.insert(7);
    b.insert(2);
    b.insert(1);
    b.insert(5);
    b.insert(4);
    b.insert(6);
    b.insert(3);

    b.remove(1);
    b.remove(4);

    return 0;
}
