#pragma once

#include "Project6.h"

class Customer {
    // private class attributes
    private:
        int id;
        int numItems;
        int shoppingTime;
        int enterQTime;
        int exitQTime;
        // Take between 30sec and 1min to shop for each item

    public:
        // constructor passing time (i)
        Customer(int i) {
            numItems = 0;
            shoppingTime = 0;
            enterQTime = 0;
            exitQTime = 0;
            // assigns customer with random category for amount of items then random # items within the category
            int numCategory = rand() % 10;
            if (numCategory == 0 || numCategory == 1 || numCategory == 2 || numCategory == 3) { 
                numItems = rand() % 10 + 1;
            }
            else if (numCategory == 4 || numCategory == 5 || numCategory == 6) {
                numItems = rand() % 10 + 11;

            }
            else if (numCategory == 7 || numCategory == 8) {
                numItems = rand() % 10 + 21;

            }
            else if (numCategory == 9) {
                numItems = rand() % 30 + 31;
            }
            // assigns random shopping time per item between 30 and 60 seconds
            int shoppingTimePerItem = rand() % 30 + 30;
            // calculates shopping time, enterQ and exitQ times
            shoppingTime = numItems * shoppingTimePerItem;
            enterQTime = i + shoppingTime;
            exitQTime = enterQTime + (numItems*15);

            // gives customer unique id the increments when each customer object is constructed
            static int counter = 0;
            id = counter++;
        }
        // setters
        void set_numItems(int numItems) {
            this->numItems = numItems;
        }
        void set_shoppingTime(int shoppingTime) {
            this->shoppingTime = shoppingTime;
        }
        void set_id(int id) {
            this->id = id;
        }
        void set_enterQTime(int enterQTime) {
            this->enterQTime = enterQTime;
        }
        void set_exitQTime(int exitQTime) {
            this->exitQTime = exitQTime;
        }
        // getters
        int get_numItems() {
            return numItems;
        }
        int get_shoppingTime() {
            return shoppingTime;
        }
        int get_id() {
            return id;
        }
        int get_enterQTime() {
            return enterQTime;
        }
        int get_exitQTime() {
            return exitQTime;
        }
};