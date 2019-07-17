#include <iostream>

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

template <typename T>
struct Node {
    T value;
    Node<T>* next;
    Node<T>* prev;

    Node(T value) {
        this->value = value;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class LinkedList {
   private:
    Node<T>* first;
    Node<T>* last;
    int _size;

   public:
    LinkedList() : first(nullptr), last(nullptr), _size(0){};
    ~LinkedList() {}
    LinkedList(const LinkedList& other) {}

    void addFirst(const T& value) {
        Node<T> *add = new Node<T>(value);

        if(first) {
            add->next = first;
            add->prev = nullptr;
            first->prev = add;
            first = add;
        } else {
            first = add;
            first->next = nullptr;
            first->prev = nullptr;
            last = first;
        }
        _size++;
    }

    void addLast(const T& value) {
        Node<T> *add = new Node<T>(value);

        if(first) {
            add->prev = last;
            add->next = nullptr;
            last->next = add;
            last = add;
        } else {
            first = add;
            first->next = nullptr;
            first->prev = nullptr;
            last = first;
        }
        _size++;
    }

    void removeFirst() {
        if(_size > 1) {
            Node<T> *aux = first->next;
            delete first;
            first = aux;
            first->prev = nullptr;
        } else {
            first = nullptr;
            last = nullptr;
            _size = 0;
        }

        if(_size>0) {
            _size--;
        }
        
    }

    void removeLast() {
        if(_size==1) {
            first = nullptr;
            last = nullptr;
            _size = 0;
            return;
        }

        if(last) {
            Node<T> *aux = last->prev;
            delete last;
            last = aux;
            last->next = nullptr;
            if(_size>0) {
                _size--;
            }
        }     
    }

    int getSize() const { return _size; }

    bool hasElement(const T& element) const { 
        Node<T> *curr = first;
        if(_size != 0) {
            do {
                if(curr->value == element) {
                    return true;
                } else {
                    curr = curr->next; 
                }
            } while (curr!=nullptr);
        }
        return false;
    }

    T getElement(int id) const {
        if(id>=_size) {
            return T(NULL);
        }

        Node<T> *curr = first;
        int counter = 0;
        if(_size != 0) {
            do {
                if(counter==id) {
                    return curr->value;
                } else {
                    counter++;
                    curr = curr->next; 
                }
            } while (curr!=nullptr);
        }
        return T(NULL);
    }

    T getHead() {
        return first->value;
    }

    T getTail() {
        return last->value;
    }

    void printInverse() {
        Node<T> *curr = last;
        if(_size != 0) {
            do {
                std::cout << curr->value << " ";
                curr = curr->prev;
            } while (curr!=nullptr);
        }
        std::cout << "\n";
    }

    friend std::ostream& operator<<(std::ostream& output,
                                    const LinkedList& list) {
        Node<T> *curr = list.first;
        if(list._size != 0) {
            do {
                output << curr->value << " ";
                curr = curr->next;
            } while (curr!=nullptr);
        }
        return output;
    }
};

#endif  // LINKEDLIST_H_