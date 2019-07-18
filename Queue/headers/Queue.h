// Copyright Grama Nicolae 2019
#ifndef QUEUE_H_
#define QUEUE_H_

/*  This is a implementation of a queue. The data is stored in nodes,
    linked using pointers. This means that the queue can use all the
    memory the computer has available, as it doesn't need a continuous
    block of memory.

    The queue is a data structure based on the FIFO principle (first
    in, first out). This means any new node is added at the end of
    the "list", and only the last node will be accessible or removable
*/

#include <iostream>

/*  A data structure in which values are stored, the base of the queue.
    Beside the value, it will store a pointer to the next node. It doesn't
    need a pointer to the previous node, because of the way the queue will
    function
 */
template <typename T>
struct Node {
    T value;
    Node* next;
    Node(const T& value) : value(value), next(nullptr) {}
};

template <typename T>
class Queue {
   private:
    // End of the queue & the number of elements (nodes)
    Node<T>* tail;
    uint size;

   public:
    // Constructor
    Queue() : tail(nullptr), size(0) {}


    /*  Copy-Constructor
        Because of the way queues work, the values can't be peeked and queued. The
        resulting queue would be reversed. To solved this, they are reversed first 
        using an array, and then enqueued in the right order 
    */
    Queue(const Queue& other) : tail(nullptr), size(0) {
        Node<T>* curr = other.tail;
        T *aux = new T[other.size];
        int id=0;
        while (curr) {
            aux[id++] = curr->value;
            curr = curr->next;
        }

        for(int i=other.size-1; i>=0; i--) {
            enqueue(aux[i]);
        }
        delete[] aux;
    }

    // Destructor
    ~Queue() {
        Node<T>* curr = tail;
        while (curr != nullptr) {
            Node<T>* aux = curr->next;
            delete curr;
            curr = aux;
        }
    }

    // The enqueue operation - adds an element in the queue
    void enqueue(const T& value) {
        Node<T>* ins = new Node<T>(value);
        if (tail) {
            ins->next = tail;
            tail = ins;
        } else {
            tail = ins;
        }
        size++;
    }

    // The dequeue operations - removes an element from the queue
    // It will return the removed value
    T dequeue() {
        if (size == 1) {
            T val = tail->value;
            delete tail;
            tail = nullptr;
            size--;
            return val;
        } else {
            T val = tail->value;
            Node<T>* aux = tail->next;
            delete tail;
            tail = aux;
            size--;
            return val;
        }
    }

    // Return the last element inserted in the queue, without removing it.
    T peek() const { return tail->value; }

    // Checks whether the queue is empty
    bool isEmpty() const { return (size == 0); }

    // Returns the number of elements in the queue
    int getSize() const { return int(size); }

    // Operator overload for output (print the values in the queue)
    // The first element added will be the first in the output and so on
    friend std::ostream& operator<<(std::ostream& output, const Queue& queue) {
        Node<T>* curr = queue.tail;
        T *aux = new T[queue.getSize()];
        int id = 0;

        while (curr) {
            aux[id++] = curr->value;
            curr = curr->next;
        }

        for(int i = queue.getSize() - 1; i>=0; i--) {
            output << aux[i] << " ";
        }

        delete[] aux;
        return output;
    }
};

#endif  // QUEUE_H_