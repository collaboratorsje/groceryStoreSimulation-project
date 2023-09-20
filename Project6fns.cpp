#include "Project6.h"

int getQueueNumber() {
    int numQueues;
    while (true) {
        cout << "Enter the number of queues: ";
        cin >> numQueues;

        if (cin.fail()) {
            cout << "Invalid input. Please enter an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            return numQueues;
        }
    }
}