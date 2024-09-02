// Demonstrate the use of Min Heaps to work with Currency objects

#include "StackQueue.h"
#include "SinglyLinkedList.h"

// Stack Class Implementation
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



// Queue Class Implementation
// Constructor
Queue::Queue() : SinglyLinkedList() {}

void Queue::createQueue(Currency* data) {
    this->addCurrency(data, this->countCurrency());
}

// Destructor
Queue::~Queue() {
    this->destroyList();
}

void Queue::destroyQueue() {
    this->destroyList();
}

// Methods
void Queue::enqueue(Currency* data) { // adds to the end
    this->addCurrency(data, this->countCurrency());
}

Currency* Queue::dequeue() { // removes from the end
    if (this->isListEmpty()) {
        throw std::out_of_range("Queue is empty.");
    }

    Currency* frontCurrency = this->getCurrency(0);
    this->removeCurrency(0);
    return frontCurrency;
}

Currency* Queue::peekFront() const {
    if (this->isListEmpty()) {
        throw std::out_of_range("Queue is empty.");
    }
    return this->getCurrency(0);
}

Currency* Queue::peekRear() const {
    if (this->isListEmpty()) {
        throw std::out_of_range("Queue is empty.");
    }
    return this->getCurrency(this->countCurrency() - 1);
}

std::string Queue::printQueue() const {
    std::string queueString;
    for(int i = 0; i < this->countCurrency(); i++) {
        queueString += this->getCurrency(i)->toString();
        queueString += "\t";
    }
    return queueString;
}
