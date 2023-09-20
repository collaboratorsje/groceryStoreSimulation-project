
#include "linkedtest.h"

// initializes listCount to 0
int LinkedList::listCount = 0;

// prints the list from the headPtr until the end (when current is the nullptr)
void LinkedList::printList() {
    Node* current = headPtr;

    while (current != nullptr) {
        cout << "Cart ID: " << current->data.cartId << ", Item Count: " << current->data.itemCount
            << ", Enter Queue Time: " << current->data.enterQTime << ", Exit Queue Time: " << current->data.exitQTime << endl;
        current = current->nextPtr;
    }
}
// adds nodes to the list by making data equal to the listtype object that is passed and adjusting pointers
void LinkedList::addElement(listType element) {
    Node* newNode = new Node;
    newNode->data = element;

    // Insert the new node in the correct position
    Node* current = headPtr;
    Node* previous = nullptr;
    // adding in nodes so that the list is sorted by enterQTime (so that enterQTime objects are the at the top)
    while (current != nullptr && current->data.enterQTime < element.enterQTime) {
        previous = current;
        current = current->nextPtr;
    }

    if (previous == nullptr) {
        headPtr = newNode;
    } else {
        previous->nextPtr = newNode;
    }

    newNode->nextPtr = current;
}
// returns the data from the head of the list, if not just throws a list is empty error
listType LinkedList::peek() {
    if (headPtr == nullptr) {
        throw runtime_error("List is empty");
    }

    return headPtr->data;
}
// deletes a node from the list and then adjusts the pointers
void LinkedList::delElement() {
    if (headPtr == nullptr) {
        throw runtime_error("List is empty");
    }

    Node* temp = headPtr;
    headPtr = headPtr->nextPtr;
    delete temp;
}

