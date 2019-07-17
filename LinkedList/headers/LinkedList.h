#include <iostream>

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

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
    Node<T> *first;
    Node<T> *last;
    int _size;

   public:
    explicit LinkedList() : first(nullptr), last(nullptr), _size(0) {}
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

    void addFirst(const T &value) {
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

    void addLast(const T &value) {
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

    int getSize() const { return _size; }

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

    T getElement(int id) const {
        if (id >= _size) {
            return T(NULL);
        }

        Node<T> *curr = first;
        int counter = 0;
        if (_size != 0) {
            do {
                if (counter == id) {
                    return curr->value;
                } else {
                    counter++;
                    curr = curr->next;
                }
            } while (curr != nullptr);
        }
        return T(NULL);
    }

    T getHead() { return first->value; }

    T getTail() { return last->value; }

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