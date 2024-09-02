// Demonstrate the use of ADTs to work with Currency objects


#include "Stack.h"
#include "SinglyLinkedList.h"

// Constructor
Stack::Stack() : SinglyLinkedList() {}

void Stack::createStack(Currency* data) {
    this->push(data);
}

// Destructor
Stack::~Stack() {
    this->destroyList();
}

void Stack::destroyStack() {
    this->destroyList();
}

// Functions
void Stack::push(Currency* data) {
    this->addCurrency(data, 0);
}

Currency* Stack::pop() {
    if (this->isListEmpty()) {
        throw std::out_of_range("Stack is empty.");
    }
    Currency* top = this->getCurrency(0);
    this->removeCurrency(0);
    return top;
}

Currency* Stack::peek() const {
    if (this->isListEmpty()) {
        throw std::out_of_range("Stack is empty.");
    }
    return this->getCurrency(0);
}

std::string Stack::printStack() const {
    return this->printList();
}


// Override countCurrency to public
int Stack::countCurrency() const {
    return SinglyLinkedList::countCurrency();
}

// Override isListEmpty to public
bool Stack::isListEmpty() const {
    return SinglyLinkedList::isListEmpty();
}
