/*
    Author: Franklin Doane
    Date created: 21 December 2024
    Purpose: hash table class
*/

// file guards
#ifndef HASHTABLE_H
#define HASHTABLE_H

// includes
#include <string>
#include <vector>

// namespace
using std::string;
using std::vector;

// linked list class
class Node {

    private:

        string value;
        Node* next;

    public:

        // default constructor
        Node() {

            string value = "";
            Node* next = nullptr;
        }
        
        // constructor
        Node(string nodeValue) {

            string value = nodeValue;
            Node* next = nullptr;
        }

        // destructor
        ~Node() {

            if (next != nullptr) {

                delete next;
            }
        }

        // access next
        Node* getNext() {

            return next;
        }

        // access next
        string getValue() {

            return value;
        }

        // mutate next
        void setNext(Node* nextNode) {

            next = nextNode;
        }

};

// hash table class
class HashTable {

    private:

        // table
        Node** table;

        // nodes for deletion put together
        vector<Node*> valuesInTable;

        // number of indexes
        int tableSize;

        // string index to add to ascii value for string hash
        const int ASCII_ADD_IND = 4;

    public:

        // default constructor
        HashTable() {

            table = nullptr;
            tableSize = 0;
        }

        // constructor
        HashTable(int size) {

            table = new Node*[size]();
            tableSize = size;
        }

        // destructor
        ~HashTable() {

            // iterate through indexes
            for (int i = 0; i < tableSize; i ++) {

                // delete index if not empty
                if (table[i] != nullptr) {

                    delete table[i];
                }
            }

            delete [] table;
        }

        // raw hashing function
        int hash(int key) {

            return key % tableSize;
        }

        // string hashing function
        int strHash(string key) {

            // check if key has min characters
            if (key.length() >= ASCII_ADD_IND + 1) {

                // hash with the ascii value of the nth character added to the length
                return this->hash(key.length() + key.at(ASCII_ADD_IND));

            }
            // otherwise add the first character
            else {

                // hash with the ascii value of the nth character added to the length
                return this->hash(key.length() + key.at(0));

            }

        }

        // insert string into the hash table
        void insert(string str) {

            // hash 
            int index = this->strHash(str);

            // create node 
            Node* newNode = new Node(str);

            // if empty index, insert value
            if (table[index] == nullptr) {

                // insert
                table[index] = newNode;

            }

            // handle collision with chaining
            else {

                // node tracker
                Node* currentNode = table[index];

                // while next node isn't nullptr
                while (currentNode->getNext() != nullptr) {

                    currentNode = currentNode->getNext();

                }

                // insert
                currentNode->setNext(newNode);

            }

            // add nodes to list to delete
            valuesInTable.push_back(newNode);

        }

        // search if a string has been inserted into the table
        bool search(string str) {

            // hash 
            int index = this->strHash(str);

            // check for value at index
            if (table[index]->getValue() == str) {

                return true;
            }
            // check for empty index
            else if (table[index] == nullptr) {

                return false;
            }
            // chain
            else {

                // tracker node
                Node* currentNode = table[index];

                // while next node isn't nullptr
                while (currentNode->getNext() != nullptr) {

                    currentNode = currentNode->getNext();
                    
                    // check if the current node value is the str
                    if (currentNode->getValue() == str) {

                        return true;
                    }

                }

                return false;

            }

        }

        void saveToFile();

};



#endif
