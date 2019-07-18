// Copyright Grama Nicolae 2019
#include "../headers/ArrayList.h"

// Test for the ArrayList

int main() {
    ArrayList<int> list(3);

    for (int i = 0; i < 10; i++) {
        list.addLast(i);
    }

    std::cout << list << "\n";

    ArrayList<int> other = list;
    std::cout << other << "\n";

    for (int i = 0; i < 9; i++) {
        list.removeLast();
    }

    std::cout << list << "\n";
    std::cout << other << "\n";


    return 0;
}
