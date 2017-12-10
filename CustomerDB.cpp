/*
 * Name:
 * EID:
 * Project 7, CRM part 2
 * EE 312, Spring 2017
 */
#include <iostream>
#include <cassert>
#include "String.h"
#include "CustomerDB.h"

using namespace std;

const int default_capacity = 1;

Customer::Customer(String name) { // done, please do not edit
    this->bottles = 0;
    this->rattles = 0;
    this->diapers = 0;
    this->name = name;
}

CustomerDB::CustomerDB(void) { // done, please do not edit
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

int CustomerDB::size(void) {
    return this->length;
}

CustomerDB::~CustomerDB(void) { // done, please do not edit
    delete[] this->data;
}

void CustomerDB::clear(void) { // done, please do not edit
    delete[] this->data;
    this->capacity = default_capacity;
    this->data = new Customer[this->capacity];
    this->length = 0;
}

Customer& CustomerDB::operator[](int k) { // done, please do not edit
    assert(k >= 0 && k < this->length);
    return this->data[k];
}

Customer& CustomerDB::operator[](String name) { // not done, your effort goes here
    for (int index = 0; index < this->length; index++){
        if (this->data[index].name == name)
            return this->data[index];
    }

    if (this->length < this->capacity){
        Customer* newData = new Customer[this->capacity * 2];
        for (int index = 0; index < this->length; index++){
            newData[index] = this->data[index];
        }
        newData[this->length] = Customer(name);
        this->length = this->length + 1;
        this->capacity = this->capacity * 2;
        delete [] this->data;
        this->data = newData;
        return this->data[this->length - 1];
    }
    else {
        this->data[this->length] = Customer(name);
        return this->data[this->length - 1];
    }
}



bool CustomerDB::isMember(String name) { // not done, your effort goes here
    for (int index = 0; index < this->length; index++) {
        if (this->data[index].name == name)
            return true;
    }
    return false;
}


