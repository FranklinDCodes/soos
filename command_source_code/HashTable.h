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
#include <iostream>
#include <iomanip>

// namespace
using std::string;
using std::vector;
using std::cout, std::endl, std::ostream;
using std::setw, std::left;

// constants

// string index to add to ascii value for string hash
const int ASCII_ADD_IND = 4;


// linked list class
template <typename t>
class Node {

    private:

        t value;
        Node* next;

    public:

        // default constructor
        Node() {

            t = NULL;
            next = nullptr;
        }
        
        // constructor
        Node(t nodeValue) {

            t = nodeValue;
            next = nullptr;
        }

        // destructor
        ~Node() {

            if (next != nullptr) {

                delete next;
            }
        }

        // access next
        Node* getNext() const {

            return next;
        }

        // access next
        t getValue() const {

            return value;
        }

        // mutate next
        void setNext(Node* nextNode) {

            next = nextNode;
        }

};

// hash table class
template <typename T>
class HashTable {

    private:

        // table
        Node<T>** table;

        // nodes for deletion put together
        vector<Node<T>*> valuesInTable;

        // number of indexes
        int tableSize;

    public:

        // default constructor
        HashTable() {

            table = nullptr;
            tableSize = 0;
        }

        // constructor
        HashTable(int size) {

            table = new Node<T>*[size]();
            tableSize = size;
        }

        // destructor
        ~HashTable() {

            // delete all the items that were added to the table
            for (Node<T>* ptr : valuesInTable) {

                delete ptr;
            }

            delete [] table;
        }

        // raw hashing function
        int hash(int key) const {

            return key % tableSize;
        }

        // string hashing function
        int strHash(string key) const {

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
        void insert(T value, string key) {

            // hash 
            int index = this->strHash(key);

            // create node 
            Node<T>* newNode = new Node<T>(value);

            // if empty index, insert value
            if (table[index] == nullptr) {

                // insert
                table[index] = newNode;

            }

            // handle collision with chaining
            else {

                // node tracker
                Node<T>* currentNode = table[index];

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
        bool search(string str) const {

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
                Node<T>* currentNode = table[index];

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

        friend ostream& operator<<(ostream& os, const HashTable& hashTable) const {

            // consts
            const int PRINT_INDEX_WIDTH = 5;  
            const string EMPTY_SPACE = "-";        

            
            // vector to hold the empty index sequence
            int emptyInds = 0;

            // open every ind in the table
            for (int i = 0; i < hashTable.tableSize; i ++) {
                
                // if printing this space
                if (hashTable.table[i] != nullptr || i == 0 || i == hashTable.tableSize - 1) {

                    // print previous empties
                    // 1 emtpy space has accumulated
                    if (emptyInds == 1) {

                        os << setw(PRINT_INDEX_WIDTH) << left << i - 1 << " | " << EMPTY_SPACE << endl;
                        emptyInds = 0;
                    }
                    // 2 emtpy spaces have accumulated
                    else if (emptyInds == 2) {

                        os << setw(PRINT_INDEX_WIDTH) << left << i - 2 << " | " << EMPTY_SPACE << endl;
                        os << setw(PRINT_INDEX_WIDTH) << left << i - 1 << " | " << EMPTY_SPACE << endl;
                        emptyInds = 0;
                    }
                    // 3+ emtpy spaces have accumulated
                    else if (emptyInds >= 3) {

                        os << setw(PRINT_INDEX_WIDTH) << left << i - emptyInds << " | " << EMPTY_SPACE << endl;
                        os << "  ..." << endl;
                        os << setw(PRINT_INDEX_WIDTH) << left << i - 1 << " | " << EMPTY_SPACE << endl;
                        emptyInds = 0;

                    }

                    // print space itself
                    // print space non-empty
                    if (hashTable.table[i] != nullptr) {

                        os << setw(PRINT_INDEX_WIDTH) << left << i << " | " << hashTable.table[i]->getValue() << endl;
                    }
                    // print spaceempty
                    else {

                        os << setw(PRINT_INDEX_WIDTH) << left << i << " | " << EMPTY_SPACE << endl;
                    }

                }
                // if space is empty
                else {

                    emptyInds ++;
                }

            }

            return os;
        }


        void saveToFile();

};




#endif
