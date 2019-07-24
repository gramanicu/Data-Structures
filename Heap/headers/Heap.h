// Copyright 2019 Grama Nicolae
#ifndef HEAP_H_
#define HEAP_H_

/*  A heap is another type of binary tree, with the advantage
    of a linear representation, meaning that it doesn't need pointers
    and can be used to store the tree in a file.

    This is actually a min-heap, but it's not that different from a max-heap.
    In a min heap, every child of a "node" is bigger or equal to the node.
*/

#include <iostream>
#include <vector>


// Operator overload to display the content of a vector
template <typename T>
std::ostream& operator<<(std::ostream& output, const std::vector<T> v) {
    for(auto& i : v) {
        output << i << " ";
    }
    return output;
} 

template <typename T>
class Heap {
   private:
    // The vector that contains the nodes
    std::vector<T> node;

    /*  The push up (and push down) are two important methods for a heap
        As the elements of a heap are inserted at the end, to ensure they
        have the correct order, they are "pushed up" to their place.

        We take every element (starting from the back) and compare it to
        its parent (we find the parent using a mathematical formula). If
        it is smaller than it's parent, we swap them (bigger for a max-heap).

        The algorithm continues until we made no change to the vector.
    */
    void pushUp() {
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = node.size() - 1; i >= 0; i--) {
                if (node[parent(i)] > node[i]) {
                    std::swap(node[i], node[parent(i)]);
                    changed = true;
                }
            }
        }
    }

    /*  Push down method. When we delete the first element, the last element
        takes it's place. Then, it will be "pushed down" to it's place. To do
        this, we compare every element (starting from the first) to its
        children. If it is bigger than at least one of them, we swap them.

        This algorithm continues until we made no change to the vector.
    */
    void pushDown() {
        bool changed = true;
        while (changed) {
            changed = false;
            for (int i = 0; i < int(node.size()); i++) {
                int r = right(i);
                int l = left(i);

                if(r > int(node.size())-1) {
                    r = i;
                }

                if(l > int(node.size())-1) {
                    l = i;
                }

                if(node[i]>node[l]) {
                    std::swap(node[i], node[l]);
                    changed = true;
                } else if(node[i] > node[r]) {
                    std::swap(node[i], node[r]);
                    changed = true;
                }
            }
        }
    }

    // The next 3 methods are used to determine the positions of the
    // node's parent, left child and right child.
    static int parent(const int index) { return (index - 1) / 2; }
    static int left(const int index) { return 2 * index + 1; }
    static int right(const int index) { return 2 * index + 2; }

   public:
    // Constructor
    Heap() {}
    // Destructor
    ~Heap() {}
    // Copy-Constructor
    Heap(const Heap& other) { node = other.node; }

    // Insert a value in the heap
    void push(const T& value) {
        node.push_back(value);
        pushUp();
    }

    // Returns the first value in the heap (smallest number)
    T peek() const { return node[0]; }

    // Removes the first element in the heap and returns it
    T pop() {
        T rem = node[0];
        node[0] = node[node.size() - 1];
        node.pop_back();
        pushDown();
        return rem;
    }

    // Returns the number of elements in the heap
    int size() const {
        return node.size();
    }

    // Returns a vector containing all elements of the heap, sorted 
    // in ascending order
    std::vector<T> sort() const {
        std::vector<T> sorted;
        Heap other = *this;

        while(other.size()!=0) {
            sorted.push_back(other.pop());
        }

        return sorted;
    }

    // Returns a vector with the heap's nodes
    std::vector<T> getNodes() const { return node; }

    // Operator overload for output, to print or save the heap
    friend std::ostream& operator<<(std::ostream& output, const Heap& h) {
        for (auto& i : h.getNodes()) {
            output << i << " ";
        }
        return output;
    }
};

#endif  // HEAP_H_