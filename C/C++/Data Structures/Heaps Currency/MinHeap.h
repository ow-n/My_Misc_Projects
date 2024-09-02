// Demonstrate the use of Min Heaps to work with Currency objects

#ifndef MINHEAP_H
#define MINHEAP_H

#include "BinarySearchTree.h"

class MinHeap : public BinarySearchTree {
private:
    // Utility Methods
    /**
     * Purpose: Finds the next available position in the binary search tree for insertion.
     * Pre: None.
     * Post: Returns the position for the next insertion.
     * Return: A pointer to the BSTNode indicating the next available position. 
     */
    BSTNode* nextAvailablePosition(); // helper for insert()

    /**
     * Purpose: Moves the given node upwards to its correct position after insertion.
     * Pre: 'node' - a valid BSTNode pointer.
     * Post: Node has been moved up to maintain the min heap property.
     * Return: None.
     */
    void bubbleUp(BSTNode* node); // helper for insert() & deleteNode()

    /**
     * Purpose: Moves the given node downwards to its correct position after deletion.
     * Pre: 'node' - a valid BSTNode pointer.
     * Post: Node has been moved down to maintain the min heap property.
     * Return: None.
     */
    void bubbleDown(BSTNode* node); // helper for deleteNode()

    /**
     * Purpose: Checks if one currency is less than another.
     * Pre: 'a' and 'b' - valid Currency object pointers.
     * Post: None.
     * Return: True if 'a' is less than 'b', else False.
     */
    bool isLessThan(Currency* a, Currency* b); // helper for bubbleDown()

    /**
     * Purpose: Retrieves the last node in the binary search tree.
     * Pre: None.
     * Post: None.
     * Return: A pointer to the BSTNode representing the last node in the tree.
     */
    BSTNode* getLastNode(); // helper for deleteNode()

    /**
     * Purpose: Retrieves the parent node of the given node.
     * Pre: 'node' - a valid BSTNode pointer.
     * Post: None.
     * Return: A pointer to the BSTNode representing the parent of the given node.
     */
    BSTNode* getParent(BSTNode* node); // helper for deleteNode()

public:
    // Main Methods
    /**
     * Purpose: Inserts a currency object into the binary search tree.
     * Pre: 'data' - a valid Currency object pointer.
     * Post: 'data' is inserted into the binary search tree.
     * Return: None.
     */
    void insert(Currency* data) override;

    /**
     * Purpose: Searches for a given value in the binary search tree.
     * Pre: 'value' - a double representing the currency value to search for.
     * Post: None.
     * Return: True if 'value' is found in the tree, else False.
     */
    bool search(double value) const override;

    /**
     * Purpose: Deletes a node with a given value from the binary search tree.
     * Pre: 'value' - a double representing the currency value to delete.
     * Post: If 'value' is found, the node is removed and the tree retains its structure.
     * Return: True if the deletion was successful, else False.
     */
    bool deleteNode(double value) override;
    
};

#endif // MINHEAP_H
