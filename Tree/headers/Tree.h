// Copyright 2019 Grama Nicolae
#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include <queue>
#include <vector>

// A operator overload to display a vector's content
template <typename T>
std::ostream& operator<<(std::ostream& output, const std::vector<T> v) {
    for (auto& i : v) {
        output << i << " ";
    }
    return output;
}

template <typename T>
class Tree {
   private:
    // The nodes from which the binary tree is build
    class Node {
       private:
        Node* left;         // Left Child
        Node* right;        // Right Child
        T data;             // The data stored in the node

       public:
        // Constructor
        Node(const T& data) : left(nullptr), right(nullptr), data(data) {};
        // Destructor
        ~Node() {
            delete left;
            delete right;
        }

        // Get/Set data in the node
        void setData(const T& data) { this->data = data; }
        T getData() const { return data; }

        // Set right/left child
        void setLeft(const T& data) { left = new Node(data); }
        void setRight(const T& data) { right = new Node(data); }

        // Get a pointer to the right/left child
        Node* getLeft() { return left; }
        Node* getRight() { return right; }
    };

    int size;           // The number of nodes in the BST
    Node* root;         // The root of the bst

   public:
    // Constructor
    Tree() : size(0), root(nullptr) {}
    // Destructor
    ~Tree() { delete root; }

    // Insert a new node in the tree (using a "preorder Traversal").
    // It will look if the current node is free, if not, it will insert it
    // in the left child, then right child
    void insert(const T& data) {
        if (size == 0) {
            root = new Node(data);
            root->setLeft(T());
            root->setRight(T());
            size++;
        } else {
            std::queue<Node*> q;
            q.push(root->getLeft());
            q.push(root->getRight());
            
            while (!q.empty()) {
                Node* curr = q.front();
                if (curr->getData() == T()) {
                    curr->setData(data);
                    curr->setLeft(T());
                    curr->setRight(T());

                    size++;
                    return;
                } else {
                    q.pop();
                    q.push(curr->getLeft());
                    q.push(curr->getRight());
                }
            }
        }
    }

    // Returns a vector with all the elements in the BT, using a preorder
    // traversal
    std::vector<T> traversal() {
        std::vector<T> v;
        std::queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* curr = q.front();
            if (curr->getData() != T()) {
                v.push_back(curr->getData());
                q.push(curr->getLeft());
                q.push(curr->getRight());
            }
            q.pop();
        }

        return v;
    }
};

#endif  // TREE_H_