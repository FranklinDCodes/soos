#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    // open file
    ifstream infile;
    infile.open("myFileCommit10.goop");

    // lines for tracking through the file
    string curLinePrev = "";
    string nextLinePrev;
    string curLineNew;
    int lineNumPrev = 0;
    int lineNumNew = 0;

    // keep reading in lines in pairs
    while (getline(infile, curLineNew)) {

        cout << curLineNew << endl;
        cout << infile.bad() << endl;
        cout << infile.eof() << endl;

    }


    return 0;
}