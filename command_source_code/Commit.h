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
#include <utility>

// namespace
using std::string;
using std::vector;
using std::ifstream, std::ofstream;
using std::pair;

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

// change object
struct modification {
    int line;
    int linesReplaced;
    string code;
    changeType type;
};


// object to represent a line of code in a file
class FileLine {

    private:

        // actual line of code
        string lineText;

        // line number
        int lineNum;

    public:

        // default constructor
        FileLine() {

            lineText = "";
            lineNum = -1;
        }

        // constructor
        FileLine(string text, int line) {

            lineText = text;
            lineNum = line;
        }

        // line text getter
        string getText() const {

            return lineText;
        }

        // line num getter
        int getNum() const {

            return lineNum;
        }

        // overload for comparison operator
        bool operator == (const FileLine& otherLine) const {

            return lineText == otherLine.getText();
        }

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
            HashTable<FileLine>* hashTable = new HashTable<FileLine>(HASH_TABLE_SIZE);

            // add all of new commit to hash table
            string fileLine;
            int lineNum = 0;
            while (getline(infile, fileLine)) {

                // create new file line to add
                FileLine fileLineObj = FileLine(fileLine, lineNum);

                // insert into hash table
                hashTable->insert(fileLineObj, fileLine);
            
                lineNum ++;

            }

            // search for every line of prev version in hash table

            // add all common lines to pair showing which lines map up

            // figure out how to handle multiple of the same line
            // build in pop function into node that returns true if it's to be removed

            return 0;
        }

        int addFirstTimeFile(string filePath) {

        }    


};




#endif
