#pragma once

#include "customer.h"

// makes a listType struct to be passed as the data in the linkedlist
struct listType {
    int cartId;
    int itemCount;
    int enterQTime;
    int exitQTime;
};
// makes the nodes of the list
struct Node {
    listType data;
    Node* nextPtr;
};
// creates standard linked list
class LinkedList {
private:
    Node* headPtr;
    static int listCount;

public:
    // function declarations
    LinkedList() : headPtr(nullptr) {}

    void addElement(listType element);
    listType peek();
    void delElement();
    void printList();

    bool listIsEmpty() {
        return headPtr == nullptr;
    }

    static int getListCount() {
        return listCount;
    }

    static void setListCount(int count) {
        listCount = count;
    }
};
