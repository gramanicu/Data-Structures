// Copyright Grama Nicolae 2019
#include "../headers/Queue.h"

// Test for the Queue

int main() {
    Queue<int> q;
    for(int i=1; i<10; i++) {
        q.enqueue(i);
    }

    std::cout << "The queue is : " << q << "\n";

    Queue<int> other = q;
    for(int i=0; i<4; i++) {
        std::cout << "Removing element from the queue : " << q.dequeue() << "\n";
    }

    std::cout << "The first queue is : " << q << " with the first element " << q.peek() << "\n";
    std::cout << "The second queue is : " << other << " with the first element " << other.peek() << "\n";

    std::cout << "They weren't changed by the peek :\n" << q << "\n" << other << "\n";

    return 0;
}

