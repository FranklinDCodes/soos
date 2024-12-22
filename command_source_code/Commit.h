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

// namespace
using std::string;
using std::vector;
using std::ifstream, std::ofstream;

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


            // lines for tracking through the file
            string curLinePrev = previousVersion.at(0);
            string nextLinePrev;
            string curLineNew;
            int lineNumPrev = 0;
            int lineNumNew = 0;

            // keep reading in lines in pairs
            while (getline(infile, curLineNew)) {
                
                // if cur line in the previous file is the last one
                if (lineNumPrev >= previousVersion.size()) {
                    
                    

                }
                else {

                    // grab the next line of the new file

                    

                }


                lineNumNew ++;


            }



            return 0;
        }

        int addFirstTimeFile(string filePath) {

        }    


};




#endif
