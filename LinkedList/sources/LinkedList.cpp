#include "../headers/LinkedList.h"

int main() {
    LinkedList<int> list;
    list.addLast(1);
    std::cout << list << "\n";
    list.addLast(2);
    std::cout << list << "\n";
    list.addLast(3);
    std::cout << list << "\n";
    list.addLast(4);
    std::cout << list << "\n";
    list.addLast(5);
    std::cout << list << "\n";
    list.printInverse();
    std::cout << "\n";

    std::cout << "List has 6: " << list.hasElement(6) << "\n"; 
    std::cout << "List has 2: " << list.hasElement(2) << "\n";
    std::cout << "List has 1: " << list.hasElement(1) << "\n";
    std::cout << "List has 0: " << list.hasElement(0) << "\n";

    std::cout << "Element with id 0: " << list.getElement(0) << "\n";
    std::cout << "Element with id 2: " << list.getElement(2) << "\n";
    std::cout << "Element with id 5: " << list.getElement(5) << "\n";
    std::cout << "Element with id 9: " << list.getElement(9) << "\n";
    std::cout << "Element with id 3: " << list.getElement(3) << "\n";

    list.addFirst(9);
    list.addFirst(5);
    list.addLast(3);
    list.addLast(2);
    list.addFirst(10);

    std::cout << list << "\n";
    list.printInverse();
    std::cout << "\n";

    list.removeFirst();
    list.removeFirst();
    list.removeFirst();
    list.removeFirst();
    list.removeFirst();

    std::cout << list << "\n";
    list.printInverse();
    std::cout << "\n";

    list.removeLast();

    std::cout << list << "\n";
    list.printInverse();
    std::cout << "\n";
    
    list.removeLast();
    list.removeLast();
    std::cout << "Size is : " << list.getSize() << " - " << list << "\n";

    list.removeLast();
    list.removeLast();
    std::cout << "Size is : " << list.getSize() << " - " << list << "\n";
    list.printInverse();

    list.addFirst(5);
    std::cout << "Size is : " << list.getSize() << " - " << list << "\n";
    list.printInverse();

    list.removeFirst();
    std::cout << "Size is : " << list.getSize() << " - " << list << "\n";
    list.printInverse();

    list.addLast(2);
    std::cout << "Size is : " << list.getSize() << " - " << list << "\n";
    list.printInverse();

    list.addFirst(3);
    list.addLast(4);
    list.addFirst(2);
    list.addLast(5);
    list.addFirst(1);
    std::cout << "First element is: " << list.getHead() << "\n";
    std::cout << "Last element is: " << list.getTail() << "\n";
    std::cout << "The list is: " << list << "\n";

    return 0;
}
