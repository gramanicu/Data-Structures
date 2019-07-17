#include "../headers/ArrayList.h"

int main() {
    ArrayList<int> list(3);

    for (int i = 0; i < 10; i++) {
        list.addLast(i);
    }

    std::cout << list << "\n";
    list.removeLast();
    std::cout << list << "\n";
    list.removeFirst();
    std::cout << list << "\n";
    list.addFirst(10);
    std::cout << list << "\n";
    list.addLast(92);
    std::cout << list << "\n";

    return 0;
}
