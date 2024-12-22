
// includes
#include "HashTable.h"
#include <iostream>
#include <string>

// namespace
using std::string;
using std::cout, std::endl;

int main() {

    const int SIZE = 23;
    HashTable hashTable = HashTable(SIZE);

    // insert 
    hashTable.insert("    Purpose: commit class");
    hashTable.insert("#include <fstream>");
    hashTable.insert("            id = -1;");
    hashTable.insert("vector<Node*> valuesInTable;");
    hashTable.insert("            string nextLinePrev;");
    hashTable.insert("        int addFile(string filePath, vector<string> previousVersion) {");


    cout << endl << "Hash Table: " << endl << endl;
    cout << hashTable << endl;



    return 0;
}


