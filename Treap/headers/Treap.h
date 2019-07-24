// Copyright 2019 Grama Nicolae
#ifndef TREAP_H_
#define TREAP_H_

#include <iostream>
#include <random>

template <typename T>
class Treap {
   private:
    class Node {
       private:
        T key;
        int priority;

        int generatePriority() const {
            std::mt19937 generator;
            std::uniform_int_distribution<int32_t> distribution;
            std::random_device trueRNG;

            // Seed the generator
            generator = std::mt19937(trueRNG());

            // Initialise the distribution
            distribution = std::uniform_int_distribution<int32_t>();

            // Generate and return the random number
            int randomPriority = distribution(generator);
            return randomPriority%100;
        }

       public:
        // This field are public to simplify the code
        Node *left, *right;

        // Constructor
        Node(const T& key)
            : key(key),
              left(nullptr),
              right(nullptr) {
                  priority = generatePriority();
              }
        // Destructor
        ~Node() {
            delete left;
            delete right;
        }

        // Setters
        void setKey(const T& key) { this->key = key; }
        void setLeft(Node* node) { left = node; }
        void setRight(Node* node) { right = node; }

        // Getters
        T getKey() const { return key; }
        int getPriority() const { return priority; }
        Node* getLeft() { return left; }
        Node* getRight() { return right; }
    };

    Node* root;
    int size;

    Node* rotateRight(Node* toRotate) {
        Node* lChild = toRotate->left;
        Node* rlGrandchild = lChild->right;

        lChild->right = toRotate;
        toRotate->left = rlGrandchild;
        return lChild;
    }

    Node* rotateLeft(Node* toRotate) {
        Node* rChild = toRotate->right;
        Node* lrGrandchild = rChild->left;

        rChild->left = toRotate;
        toRotate->right = lrGrandchild;
        return rChild;
    }

    Node* _insert(Node* _root, const T& key) {
        if (!_root) {
            return new Node(key);
        }

        if (key <= _root->getKey()) {
            // Insert in left subtree
            _root->left = _insert(_root->left, key);

            if (_root->left->getPriority() > _root->getPriority()) {
                _root = rotateRight(_root);
            }
        } else {
            // Insert in right substree
            _root->right = _insert(_root->right, key);

            if (_root->right->getPriority() > _root->getPriority()) {
                _root = rotateLeft(_root);
            }
        }
        return _root;
    }

    void _inorder(Node* _root) {
        if (_root) {
            _inorder(_root->left);
            std::cout << "key: " << _root->getKey()
                   << " | priority: " << _root->getPriority();
            if (_root->left) {
                std::cout << " | left child : " << _root->left->getKey();
            }
            if (_root->right) {
                std::cout << " | right child : " << _root->right->getKey();
            }

            std::cout << "\n";
            _inorder(_root->right);
        }
    }

    Node* _delete(Node* _root,const T& key) {
        if(_root == nullptr) {
            return _root;
        }

        if(key < _root->getKey()) {
            _root->left = _delete(_root->left, key);
        } else if (key > _root->getKey()) {
            _root->right = _delete(_root->right, key);
        } else if (_root->left == nullptr) {
            Node *temp = _root->right;
            delete(_root);
            _root = temp;
        } else if (_root->right == nullptr) {
            Node *temp = _root->left;
            delete(_root);
            _root = temp;
        } else if(_root->left->getPriority() < _root->right->getPriority()) {
            _root = rotateLeft(_root);
            _root->right = _delete(_root->left, key);
        } else {
            _root = rotateRight(_root);
            _root->right = _delete(_root->right, key);
        }
        return _root;
    }

    Node* _search(Node* _root, const T& key) {
        if(_root == nullptr || _root->getKey() == key) {
            return _root;
        }

        if(_root->getKey() < key) {
            return _search(_root->right, key);
        }

        return _search(_root->left, key);
    }

   public:
    Treap() : root(nullptr), size(0) {}
    ~Treap() { delete root; }

    void insert(const T& key) { root = _insert(root, key); }

    void remove(const T& key) {
        root = _delete(root, key);
    }

    bool search(const T& key) {
        return (_search(root, key)) ? false : true;
    }

    void inorder() {
        _inorder(root);
    }
};

#endif  // TREAP_H_