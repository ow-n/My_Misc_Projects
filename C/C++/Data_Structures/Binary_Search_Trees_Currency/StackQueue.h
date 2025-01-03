// Demonstrate the use of Binary Search Trees to work with Currency objects

#ifndef STACKQUEUE_H
#define STACKQUEUE_H

#include "SinglyLinkedList.h"

class Stack : private SinglyLinkedList {
public:
    Stack(); // Constructor
    void createStack(Currency* data);
    ~Stack(); // Destructor
    void destroyStack();

    /**
     * Purpose: Pushes a currency object onto the top of the stack.
     * Pre: 'data' - a valid Currency pointer to be pushed onto the stack.
     * Post: Adds the specified currency 'data' to the top of the stack (at index 0 in the underlying linked list).
     * Return: None.
     */
    void push(Currency* data);

    /**
     * Purpose: Pops the top currency object from the stack.
     * Pre: None.
     * Post: Removes and retrieves the top currency object from the stack (at index 0 in the underlying linked list).
     *       If the stack is empty, an exception is thrown.
     * Return: Returns a pointer to the Currency object that was popped from the top of the stack.
     */
    Currency* pop();

    /**
     * Purpose: Peeks at the top currency object on the stack without removing it.
     * Pre: None.
     * Post: Retrieves the top currency object from the stack (at index 0 in the underlying linked list) without removing it.
     *       If the stack is empty, an exception is thrown.
     * Return: Returns a pointer to the Currency object at the top of the stack.
     */
    Currency* peek() const;

    /**
     * Purpose: Generates a string representation of the stack.
     * Pre: None.
     * Post: Calls the 'printList' method from the underlying linked list to create a string representation of the stack.
     * Return: Returns a string representation of the stack.
     */
    std::string printStack() const;

    /**
     * Purpose: Returns the count of currencies in the stack.
     * Pre: None.
     * Post: Calls the 'countCurrency' method from the underlying linked list to retrieve the count of currencies in the stack.
     * Return: Returns the number of currencies in the stack.
     */
    int countCurrency() const;

    /**
     * Purpose: Checks if the stack is empty.
     * Pre: None.
     * Post: Calls the 'isListEmpty' method from the underlying linked list to determine whether the stack is empty.
     * Return: Returns 'true' if the stack is empty, and 'false' otherwise.
     */
    bool isListEmpty() const;
};




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
    Currency* dequeue();

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

#endif // STACKQUEUE_H
