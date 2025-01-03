/**
 * Assignment 1: priority queue of processes
 * @file readyqueue.h
 * @author Owen Man
 * @brief ReadyQueue is a queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 * @version 0.1
 */

#pragma once

#include "pcb.h"

/**
 * @brief A queue of PCB's that are in the READY state to be scheduled to run.
 * It should be a priority queue such that the process with the highest priority can be selected next.
 */
class ReadyQueue {
private:
    PCB** heap;
    int heapSize; // number of elements in the heap
    int capacity; // capacity of the heap array

    void bubbleUp(int index);
    void bubbleDown(int index);
    void resizeHeap();
    int parent(int index);
    int leftChild(int index);
    int rightChild(int index);

public:
    /**
     * @brief Construct a new ReadyQueue object
     */
    ReadyQueue();

    /**
     * @brief Destructor
     */
    ~ReadyQueue();

    /**
     * @brief Creates copy of the constructor
     */
    ReadyQueue(ReadyQueue &secondReadyQueue);

    /**
     * @brief Set a ready queue equal to another
     */
    ReadyQueue& operator=(const ReadyQueue& secondReadyQueue);

    /**
     * @brief Add a PCB representing a process into the ready queue.
     *
     * @param pcbPtr: the pointer to the PCB to be added
     */
	void addPCB(PCB* pcbPtr);

    /**
     * @brief Remove and return the PCB with the highest priority from the queue
     *
     * @return PCB*: the pointer to the PCB with the highest priority
     */
	PCB* removePCB();

    /**
     * @brief Returns the number of elements in the queue.
     *
     * @return int: the number of PCBs in the queue
     */
	int size();

     /**
      * @brief Display the PCBs in the queue.
      */
	void displayAll();

};
