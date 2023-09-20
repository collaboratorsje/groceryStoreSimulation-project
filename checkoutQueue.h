#pragma once

#include "Project6.h"
// queueNodeData is the type of data in each queue node
struct queueNodeData {
    int timeAvailable;
    int itemCount;
    int cartId;
};
// Making the nodes for the queue
struct queueNode {
    queueNodeData data;
    queueNode* nextPtr;
};
// A type that I use to keep stats for a particular queue
struct queueData {
    int queueCount;
    int totalIdleTime;
    int totalOverTime;
    int maxQueueLength;
    int currItems;
    int totalItems;
    vector<int> cartList;
    // initializer list to set the attributes to 0 (learned this for this project)
    queueData() : queueCount(0), totalIdleTime(0), totalOverTime(0), maxQueueLength(0), currItems(0), totalItems(0) {}
};
// Makes the queue and declares the functions
class Queue {
private:
    queueNode* front;
    queueNode* rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}
    ~Queue();
    void enQueue(queueNodeData, queueData& queueStats); 
    queueNodeData deQueue(queueData& queueStats);   
    queueNodeData peek();        
    bool queueEmpty();           
    void printQueue();
};
// Gets the queue with the least items (defined in .cpp)
int getQueueWithLeastItems(vector<queueData>& checkoutQueueStatsVector);
// Prints the report of all the queue data at the end of the simulation
void printReport(const vector<queueData>& checkoutQueueStatsVector);
