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

// namespace
using std::string;

// linked list struct
struct Node {
    string value;
    Node* next;
};

// hash table class
class HashTable {

    private:

        // table
        Node** table;

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

        // raw hashing function
        int hash(int key) {

            return key % tableSize;
        }

        // string hashing function
        int strHash(string key) {

            // check if key has min characters
            if (key.length() >= ASCII_ADD_IND + 1) {

                // hash with the ascii value of the nth character added to the length
                return this->hash(key.length() + key.at(ASCII_ADD_IND))

            }
            // otherwise add the first character
            else {

                // hash with the ascii value of the nth character added to the length
                return this->hash(key.length() + key.at(0))

            }

        }

        // insert string into the hash table
        void insert(string str) {

            // hash 
            int index = this->strHash(str);

            // create node 
            Node* newNode = new Node;
            newNode->value = str;
            newNode->next = nullptr;

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
                while (currentNode->next != nullptr) {

                    currentNode = currentNode->next;

                }

                // insert
                currentNode->next = newNode;

            }

        }

        // search if a string has been inserted into the table
        bool search(string str) {

            // hash 
            int index = this->strHash(str);

            // check for value at index
            if (table[index]->value == str) {

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
                while (currentNode->next != nullptr) {

                    currentNode = currentNode->next;
                    
                    // check if the current node value is the str
                    if (currentNode->value == str) {

                        return true;
                    }

                }

                return false;

            }

        }

        void saveToFile();
        
};



#endif
