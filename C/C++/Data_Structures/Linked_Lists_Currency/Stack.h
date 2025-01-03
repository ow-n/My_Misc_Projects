// Demonstrate the use of ADTs to work with Currency objects


#ifndef STACK_H
#define STACK_H

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
     * Return:
     */
    void push(Currency* data);

    /**
     * Purpose: Pops the top currency object from the stack.
     * Pre:
     * Post: Removes and retrieves the top currency object from the stack (at index 0 in the underlying linked list).
     *       If the stack is empty, an exception is thrown.
     * Return: Returns a pointer to the Currency object that was popped from the top of the stack.
     */
    Currency* pop();

    /**
     * Purpose: Peeks at the top currency object on the stack without removing it.
     * Pre:
     * Post: Retrieves the top currency object from the stack (at index 0 in the underlying linked list) without removing it.
     *       If the stack is empty, an exception is thrown.
     * Return: Returns a pointer to the Currency object at the top of the stack.
     */
    Currency* peek() const;

    /**
     * Purpose: Generates a string representation of the stack.
     * Pre:
     * Post: Calls the 'printList' method from the underlying linked list to create a string representation of the stack.
     * Return: Returns a string representation of the stack.
     */
    std::string printStack() const;

    /**
     * Purpose: Returns the count of currencies in the stack.
     * Pre:
     * Post: Calls the 'countCurrency' method from the underlying linked list to retrieve the count of currencies in the stack.
     * Return: Returns the number of currencies in the stack.
     */
    int countCurrency() const;

    /**
     * Purpose: Checks if the stack is empty.
     * Pre:
     * Post: Calls the 'isListEmpty' method from the underlying linked list to determine whether the stack is empty.
     * Return: Returns 'true' if the stack is empty, and 'false' otherwise.
     */
    bool isListEmpty() const;
};

#endif // STACK_H
