// Copyright 2019 Grama Nicolae
#include "../headers/Heap.h"

int main() {
    Heap<int> h;

    for(int i = 100; i> 0; i--) {
        h.push(i);
    }


    std:: cout << "Eliminated the first element : " << h.pop() << "\n";

    std::cout << "The elements sorted are " << h.sort() << "\n";
 
    return 0;
}
