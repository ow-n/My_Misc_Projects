// Demonstrate the use of Binary Search Trees to work with Currency objects

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include "Currency.h"
#include <iostream>

class LinkNode {
public:
    Currency* data;
    LinkNode* next;

    LinkNode(Currency* data); // Constructor
};




class SinglyLinkedList {
private:
    LinkNode* start;
    LinkNode* end;
    int count;

public:
    SinglyLinkedList(); // Constructor
    void createList();
    void createList(Currency* data);
    
    ~SinglyLinkedList(); // Destructor
    void destroyList();

    /**
     * Purpose: Adds a new currency node at the specified index in the linked list.
     * Pre: 'data' - a valid Currency pointer to be added.
     *      'index' - an integer representing the position in the linked list where the new currency will be inserted.
     * Post: A new node containing the 'data' is inserted at the specified 'index' in the linked list.
     *       If 'index' is out of range, an exception is thrown.
     * Return: None.
     */
    void addCurrency(Currency* data, int index);

    /**
     * Purpose: Removes a currency node at the specified index from the linked list.
     * Pre: 'index' - an integer representing the position in the linked list of the node to be removed.
     * Post: The node at the specified 'index' is removed from the linked list.
     *       If 'index' is out of range, an exception is thrown.
     * Return: Returns a pointer to the Currency object that was removed.
     */
    Currency* removeCurrency(int index);

    /**
     * Purpose: Finds the index of the first occurrence of the specified currency in the linked list.
     * Pre: 'data' - a valid Currency pointer to be searched for.
     * Post: Searches for the specified currency 'data' in the linked list.
     * Return: Returns the index of the first occurrence if found, and -1 otherwise.
    */
    int findCurrency(Currency* data) const;

    /**
     * Purpose: Finds all indices of the specified currency in the linked list.
     * Pre: 'data' - a valid Currency pointer to be searched for.
     *      'numIndices' - a reference to an integer where the number of occurrences will be stored.
     * Post: Searches for all occurrences of the specified currency 'data' in the linked list.
     *       IMPORTANT: Must deallocate memory returned by using `delete[]`.
     *       Unnecessary if function returns nullptr.
     * Return: Returns a dynamically allocated array of indices if found, and nullptr otherwise.
     */
    int* findAllCurrencyIndices(Currency* data, int& numIndices) const;

    /**
     * Purpose: Retrieves the currency at the specified index from the linked list.
     * Pre: 'index' - an integer representing the position in the linked list of the node to be retrieved.
     * Post: Retrieves the currency at the specified 'index' from the linked list.
     *       If 'index' is out of range, an exception is thrown.
     * Return: Returns a pointer to the Currency object at the specified index.
     */
    Currency* getCurrency(int index) const;

    /**
     * Purpose: Generates a string representation of the linked list.
     * Pre: None.
     * Post: Iterates through the linked list, concatenating the string representations of the currency objects.
     * Return: Returns a string representation of the linked list.
     */
    std::string printList() const;

    /**
     * Purpose: Checks if the linked list is empty.
     * Pre: None.
     * Post: Determines whether the linked list is empty by checking the 'count' variable.
     * Return: Returns 'true' if the linked list is empty, and 'false' otherwise.
     */
    bool isListEmpty() const;

    /**
     * Purpose: Returns the count of currencies in the linked list.
     * Pre: None.
     * Post: Retrieves the 'count' variable representing the number of currencies in the linked list.
     * Return: Returns the number of currencies in the linked list.
     */
    int countCurrency() const;

    /**
     * Purpose: Clears the linked list by calling the 'destroyList' method.
     * Pre:
     * Post: Calls the 'destroyList' method to remove all nodes from the linked list.
     * Return:
     */
    void clear();

    /**
     * Purpose: Checks if the specified currency exists in the linked list.
     * Pre: 'data' - a valid Currency pointer to be searched for.
     * Post: Calls the 'findCurrency' method to check if the specified currency 'data' exists in the linked list.
     * Return: Returns 'true' if the currency exists, and 'false' otherwise.
     */
    bool exists(Currency* data);
};

#endif // SINGLYLINKEDLIST_H
