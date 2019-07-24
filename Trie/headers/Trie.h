// Copyright 2019 Grama Nicolae
#ifndef TRIE_H_
#define TRIE_H_

/*  A trie (also know as a prefix tree, radix tree, etc), is a Search Tree 
    which allows for fast insertion and search (O(L), where L is the length
    of the key searched). This is a implementation for a trie that uses 
    strings as keys and any type T as values. It has a better time complexity
    than a BST and similar to a hastable. 

    It's advantages are the advanced searches, such as prefix search or
    searching for keys when they are misspelled (autocomplete).

    The dissadvantage of this structure is it's memory usage, which can vary a
    lot, depending on the data stored. 
*/


#define ALPHABET_SIZE 26  // The number of letters in the english alphabet

// The message to be returned when a word is not found
#define NO_RES_FOUND "! no definition found !"

#include <iostream>
#include <string>
#include <vector>

template <typename T>
class Trie {
   private:
    // Each node stores it's data/value, pointers to childrens, if it is
    // a End Of Word and the number of children it has
    class Node {
       private:
        T data;
        std::vector<Node*> children;
        bool isEOW;
        int nChild;

        // This is a method to determine the position of a character
        // in the alphabet
        static int getCharIndex(const char c) { return c - 'a'; }

       public:
        /*  Constructor
            In the case of a trie, the keys are not stored explicitly in the 
            nodes. Every link to a children has a letter "assigned" (child 0,
            'a', child 1 'b' and so on). By combining the links leading to a
            node, we get its key.
        */
        Node(const T& data = T())
            : data(data),
              children(std::vector<Node*>(ALPHABET_SIZE)),
              isEOW(false),
              nChild(0) {}

        // Destructor
        ~Node() {
            for(auto& i : children) {
                delete i;
            }
        }

        // Search for a key
        // (a similar algorithm is used also for insert and remove)
        T search(std::string key) {
            // If the key is null, we reached the destination
            if (key.length() == 0) {
                if (this->isEOW) {
                    // If the node is a end of word, the key we searched
                    // for exists
                    return this->data;
                } else {
                    // ... the key doesn't exist
                    return T();
                }
            }

            // Gets the path to the next node (get the first character of
            // the current key and gets its alphabetical order).
            Node* next = this->children[getCharIndex(key[0])];

            // Delete the first letter from the key
            key.erase(0, 1);

            // If there is nothing stored in the next node, the search ends
            if (next == nullptr) {
                return T();
            }

            // Search recursively using the updated key
            return next->search(key);
        }

        // Inserts a key in the trie
        void insert(std::string key, const T& value) {
            if (key.length() == 0) {
                this->data = value;
                // Mark the node as a End Of Word
                this->isEOW = true;
                return;
            }

            int next = getCharIndex(key[0]);
            // Remove first letter
            key.erase(0, 1);
            if (this->children[next] == nullptr) {
                this->children[next] = new Node();
                this->nChild++;
            }

            this->children[next]->insert(key, value);
        }

        // Removes a key from the trie
        bool remove(std::string key) {
            if (key.length() == 0) {
                this->data = T();
                if(this->nChild == 0 && !this->isEOW) {
                    // The node can be deleted
                    return true;
                }
            }

            int next = getCharIndex(key[0]);
            // Remove first letter
            key.erase(0, 1);
            
            if(this->children[next] != nullptr) {
                if(this->children[next]->remove(key)) {
                    delete this->children[next];
                    this->nChild--;
                    if(this->nChild == 0 && !this->isEOW) {
                        // If the node can be deleted
                        return true;
                    }
                }
            }
            return false;
        }
    };

    // The root of the trie (stores no letter)
    Node* root;
   public:
    // Constructor
    Trie() : root(new Node()) {}
    // Destructor
    ~Trie() { 
        delete root; 
    }

    // Search for a key and returns the associated value
    T search(std::string key) const { 
        std::string result = root->search(key); 
        if(result.length() == 0) {
            // If it will not find a value, returns the NO_RES_FOUND message
            result = NO_RES_FOUND;
        }
        return result;
    }

    // Checks if the trie contains a key
    bool contains(std::string key) const {
        return (root->search(key) == T()) ? false : true;
    }   

    // Insert/Remove a key/value pair from the trie
    void insert(std::string key, const T& value) { root->insert(key, value); }
    void remove(std::string key) { root->remove(key); }
};

#endif  // TRIE_H_