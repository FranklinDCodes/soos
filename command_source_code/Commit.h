/*
    Author: Franklin Doane
    Date created: 20 December 2024
    Purpose: commit class
*/

// file guards
#ifndef COMMIT_H
#define COMMIT_H

// include
#include <string>
#include <ctime>
#include <vector>
#include <fstream>
#include "HashTable.h"

// namespace
using std::string;
using std::vector;
using std::ifstream, std::ofstream;

// constants
const int HASH_TABLE_SIZE = 977;

// change type
enum changeType {
    INSERTION,
    MODIFICATION
};

// change object
struct modification {
    int line;
    int linesReplaced;
    string code;
    changeType type;
};


// commit class
class Commit {

    private:

        // unique commit it
        int id;

        // timestamp of commit
        string dt;
        
        // list of files tracked in commit
        vector<string> files;

        // list of modifications
        vector<vector<modification>*> fileModifications;
        

    public:

        // default constructor
        Commit() {

            id = -1;
            dt = "";

        }

        // constructor
        Commit(int id) {

            // set unique id
            int id = id;

            // Get the current time
            time_t now = time(0);
            dt = ctime(&now);

        }

        // add all the changes from a file
        int addFile(string filePath, vector<string> previousVersion) {

            // add file to file list
            files.push_back(filePath);
            
            // create new array to add modifications to
            fileModifications.at(files.size() - 1) = new vector<modification>();
            vector<modification>* fileMods = fileModifications.at(files.size() - 1);

            // open file
            ifstream infile;
            infile.open(filePath);

            // check that file is open
            if (!infile.is_open()) {
                return -1;
            }

            // init hashtable
            HashTable* hashTable = new HashTable(HASH_TABLE_SIZE);

            // add all of new commit to hash table
            string fileLine;
            while (getline(infile, fileLine)) {
                
                hashTable->insert(fileLine);
            }

            // search for every line of prev version in hash table

            // add all common lines to pair showing which lines map up

            // make hash table to hold a struct with a seperate arg for keys
            // the struct needs to hold the str value as well as the line number so they can be matched up

            return 0;
        }

        int addFirstTimeFile(string filePath) {

        }    


};




#endif
