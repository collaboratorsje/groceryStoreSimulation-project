
#include "checkoutQueue.h"
// Destructor
Queue::~Queue() {
    while (front != nullptr) {
        queueNode* temp = front;
        front = front->nextPtr;
        delete temp;
    }
    rear = nullptr;
}
// Puts a customer in the queue and adjust the attributes that are in the associated queue's queueData
void Queue::enQueue(queueNodeData data, queueData& queueStats) {
    queueNode* newNode = new queueNode;
    newNode->data = data;
    newNode->nextPtr = nullptr;
    // makes the timeAvailable of the queue equal to when the curret customer is done checking out
    if (rear == nullptr) {
        newNode->data.timeAvailable = data.timeAvailable + data.itemCount * 15;
        front = rear = newNode;
    } 
    // If there are customers in line then add their timeAvailable to the checkout time of the next customer
    // This just makes the customers have to wait on prior customers in the queue 
    else {
        newNode->data.timeAvailable = rear->data.timeAvailable + data.itemCount * 15;
        rear->nextPtr = newNode;
        rear = newNode;
    }
    
    // Update queue stats
    queueStats.queueCount++;
    queueStats.currItems += data.itemCount;
    queueStats.totalItems += data.itemCount;
    // Puts the cartId onto a vector who's size represents the amount of customers served when simulation is finished
    queueStats.cartList.push_back(data.cartId);
    // If the current queue is longer than it is ever been, then it is the new max length of the queue
    if (queueStats.queueCount > queueStats.maxQueueLength) {
        queueStats.maxQueueLength = queueStats.queueCount;
    }
}
// deQueue function removes the customer from queue and updates the stats in the queueData object for that queue
queueNodeData Queue::deQueue(queueData& queueStats) {
    if (front == nullptr) {
        queueNodeData data = {0, 0};
        return data;
    }
    queueNodeData data = front->data;
    queueNode* temp = front;
    front = front->nextPtr;
    delete temp;
    if (front == nullptr) {
        rear = nullptr;
    }
    // Takes away the amount of items the customer had from the current items in the queue
    queueStats.currItems -= data.itemCount;
    // Decreases the current length of the queue by 1
    queueStats.queueCount -= 1;
    return data;
}
// Returns the data at the front of the queue
queueNodeData Queue::peek() {
    if (front == nullptr) {
        queueNodeData data = {0, 0};
        return data;
    }
    return front->data;
}
// Returns bool (true) if the queue is empty (if the front is the nullptr) otherwise returns false
bool Queue::queueEmpty() {
    return front == nullptr;
}
// prints the queue members, I used this when making the program (it's required for the project) but it doesn't get used in main
// I used it a lot to test out if my queue was working properly during creation of the queue
void Queue::printQueue() {
    queueNode* current = front;
    while (current != nullptr) {
        cout << "Time available: " << current->data.timeAvailable << ", Item count: " << current->data.itemCount << endl;
        current = current->nextPtr;
    }
}
// Function iterates through my vector of queueData objects and finds out the currItems in each queue
// returns the index in the vector of the queueData objects that has the least items
int getQueueWithLeastItems(vector<queueData>& checkoutQueueStatsVector) {
    int minIndex = 0;
    int minItems = checkoutQueueStatsVector.at(0).currItems;

    for (int i = 1; i < checkoutQueueStatsVector.size(); i++) {
        if (checkoutQueueStatsVector.at(i).currItems < minItems) {
            minIndex = i;
            minItems = checkoutQueueStatsVector.at(i).currItems;
        }
    }

    return minIndex;
}
// Formatted printout of the stats of each queue (from their queueData vector) ; iterates the vector prints and prints attributes
void printReport(const vector<queueData>& checkoutQueueStatsVector) {
    for (int j = 0; j < checkoutQueueStatsVector.size(); j++) {
        cout << "CHECKOUT LINE:     " << j+1 << endl;
        cout << setw(25) << left << "Total Customers Helped: " << setw(5) << left << checkoutQueueStatsVector.at(j).cartList.size() << endl;
        cout << setw(25) << left << "Total Number of Items: " << setw(5) << left << checkoutQueueStatsVector.at(j).totalItems << endl;
        cout << setw(25) << left << "Max Line Length: " << setw(5) << left << checkoutQueueStatsVector.at(j).maxQueueLength << endl;
        cout << setw(25) << left << "Total Idle Time: " << setw(5) << left << checkoutQueueStatsVector.at(j).totalIdleTime / 60 << endl;
        cout << setw(25) << left << "Total Over Time: " << setw(5) << left << checkoutQueueStatsVector.at(j).totalOverTime / 60 << endl;
        cout << endl;
    }
}
