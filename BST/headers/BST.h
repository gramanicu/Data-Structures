// Copyright 2019 Grama Nicolae
#ifndef BST_H_
#define BST_H_

/*
    A binary search tree is a optimized binary tree. Because of the
    way the nodes are inserted, the search is faster than in a simple
    binary tree. The data stored in the nodes is called keys. For each
    node, it's left child has a key smaller than his, and the right one
    has a key bigger. So, the smallest element in the tree is in the
    bottom left, and the biggest one is located on the bottom right.
*/

#include <iostream>
#include <queue>
#include <vector>

template <typename T>
class BST {
   private:
    /*  A class for the nodes
        It is pretty much the same the same node structure from the
        simple binary tree.
     */
    class Node {
       private:
        Node* left;
        Node* right;
        T data;

       public:
        Node(const T& data) : left(nullptr), right(nullptr), data(data){};
        ~Node() {
            delete left;
            delete right;
        }

        void setData(const T& data) { this->data = data; }
        T getData() const { return data; }

        void setLeft(const T& data) { left = new Node(data); }
        void setRight(const T& data) { right = new Node(data); }

        Node* getLeft() { return left; }
        Node* getRight() { return right; }

        Node* cGetLeft() const { return left; };
        Node* cGetRight() const { return right; };
    };

    // The root of the tree
    Node* root;
    // The number of nodes stored
    int size;

    /*  This method will return a list with all the children of the specified
        node. This is used when deleting a node, to reinsert it's children
        back in the BST.
    */
    static std::vector<T> allChildren(const Node* node) {
        std::vector<T> out;

        if (node->cGetLeft()->getData() != T()) {
            std::vector<T> aux = allChildren(node->cGetLeft());
            out.insert(out.end(), aux.begin(), aux.end());
        }
        out.push_back(node->getData());
        if (node->cGetRight()->getData() != T()) {
            std::vector<T> aux = allChildren(node->cGetRight());
            out.insert(out.end(), aux.begin(), aux.end());
        }

        return out;
    }

   public:
    // Constructor
    BST() : root(nullptr), size(0){};
    // Destructor
    ~BST() { delete root; }

    // Insert a node in the BST
    void insert(const T& key, Node* node = nullptr) {
        if (node == nullptr) {
            if (size == 0) {
                root = new Node(T());
            }
            node = root;
        }

        if (node->getData() == T()) {
            node->setData(key);
            node->setLeft(T());
            node->setRight(T());
            size++;
            return;
        }

        if (key == node->getData()) {
            return;
        }

        if (key > node->getData()) {
            insert(key, node->getRight());
        } else {
            insert(key, node->getLeft());
        }
    }

    // Deletes a node from the BST
    // (! this method generates some memory problems !)
    void remove(const T& key, Node* node = nullptr) {
        if (size == 0) {
            return;
        } else {
            if (node == nullptr) {
                node = root;
            }

            if (key == node->getData()) {
                std::vector<T> toInsert;
                if (node->getLeft()->getData() != T()) {
                    std::vector<T> aux = allChildren(node->getLeft());
                    toInsert.insert(toInsert.end(), aux.begin(), aux.end());

                    if (node != root) {
                        delete node->getLeft();
                    }
                }

                if (node->getRight()->getData() != T()) {
                    std::vector<T> aux = allChildren(node->getRight());
                    toInsert.insert(toInsert.end(), aux.begin(), aux.end());
                    if (node != root) {
                        delete node->getRight();
                    }
                }

                if (node == root) {
                    delete root->getLeft();
                    delete root->getRight();
                }

                node->setData(T());
                size--;

                for (auto& i : toInsert) {
                    insert(i);
                }
            } else if (key < node->getData()) {
                remove(key, node->getLeft());
            } else {
                remove(key, node->getRight());
            }
        }
    }

    // Search for a node in the BST
    bool search(const T& key, Node* node = nullptr) const {
        if (size == 0) {
            return false;
        }

        if (node == nullptr) {
            node = root;
        }

        if (node->getData() == T()) {
            return false;
        }

        if (node->getData() == key) {
            return true;
        }

        if (node->getData() > key) {
            return search(key, node->getLeft());
        } else {
            return search(key, node->getRight());
        }
    }

    // Returns the smallest key in the BST
    T getMin() const {
        if (size == 0) {
            return T();
        } else {
            Node* curr = root;
            while (curr->getLeft()->getData() != T()) {
                curr = curr->getLeft();
            }
            return curr->getData();
        }
    }

    // Returns the biggest key in the BST
    T getMax() const {
        if (size == 0) {
            return T();
        } else {
            Node* curr = root;
            while (curr->getRight()->getData() != T()) {
                curr = curr->getRight();
            }
            return curr->getData();
        }
    }

    // Returns the number of keys in the BST
    int getSize() const { return size; }

    // Prints all the elements stored in the BST (in "preorder" - current node
    // left child, right child)
    friend std::ostream& operator<<(std::ostream& output, const BST& tree) {
        std::vector<T> v;
        std::queue<Node*> q;
        q.push(tree.root);

        while (!q.empty()) {
            Node* curr = q.front();
            if (curr->getData() != T()) {
                v.push_back(curr->getData());
                q.push(curr->getLeft());
                q.push(curr->getRight());
            }
            q.pop();
        }

        for (auto& i : v) {
            output << i << " ";
        }

        return output;
    }
};

#endif  // BST_H_