/**
 * @file readyqueue.cpp
 * @author Owen Man
 * @brief This is the implementation file for the ReadyQueue class.
 * @version 0.1
 */

#include <iostream>
#include "readyqueue.h"
#include "pcb.h"

using namespace std;

/**
 * @brief Constructor for the ReadyQueue class.
 */
 ReadyQueue::ReadyQueue()  {
    heapSize = 0;
    capacity = 1000;
    heap = new PCB*[capacity]; // allocate memory for heap array
}

/**
 * @brief Destructor to release dynamically allocate memory.
*/
ReadyQueue::~ReadyQueue() {
    delete[] heap;
}

/**
 * @brief Copy Constructor
 */
ReadyQueue::ReadyQueue(ReadyQueue &secondReadyQueue) {
    capacity = secondReadyQueue.capacity;
    heapSize = secondReadyQueue.heapSize;
    for (int i = 0; i <= secondReadyQueue.heapSize; i++) {
        heap[i - 1] = secondReadyQueue.heap[i - 1];
    }
}

/**
 * @brief Set a ready queue equal to another
 */
ReadyQueue& ReadyQueue::operator=(const ReadyQueue& secondReadyQueue) {
    if (this != &secondReadyQueue) {
        heapSize = secondReadyQueue.heapSize;
        capacity = secondReadyQueue.capacity; // set capacity
        for (int i = 1; i <= secondReadyQueue.heapSize; i++) { // copy each value
            heap[i - 1] = secondReadyQueue.heap[i - 1];
        }
    }

    return* this;
}

/**
 * @brief Add a PCB representing a process into the ready queue.
 *
 * @param pcbPtr: the pointer to the PCB to be added
 */
void ReadyQueue::addPCB(PCB *pcbPtr) {
    if (heapSize == capacity) {
        resizeHeap();
    }
    heap[heapSize] = pcbPtr;
    pcbPtr->setState(ProcState::READY); // set PCB state to READY
    heapSize++;
    bubbleUp(heapSize - 1); // restore heap property
}

/**
 * @brief Remove and return the PCB with the highest priority from the queue
 *
 * @return PCB*: the pointer to the PCB with the highest priority
 */
PCB* ReadyQueue::removePCB() {
    if (heapSize == 0) return nullptr;

    std::swap(heap[0], heap[heapSize-1]);
    PCB* removedPCB = heap[heapSize - 1];
    heapSize--;
    if (heapSize > 0) {
        bubbleDown(0);
    }
    removedPCB->setState(ProcState::RUNNING);
    return removedPCB;
}

/**
 * @brief Restores the heap property by moving the element at the specified index up the heap.
 *        Done whenever an element's priority is greater than its parent.
 *
 * @param index: the index of the element to bubble up
 */
void ReadyQueue::bubbleUp(int index) {
    while (index > 0 && heap[parent(index)]->getPriority() < heap[index]->getPriority()) {
        std::swap(heap[parent(index)], heap[index]);
        index = parent(index);
    }
}

/**
 * @brief Restores the heap property by moving the element at the specified index down the heap.
 *        Done whenever an element's priority is greater than its parent.
 *
 * @param index: the index of the element to bubble down
 */
void ReadyQueue::bubbleDown(int index) {
    size_t largest = static_cast<size_t>(index);
    size_t left = leftChild(index);
    size_t right = rightChild(index);

    if (left < static_cast<size_t>(heapSize) && heap[left]->getPriority() > heap[largest]->getPriority()) {
        largest = left;
    }
    if (right < static_cast<size_t>(heapSize) && heap[right]->getPriority() > heap[largest]->getPriority()) {
        largest = right;
    }

    if (largest != static_cast<size_t>(index)) {
        std::swap(heap[index], heap[largest]);
        bubbleDown(static_cast<int>(largest));
    }
}

void ReadyQueue::resizeHeap() {
    capacity *= 2;
    PCB** newHeap = new PCB*[capacity]; // create a new array with doubled capacity
    // Copy elements from old heap to new heap
    for (int i = 0; i < heapSize; ++i) {
        newHeap[i] = heap[i];
    }
    delete[] heap; // delete the old heap array
    heap = newHeap; // point heap to the new array
}

/**
 * @brief Calculates the parent's index of a given index in the heap.
 *
 * @param index the index of the current element
 * @return the index of the parent element
 */
int ReadyQueue::parent(int index) {
    return (index - 1) / 2;
}

/**
 * @brief Calculates the left child's index of a given index in the heap.
 *
 * @param index the index of the current element
 * @return the index of the left child
 */
int ReadyQueue::leftChild(int index) {
    return 2 * index + 1;
}

/**
 * @brief Calculates the right child's index of a given index in the heap.
 *
 * @param index the index of the current element
 * @return the index of the right child
 */
int ReadyQueue::rightChild(int index) {
    return 2 * index + 2;
}

/**
 * @brief Returns the number of elements in the queue.
 *
 * @return int: the number of PCBs in the queue
 */
int ReadyQueue::size() {
    return heapSize;
}

/**
 * @brief Display the PCBs in the queue.
 */
void ReadyQueue::displayAll() {
    for (int i = 0; i < heapSize; i++) {
        if (heap[i] != nullptr) {
            heap[i]->display();
        }
    }
}
