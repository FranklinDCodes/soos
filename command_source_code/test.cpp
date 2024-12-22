
// includes
#include <iostream>
#include <string>
#include <vector>

// namespace
using std::string;
using std::cout, std::endl;

class Node {

    private:

        string value;
        Node* next;

    public:

        // default constructor
        Node() {

            string value = "";
            Node* next = nullptr;
        }
        
        // constructor
        Node(string nodeValue) {

            string value = nodeValue;
            Node* next = nullptr;
        }

        // destructor
        ~Node() {

            cout << "Node Dest Called: " << value << endl;

            if (next != nullptr) {

                delete next;
            }
        }

        // access next
        Node* getNext() {

            return next;
        }

        // access next
        string getValue() {

            return value;
        }

        // mutate next
        void setNext(Node* nextNode) {

            next = nextNode;
        }

        // mutate next
        void setValue(string val) {

            value = val;
        }

};



int main() {


    Node* node1 = new Node("Val1");
    Node* node2 = new Node("Val2");
    
    node1->setValue("Val1");
    node2->setValue("Val2");


    node1->setNext(node2);
    cout << node2->getNext() << endl;

    delete node1;








    return 0;
}


