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

// namespace
using std::string;
using std::vector;

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
        vector<vector<modification>> fileModifications;
        

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
        void addFile(string filePath) {

            // add file to file list
            files.push_back(filePath);
            
            // create new array to add modifications to
            fileModifications.at(files.size() - 1) = vector<modification>();


        }

    




};




#endif
