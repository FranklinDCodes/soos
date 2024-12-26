
// includes
#include "HashTable.h"
#include <iostream>
#include <string>

// namespace
using std::string;
using std::cout, std::endl;

int main() {

    const int SIZE = 23;
    HashTable<string> hashTable = HashTable<string>(SIZE);

    // insert 
    hashTable.insert("    Purpose: commit objct", "    Purpose: commit objct");
    hashTable.insert("    Purpose: commit class", "    Purpose: commit class");
    hashTable.insert("#include <fstream>", "#include <fstream>");
    hashTable.insert("            id = -1;", "            id = -1;");
    hashTable.insert("vector<Node*> valuesInTable;", "vector<Node*> valuesInTable;");
    hashTable.insert("            string nextLinePrev;", "            string nextLinePrev;");
    hashTable.insert("        int addFile(string filePath, vector<string> previousVersion) {", "        int addFile(string filePath, vector<string> previousVersion) {");
    hashTable.insert("        int addFile(string filePath, vector<string> previousVersion) {", "        int addFile(string filePath, vector<string> previousVersion) {");


    cout << endl << "Hash Table: " << endl << endl;
    cout << hashTable << endl;



    return 0;
}


