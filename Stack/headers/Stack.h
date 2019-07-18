// Copyright Grama Nicolae 2019
#ifndef STACK_H_
#define STACK_H_

/*  This is a implementation of a stack. The data is stored in nodes,
    linked using pointers. This means that the stack can use all the
    memory the computer has available, as it doesn't need a continous
    block of memory.

    The stack is a data structure based on the LIFO principle (last
    in, first out). This means any new node is added at the end of
    the "list", but only the first one will be accessible, and can
    be removed.
*/

#include <iostream>

/*  A data structure in which values are stored, the base of the stack.
    Beside the value, it will store a pointer to the next node. It doesn't
    need a pointer to the previous node, because of the way the stack will
    function
 */
template <typename T>
struct Node {
    T value;
    Node* next;
    Node(const T& value) : value(value), next(nullptr) {}
};

template <typename T>
class Stack {
   private:
    // Start & end of the stack & the number of elements (nodes)
    Node<T>* head;
    Node<T>* tail;
    uint size;

   public:
    // Constructor, Copy-Constructor and Destructor
    Stack() : head(nullptr), tail(nullptr), size(0) {}
    Stack(const Stack& other) : head(nullptr), tail(nullptr), size(0) {
        Node<T>* curr = other.head;
        while (curr) {
            push(curr->value);
            curr = curr->next;
        }
    }
    ~Stack() {
        Node<T>* curr = head;
        while (curr != nullptr) {
            Node<T>* aux = curr->next;
            delete curr;
            curr = aux;
        }
    }

    // The push operations - adds an element at the end (tail) of the stack
    void push(const T& value) {
        Node<T>* ins = new Node<T>(value);
        if (head) {
            tail->next = ins;
            tail = ins;
        } else {
            head = ins;
            tail = ins;
        }
        size++;
    }

    // The pop operations - removes the first element (head) of the stack
    // It will return the removed value
    T pop() {
        if (size == 1) {
            T val = head->value;
            delete head;
            head = nullptr;
            tail = nullptr;
            size--;
            return val;
        } else {
            T val = head->value;
            Node<T>* aux = head->next;
            delete head;
            head = aux;
            size--;
            return val;
        }
    }

    // Return the first element in the stack, withouth removing it.
    T peek() const { return head->value; }

    // Checks whether the stack is empty
    bool isEmpty() const { return (size == 0); }

    // Returns the number of elements in the stack
    int getSize() const { return int(size); }

    // Operator overload for output (print the values in the stack)
    friend std::ostream& operator<<(std::ostream& output, const Stack& stack) {
        Node<T>* curr = stack.head;
        while (curr) {
            output << curr->value << " ";
            curr = curr->next;
        }

        return output;
    }
};

#endif  // STACK_H_