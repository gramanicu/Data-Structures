// Copyright Grama Nicolae 2019
#include "../headers/Stack.h"

int main() {
    Stack<int> s;
    for (int i = 1; i < 10; i++) {
        s.push(i);
    }

    std::cout << "Stack size is " << s.getSize() << " - " << s << "\n";

    Stack<int> other = s;
    std::cout << "A copy of the stack is " << other << "\n";

    for (int i = 0; i < 4; i++) {
        std::cout << "Removed the element " << s.pop() << "\n";
    }
    std::cout << "After removing 4 elements from the first stack, the 2 stacks "
                 "are :\n";
    std::cout << "First : " << s << "\n";
    std::cout << "Second : " << other << "\n";

    for (int i = 0; i < 5; i++) {
        s.pop();
    }
    std::cout << "After removing the last 5 elements from the first stack, we have ";
    std::cout << s.getSize() << " elements\n";
    std::cout << "The stack is " << s << "\n";

    std::cout << "Peeking into the second stack we get " << other.peek();
    std::cout << "\n";
    std::cout << "And it wasn't affected by the peek " << other << "\n";

    return 0;
}
