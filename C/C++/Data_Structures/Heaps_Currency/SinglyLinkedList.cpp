// Demonstrate the use of Min Heaps to work with Currency objects

#include "SinglyLinkedList.h"
#include "Currency.h"

// LinkNode Class Implementation
// Constructor
LinkNode::LinkNode(Currency* data) {
    this->data = data;
    next = nullptr;
}




// SinglyLinkedList Class implementation
// Constructors
SinglyLinkedList::SinglyLinkedList() {
    start = nullptr;
    end = nullptr;
    count = 0;
}

void SinglyLinkedList::createList() {
    destroyList();
    start = nullptr;
    end = nullptr;
    count = 0;
}

void SinglyLinkedList::createList(Currency* data) {
    destroyList();
    start = new LinkNode(data);
    end = start;
    count = 1;
}

// Destructor
SinglyLinkedList::~SinglyLinkedList() {
    destroyList();
}

void SinglyLinkedList::destroyList() {
    while (start) {
        LinkNode* temp = start;
        start = start->next;
        delete temp;
    }
    count = 0;
    end = nullptr;
}

// Functions
void SinglyLinkedList::addCurrency(Currency* data, int index) {
    if (index < 0 || index > count) {
        throw std::out_of_range("Index is out of range.");
    }

    LinkNode* newNode = new LinkNode(data);
    if (index == 0) {
        newNode->next = start;
        start = newNode;
        if (count == 0) {
            end = start;
        }
    } else {
        LinkNode* previous = start;
        for (int i = 0; i < index - 1; i++) {
            previous = previous->next;
        }
        newNode->next = previous->next;
        previous->next = newNode;
        if (newNode->next == nullptr) {
            end = newNode;
        }
    }
    count++;
}

Currency* SinglyLinkedList::removeCurrency(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index out of range.");
    }
    
    LinkNode* nodeToRemove;
    if (index == 0) {
        nodeToRemove = start;
        start = start->next;
        if (start == nullptr) {
            end = nullptr;
        }
    } else {
        LinkNode* current = start;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        nodeToRemove = current->next;
        current->next = current->next->next;
        if (current->next == nullptr) {
            end = current;
        }
    }
    count--;
    Currency* removedData = nodeToRemove->data;
    delete nodeToRemove;
    return removedData;
}

int SinglyLinkedList::findCurrency(Currency* data) const {
    LinkNode* current = start;
    for (int i = 0; i < count; i++) {
        if (current->data->getWholePart() == data->getWholePart() && current->data->getFractionalPart() == data->getFractionalPart()) {
            return i;
        }
        current = current->next;
    }
    return -1;
}

int* SinglyLinkedList::findAllCurrencyIndices(Currency* data, int& numIndices) const {
    int* indices = new int[count];
    numIndices = 0;

    LinkNode* current = start;
    for (int i = 0; i < count; i++) {
        if (current->data == data) {
            indices[numIndices] = i;
            numIndices++;
        }
        current = current->next;
    }

    // If no matching indices were found, return nullptr
    if (numIndices == 0) {
        delete[] indices;
        return nullptr;
    }

    return indices;
}

Currency* SinglyLinkedList::getCurrency(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Index is out of range.");
    }
    LinkNode* current = start;
    for(int i = 0; i < index; i++){
        current = current->next;
    }
    return current->data;
}

std::string SinglyLinkedList::printList() const {
    std:: string result;
    LinkNode* current = start;
    while(current != nullptr) {
        result += current->data->toString() + "\t";
        current = current->next;
    }
    return result;
}

bool SinglyLinkedList::isListEmpty() const {
    return count == 0;
}

int SinglyLinkedList::countCurrency() const {
    return count;
}

void SinglyLinkedList::clear() {
    destroyList();
}

bool SinglyLinkedList::exists(Currency* data) {
    return findCurrency(data) != -1;
}
