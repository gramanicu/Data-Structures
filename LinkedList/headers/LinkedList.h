#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

/*  This is a implementation of an double linked list. The data is
    not stored in a continuous block of memory. This can result in
    slower data access (as you can't access the n'th element directly)
    but it can use all available memory, as the list is dynamically
    allocated.
*/

#include <iostream>

/*  Node - an element of the list
    It stores a value, and pointer to the next and previous node
    in the list
*/
template <typename T>
struct Node {
    T value;
    Node<T> *next;
    Node<T> *prev;

    explicit Node(T value) {
        this->value = value;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class LinkedList {
   private:
    Node<T> *first;  // The first node of the list ("head")
    Node<T> *last;   // The last element of the list ("tail")
    int _size;       // The number of elements

   public:
    // Constructor
    explicit LinkedList() : first(nullptr), last(nullptr), _size(0) {}

    // Destructor
    ~LinkedList() {
        Node<T> *curr = first;
        if (_size != 0) {
            do {
                Node<T> *aux = curr->next;
                delete curr;
                curr = aux;
            } while (curr != nullptr);
        }
    }

    // Copy-Constructor
    LinkedList(const LinkedList &other)
        : first(nullptr), last(nullptr), _size(0) {
        Node<T> *curr = other.first;
        if (other.getSize() != 0) {
            do {
                addLast(curr->value);
                curr = curr->next;
            } while (curr != nullptr);
        }
    }

    // Adds an element at the start of the list
    void addFirst(const T &value) {
        // Check if the list is not empty
        if (first) {
            Node<T> *add = new Node<T>(value);
            add->next = first;
            add->prev = nullptr;
            first->prev = add;
            first = add;
        } else {
            Node<T> *add = new Node<T>(value);
            first = add;
            add->prev = nullptr;
            add->next = nullptr;
            last = add;
        }
        _size++;
    }

    // Adds an element at the end of the list
    void addLast(const T &value) {
        // Check if the list is not empty
        if (first) {
            Node<T> *add = new Node<T>(value);
            add->prev = last;
            add->next = nullptr;
            last->next = add;
            last = add;
        } else {
            Node<T> *add = new Node<T>(value);
            first = add;
            first->next = nullptr;
            first->prev = nullptr;
            last = first;
        }
        _size++;
    }

    // Removes the first element
    void removeFirst() {
        if (_size > 1) {
            Node<T> *aux = first->next;
            delete first;
            first = aux;
            first->prev = nullptr;
        } else {
            delete first;
            first = nullptr;
            last = nullptr;
            _size = 0;
        }

        if (_size > 0) {
            _size--;
        }
    }

    // Removes the last element
    void removeLast() {
        if (_size == 1) {
            delete first;
            first = nullptr;
            last = nullptr;
            _size = 0;
            return;
        }

        if (last) {
            Node<T> *aux = last->prev;
            delete last;
            last = aux;
            last->next = nullptr;
            if (_size > 0) {
                _size--;
            }
        }
    }

    // Returns the current number of elements
    int getSize() const { return _size; }

    // Checks if the list contains an element
    bool hasElement(const T &element) const {
        Node<T> *curr = first;
        if (_size != 0) {
            do {
                if (curr->value == element) {
                    return true;
                } else {
                    curr = curr->next;
                }
            } while (curr != nullptr);
        }
        return false;
    }

    // Returns the n'th element
    T getElement(int n) const {
        if (n >= _size) {
            return T(NULL);
        }

        Node<T> *curr = first;
        int counter = 0;
        if (_size != 0) {
            do {
                if (counter == n) {
                    return curr->value;
                } else {
                    counter++;
                    curr = curr->next;
                }
            } while (curr != nullptr);
        }
        return T(NULL);
    }

    // Returns the first element
    T getHead() { return first->value; }

    // Returns the last element
    T getTail() { return last->value; }

    // Prints the list from tail to head (to show the double links)
    void printInverse() {
        Node<T> *curr = last;
        if (_size != 0) {
            do {
                std::cout << curr->value << " ";
                curr = curr->prev;
            } while (curr != nullptr);
        }
        std::cout << "\n";
    }

    // Operator overload for output
    friend std::ostream &operator<<(std::ostream &output,
                                    const LinkedList &list) {
        Node<T> *curr = list.first;
        if (list._size != 0) {
            do {
                output << curr->value << " ";
                curr = curr->next;
            } while (curr != nullptr);
        }
        return output;
    }
};

#endif  // LINKEDLIST_H_