// Copyright Grama Nicolae 2019
#include "../headers/LinkedList.h"

// Test for the LinkedList

int main() {
    LinkedList<int> list;
    list.addFirst(3);
    list.addLast(4);
    list.addFirst(2);
    list.addLast(5);
    list.addFirst(1);

    list.removeFirst();
    list.removeLast();
    list.removeLast();
    list.addFirst(1);
    list.removeLast();
    list.addLast(3);

    std::cout << "The list is " << list << "\nAnd its inverse is : ";
    list.printInverse();

    LinkedList<int> otherList = list;
    std::cout << "The other list is " << otherList << "\n";

    list.removeFirst();
    list.removeFirst();
    list.removeFirst();

    list.addLast(1);
    list.addLast(1);
    list.addLast(1);

    std::cout << list << "\n";

    list.removeLast();
    list.removeLast();
    list.removeLast();

    list.addFirst(0);

    std::cout << list << "\n";

    return 0;
}
