// Copyright Grama Nicolae 2019
#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_
/*  This is a implementation of an array list. The data is
    stored in a continuous block of memory. This means faster
    access, but it can lead to some problems (the computer
    doesn't have enough memory in a continuous block).
*/

#include <memory.h>
#include <iostream>

// The default size for the underlying array
#define defaultSize 100

template <typename T>
class ArrayList {
   private:
    T* elements;     // The data, stored as an array
    int _size;       // The size of the array
    int _eFactor;    // By how much should the array expand
    int _cSize = 0;  // The current number of elements stored

    /*  Expand the array. A new array is created, in which the old data is
        copied. Then, the old array is replaced with the new one. */
    void resize() {
        _size += _eFactor;
        T* newArr = new T[_size];
        memcpy(newArr, elements, (_size - _eFactor) * sizeof(T));
        delete[] elements;
        elements = newArr;
    }

    /*  Moves all the data in the array one "cell" to the right. This is used to
        create a space for a new element at the beggining of the array */
    void shiftRight() {
        _size += 1;
        T* newArr = new T[_size];
        memcpy(newArr + 1, elements, (_size - 1) * sizeof(T));
        delete[] elements;
        elements = newArr;
    }

    /*  Moves all the data in the array one "cell" to the left. This is used to
        delete the first element of the array and remove the extra space */
    void shiftLeft() {
        _size -= 1;
        T* newArr = new T[_size];
        memcpy(newArr, elements + 1, _size * sizeof(T));
        delete[] elements;
        elements = newArr;
    }

   public:
    // Constructor - defaultSize will be the initial array size
    ArrayList() {
        _size = defaultSize;
        _eFactor = _size;
        elements = new T[_size];
    }

    // Constructor - the array will have the specified size
    ArrayList(const int size) : _size(size) {
        elements = new T[_size];
        _eFactor = _size;
    }

    // Copy-Constructor
    ArrayList(const ArrayList& other) {
        elements = new T[other._size];
        _size = other._size;
        _eFactor = other._eFactor;
        _cSize = other._cSize;
        memcpy(elements, other.elements, other._cSize * sizeof(T));
    }

    // Destructor
    ~ArrayList() { delete[] elements; }

    // Returns the number of elements
    int size() const { return _cSize; }

    // Adds an element at the start of the list
    void addFirst(const T& element) {
        shiftRight();
        elements[0] = element;
        _cSize++;
    }

    // Adds an element at the end of the list
    void addLast(const T& element) {
        if (_cSize + 1 >= _size) {
            resize();
        }

        elements[_cSize] = element;
        _cSize++;
    }

    // Removes the first element
    void removeFirst() {
        shiftLeft();
        _cSize--;
    }

    // Removes the last element
    void removeLast() {
        elements[_cSize] = 0;
        _cSize--;
    }

    // Checks if the list is empty
    bool isEmpty() const {
        if (_cSize) {
            return true;
        } else {
            return false;
        }
    }

    // Returns the n'th element
    T getElement(const int n) const {
        if (n < _size) {
            return elements[n];
        } else {
            return 0;
        }
    }

    // Operator overload for output
    friend std::ostream& operator<<(std::ostream& output,
                                    const ArrayList& list) {
        for (int i = 0; i < list.size(); i++) {
            output << list.getElement(i) << " ";
        }
        return output;
    }
};

#endif  // ARRAYLIST_H_