#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

#include <memory.h>
#include <iostream>
#define defaultSize 100

template <typename T>
class ArrayList {
   private:
    T* elements;
    int _size;
    int _eFactor;
    int _cSize = 0;

    void resize() {
        _size += _eFactor;
        T* newArr = new T[_size];
        memcpy(newArr, elements, (_size - _eFactor) * sizeof(T));
        delete[] elements;
        elements = newArr;
    }

    void shiftRight() {
        _size += 1;
        T* newArr = new T[_size];
        memcpy(newArr + 1, elements, (_size - 1) * sizeof(T));
        delete[] elements;
        elements = newArr;
    }

    void shiftLeft() {
        _size -= 1;
        T* newArr = new T[_size];
        memcpy(newArr, elements + 1, _size * sizeof(T));
        delete[] elements;
        elements = newArr;
    }

   public:
    ArrayList() {
        _size = defaultSize;
        _eFactor = _size;
        elements = new T[_size];
    }

    ArrayList(const int size) : _size(size) {
        elements = new T[_size];
        _eFactor = _size;
    }

    ArrayList(const ArrayList& other) {}

    ~ArrayList() { delete[] elements; }

    int size() const { return _cSize; }

    void addFirst(const T& element) {
        shiftRight();
        elements[0] = element;
        _cSize++;
    }

    void addLast(const T& element) {
        if (_cSize + 1 >= _size) {
            resize();
        }

        elements[_cSize] = element;
        _cSize++;
    }

    void removeFirst() {
        shiftLeft();
        _cSize--;
    }

    void removeLast() {
        elements[_cSize] = 0;
        _cSize--;
    }

    bool isEmpty() const {
        if (_cSize) {
            return true;
        } else {
            return false;
        }
    }

    T getElement(const int id) const {
        if (id < _size) {
            return elements[id];
        } else {
            return 0;
        }
    }

    friend std::ostream& operator<<(std::ostream& output,
                                    const ArrayList& list) {
        for (int i = 0; i < list.size(); i++) {
            output << list.getElement(i) << " ";
        }
        return output;
    }
};

#endif  // ARRAYLIST_H_