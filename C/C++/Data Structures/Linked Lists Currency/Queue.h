// Demonstrate the use of ADTs to work with Currency objects

#ifndef QUEUE_H
#define QUEUE_H

#include "SinglyLinkedList.h"

class Queue : private SinglyLinkedList {
public:
    Queue(); // Constructor
    void createQueue(Currency* data);
    ~Queue(); // Destructor
    void destroyQueue();
    
    /**
     * Purpose: Enqueues a currency object onto the rear of the queue.
     * Pre: 'data' - a valid Currency pointer to be enqueued.
     * Post: Adds the specified currency 'data' to the rear of the queue (at the end of the underlying linked list).
     */
    void enqueue(Currency* data);

    /**
     * Purpose: Dequeues the front currency object from the queue.
     * Post: Removes and retrieves the front currency object from the queue (at index 0 in the underlying linked list).
     *       If the queue is empty, an exception is thrown.
     * Return: Returns a pointer to the Currency object that was dequeued from the front of the queue.
     */
    Currency* dequeue(); // removes from the end

    /**
     * Purpose: Peeks at the front currency object on the queue without removing it.
     * Post: Retrieves the front currency object from the queue (at index 0 in the underlying linked list) without removing it.
     *       If the queue is empty, an exception is thrown.
     * Return: Returns a pointer to the Currency object at the front of the queue.
     */
    Currency* peekFront() const;

    /**
     * Purpose: Peeks at the rear currency object on the queue without removing it.
     * Post: Retrieves the rear currency object from the queue (at the last index in the underlying linked list) without removing it.
     *       If the queue is empty, an exception is thrown.
     * Return: Returns a pointer to the Currency object at the rear of the queue.
     */
    Currency* peekRear() const;

    /**
     * Purpose: Generates a string representation of the queue.
     * Post: Iterates through the underlying linked list and concatenates each currency object's string representation to create a string of the queue.
     * Return: Returns a string representation of the queue.
     */
    std::string printQueue() const;
};

#endif // QUEUE_H
