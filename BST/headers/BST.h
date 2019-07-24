// Copyright 2019 Grama Nicolae
#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <queue>
#include <vector>

template <typename T>
class BST {
   private:
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

        Node* cGetLeft() const {return left;};
        Node* cGetRight() const {return right;};
    };

    Node* root;
    int size;

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
    BST() : root(nullptr), size(0){};
    ~BST() { delete root; }

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

                    if(node != root) { 
                        delete node->getLeft();
                    }
                }

                if (node->getRight()->getData() != T()) {
                    std::vector<T> aux = allChildren(node->getRight());
                    toInsert.insert(toInsert.end(), aux.begin(), aux.end());
                    if(node != root) {
                        delete node->getRight();
                    }
                }

                if(node == root) {
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

    int getSize() const { return size; }

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