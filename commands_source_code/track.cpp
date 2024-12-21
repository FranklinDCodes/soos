/*
    Author: Franklin Doane
    Date created: 20 December 2024
    Purpose: Adds a file to tracked_files.txt
*/

// includes
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

// namespace
using std::cout, std::cin, std::endl;
using std::fstream, std::ios;
using std::string;
using std::filesystem::path, std::filesystem::exists, std::filesystem::is_directory;

// main function
int main(int argCount, char* args[]) {

    // file stream
    fstream fileStream;

    // expected number of positional arguments
    const int EXPECTED_ARGS = 1;

    // check for too few args
    if (argCount < EXPECTED_ARGS + 1) {

        cout << endl << "Argument Error | Too few positional arguments passed: expected " << EXPECTED_ARGS << "." << endl;
        return -1;

    }
    // check for too many args
    else if (argCount > EXPECTED_ARGS + 1) {

        cout << endl << "Argument Error | Too many positional arguments passed: expected " << EXPECTED_ARGS << "." << endl;
        return -1;

    }
    
    // fetch file name as first arg
    string strArg = args[1];
    fileStream.open(strArg);

    // see if file opened
    if (!fileStream.is_open()) {

        cout << endl << "Invalid File Error | File \"" << strArg << "\" either does not exist or it cannot be opened." << endl;
        return -1;

    }
    fileStream.close();

    // check if valid soos repo
    path soosDir = ".soos";
    if (!(exists(soosDir) && is_directory(soosDir))) {

        cout << endl << "Soos Error | Current working directory does not contain a soos repository." << endl;
        return -1;

    }

    // attempt to open tracker
    path trackerFileName = "tracked_files.lst";
    path trackerFilePath = (soosDir / trackerFileName);

    // check if tracker file exists
    if (!exists(trackerFilePath)) {

        cout << endl << "Soos Error | Soos repository has been corrupted." << endl;
        return -1;

    }

    // setup to open tracker file
    string strTrackerFilePath = trackerFilePath.string();
    fileStream.open(strTrackerFilePath, ios::in);

    // check if tracker file can be opened
    if (!fileStream.is_open()) {

        cout << endl << "Soos Error | Soos repository has been corrupted." << endl;
        return -1;

    }

    // iterate through file to check if given file is already being tracked
    bool fileIsTracked = false;
    string trackedFile;
    while ((!fileIsTracked) && (!fileStream.eof())) {

        // read in next item and check if it's the arg passed
        getline(fileStream, trackedFile);
        if (trackedFile == strArg) {
            fileIsTracked = true;
        }

    }
    fileStream.close();

    // if file was already being tracked
    if (fileIsTracked) {

        cout << endl << "\t" << strArg << " is already being tracked." << endl; 

    }
    // add file to be tracked
    else {

        // open file stream
        fileStream.open(trackerFilePath, ios::app);

        // write file
        fileStream << strArg << endl;

        cout << endl << "\t" << strArg << " has been added to tracked files." << endl;

    }

    return 0;
}
