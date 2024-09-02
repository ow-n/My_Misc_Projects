// Demonstrate the use of Lists, Stacks, Queues in context

#include "Queue.h"
#include "SinglyLinkedList.h"

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
