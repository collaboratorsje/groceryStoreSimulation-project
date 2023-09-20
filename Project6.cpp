/* Name: Seth Emery || Date: April 21, 2023 || Section: Tu/Th 1pm || Project: Grocery Store Simulation */

#include "Project6.h"
#include "customer.h"
#include "linkedtest.h"
#include "checkoutQueue.h"

int main() {

    // Seeds time
    srand(time(0));
    // Declares linked list
    LinkedList customerList;

    // Create a vector of queues and a vector of each queue's queueData
    int numQueues = getQueueNumber();
    vector<Queue> checkoutQueueVector(numQueues);
    vector<queueData> checkoutQueueStatsVector(numQueues);

    // Starts for loop to keep time in 1 second intervals
    for (int i = 0; i < 43200; i+=1) {
        // If it's an interval of 60 seconds, generate 1-3 customers
        if (i % 60 == 0 && i <= 43200) {
            int numCustGenerated = rand() % 3 + 1;
            // Add the generated customers to the linkedlist
            for (int j = 0; j < numCustGenerated; j++) {
                Customer Shopper(i);
                listType cart = { Shopper.get_id(), Shopper.get_numItems(), i + Shopper.get_shoppingTime(), 0 };
                customerList.addElement(cart);
            }
        }
        // Check if the head node is ready to enter the checkout queue
        listType cart;
        while (!customerList.listIsEmpty()) {
            cart = customerList.peek();
            if (cart.enterQTime >= i) {
                // Make a queueNodeData object from the attributes of "cart"
                queueNodeData data = {cart.enterQTime, cart.itemCount, cart.cartId};
                // Check which queue is the shortest and add the cart to that queue
                int shortestQueueIndex = getQueueWithLeastItems(checkoutQueueStatsVector);
                checkoutQueueVector.at(shortestQueueIndex).enQueue(data, checkoutQueueStatsVector.at(shortestQueueIndex));

                // Remove the cart from the linked list
                customerList.delElement();
            } 
            else {
                break;
            }
        }
        // dequeues customers from the queue when they are done checking out (when timeAvailable <= i)
        for (int j = 0; j < checkoutQueueVector.size(); j++) {
            queueNodeData front = checkoutQueueVector.at(j).peek();
            if (front.timeAvailable <= i) {
                checkoutQueueVector.at(j).deQueue(checkoutQueueStatsVector.at(j));
            }
            // If a queue is empty this increments that queues idle time stat
            if (checkoutQueueVector.at(j).queueEmpty()) {
                checkoutQueueStatsVector.at(j).totalIdleTime++;
            }
        }    
    }

    // Keep running the checkout queues until they're empty
    // Overtime
    // Because 720 minutes ends at 43200 seconds, I start a while loop that starts at 43200 and increments until
    // -- increments until the linkedlist customers are all queued and then all customers are checked out (queues empty)
    int i = 43200;
    while (true) {
        bool allQueuesEmpty = true;
        // Iterate over the checkout queues and their stats
        for (int j = 0; j < checkoutQueueVector.size(); j++) {
            Queue& checkoutQueue = checkoutQueueVector.at(j);
            queueData& checkoutQueueStats = checkoutQueueStatsVector.at(j);
            
            // Check if there are any customers in the linked list that are ready to enter the checkout queue
            listType cart;
            while (!customerList.listIsEmpty()) {
                cart = customerList.peek();
                if (cart.enterQTime >= i) {
                    // Add the cart to the checkout queue with the least items
                    int shortestQueueIndex = getQueueWithLeastItems(checkoutQueueStatsVector);
                    // make a queueNodeData object from attributes of the listType object
                    queueNodeData data = { cart.enterQTime, cart.itemCount, cart.cartId };
                    // enQueues the data object created into the queue with the shortest line
                    checkoutQueueVector.at(shortestQueueIndex).enQueue(data, checkoutQueueStatsVector.at(shortestQueueIndex));
                    customerList.delElement();
                } else {
                    break;
                }
            }
            
            // Check if there are any customers in the checkout queue that are ready to be dequeued
            queueNodeData front = checkoutQueue.peek();
            if (front.timeAvailable <= i) {
                checkoutQueue.deQueue(checkoutQueueStats);
            }
            
            // Update checkoutQueueStats
            if (checkoutQueue.queueEmpty()) {
                checkoutQueueStats.totalIdleTime++;
            }
            if (checkoutQueueStats.queueCount > checkoutQueueStats.maxQueueLength) {
                checkoutQueueStats.maxQueueLength = checkoutQueueStats.queueCount;
            }
            // My program returns all checkouts with the same overtime because if one checkout is open then they all are
            // teamwork! (total overtime the same for all checkouts)
            checkoutQueueStats.totalOverTime++;
            
            // Check if the checkout queue is empty
            if (!checkoutQueue.queueEmpty()) {
                allQueuesEmpty = false;
            }
        }
        
        // Check if all checkout queues are empty and there are no more customers in the linked list
        if (allQueuesEmpty && customerList.listIsEmpty()) {
            break;
        }
        // increment while loop
        i++;
    }
    // print formatted report
    printReport(checkoutQueueStatsVector);

}