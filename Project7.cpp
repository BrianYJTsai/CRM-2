/*
 * Name: Brian Tsai
 * EID: byt76
 * Project 7, CRM part 2
 * EE 312, Spring 2017
 */

#include <stdio.h>
#include "String.h"
#include "Customer.h"
#include "CustomerDB.h"
#include <iostream>

void readString(String&);
void readNum(int&);

CustomerDB database;

int num_bottles = 0;
int num_rattles = 0;
int num_diapers = 0;


using namespace std;

/* clear the inventory and reset the customer database to empty */
void reset(void) {
    database.clear();
    num_bottles = 0;
    num_rattles = 0;
    num_diapers = 0;
}

/*
 * selectInventItem is a convenience function that allows you
 * to obtain a pointer to the inventory record using the item type name
 * word must be "Bottles", "Diapers" or "Rattles"
 * for example the expression *selectInventItem("Bottles") returns the
 * current global variable for the number of bottls in the inventory
 */
int* selectInventItem(String word) {
    if (word == "Bottles") {
        return &num_bottles;
    } else if (word == "Diapers") {
        return &num_diapers;
    } else if (word == "Rattles") {
        return &num_rattles;
    }

    /* NOT REACHED */
    return 0;
}

/*
 * this overload of selectInventItem is similar to selectInventItem above, however
 * this overload takes a Customer as a second argument and selects the data member
 * of that Customer that matches "word". The function returns a pointer to one of the three data
 * members from the specified customer.
 */
int* selectInventItem(String word, Customer& cust) {
    if (word == "Bottles") {
        return &cust.bottles;
    } else if (word == "Diapers") {
        return &cust.diapers;
    } else if (word == "Rattles") {
        return &cust.rattles;
    }

    /* NOT REACHED */
    return 0;
}


/*
 * findMax searches through the CustomerDB "database" and returns the Customer
 * who has purchased the most items of the specified type.
 * type must be one of "Bottles", "Rattles" or "Diapers".
 *
 * Note: if two or more Customers are tied for having purchased the most of that item type
 * then findMax returns the first Customer in the CustomerDB who has purchased that maximal
 * quantity.
 *
 * Note: in the special case (invalid case) where there are zero Customers in the
 * CustomerDB, fundMax returns a null pointer (0)
 */
Customer* findMax(String type) {
    Customer* result = 0;
    int max = 0;
    for (int k = 0; k < database.size(); k += 1) {
        Customer& cust = database[k];
        int *p = selectInventItem(type, cust);
        if (*p > max) {
            max = *p;
            result = &cust;
        }
    }

    return result;
}

void processPurchase() {


    // Parse the name of the customer
    String name = String();
    String& newName = name;
    readString(newName);

    // Parse the item the customer bought
    String item;
    String& newItem = item;
    readString(newItem);

    // Parse the amount the customer bought
    int quantity;
    int& newQuantity = quantity;
    readNum(newQuantity);


    // Ignore all quantities less than or equal to zero
    if (newQuantity <= 0)
        return;

    if (selectInventItem(newItem) != 0){

        // Check if the inventory has enough of the requested item
        if (*selectInventItem(newItem) < newQuantity) {
            cout << "Sorry " << newName.c_str() << ", we only have " << *selectInventItem(newItem) << " "<< newItem.c_str() << "\n";
        }
        else {
            *selectInventItem(newItem, database[newName]) += newQuantity;
            *selectInventItem(newItem) -= newQuantity;
        }
    }


}

void processSummarize() {

    // Output the number of each item currently in the inventory
    cout << "There are " << num_bottles << " Bottles, ";
    cout << num_diapers << " Diapers and ";
    cout << num_rattles << " Rattles in inventory\n";

    // Output the number of customers that have visited
    cout << "we have had a total of " << database.size() << " different customers\n";

    String items[3] = {String("Bottles"), String("Diapers"), String("Rattles")};

    // Output a summary of each item
    for (String item : items){
        Customer* customer = findMax(item);
        if (customer != NULL)
            cout << customer->name.c_str() << " has purchased the most " << item.c_str() << " (" << *selectInventItem(item, *customer) << ")\n";
        else
            cout << "no one has purchased any " << item.c_str() << "\n";
    }


}

void processInventory() {

    // Parse the inventory item to be added
    String item = String();
    String& newItem = item;
    readString(newItem);

    // Parse the amount to be added to the inventory
    int quantity;
    int& newQuantity = quantity;
    readNum(newQuantity);

    if (newQuantity <= 0)
        return;

    // Add the new quantity to the selected inventory
    if (selectInventItem(item) != 0)
        *selectInventItem(item) += newQuantity;
}

