// Demonstrate the use of Min Heaps to work with Currency objects

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "Currency.h" // for BSTNode class

class BSTNode {
private:
    Currency* data;
    BSTNode* left;
    BSTNode* right;
    BSTNode* parent; // for MinHeap

public:
    // Constructor
    BSTNode(Currency* data);

    // Getters and Setters
    Currency* getData() const;
    void setData(Currency* newData);
    BSTNode* getLeft() const;
    BSTNode*& getLeftRef();
    void setLeft(BSTNode* newLeft);
    BSTNode* getRight() const;
    BSTNode*& getRightRef();
    void setRight(BSTNode* newRight);
    BSTNode* getParent() const;
    void setParent(BSTNode* newParent);
};

class BinarySearchTree {
private:
    BSTNode* root;

    // Recursive Helper Method
    /**
     * Purpose: Performs an in-order traversal starting from the given node.
     * Pre: 'node' - a pointer to the starting node.
     * Post: Nodes are visited in the <Left><Root><Right> order.
     * Return: None.
     */
    void inOrder(BSTNode* node) const;

    /**
     * Purpose: Performs a pre-order traversal starting from the given node.
     * Pre: 'node' - a pointer to the starting node.
     * Post: Nodes are visited in the <Root><Left><Right> order.
     * Return: None.
     */
    void preOrder(BSTNode* node) const;

    /**
     * Purpose: Performs a post-order traversal starting from the given node.
     * Pre: 'node' - a pointer to the starting node.
     * Post: Nodes are visited in the <Left><Right><Root> order.
     * Return: None.
     */
    void postOrder(BSTNode* node) const;

    /**
     * Purpose: Inserts a currency object into the binary search tree.
     * Pre: 'node' - a reference to the pointer to the root node.
     *      'data' - a valid Currency object pointer.
     * Post: 'data' is inserted into the binary search tree.
     * Return: None.
     */
    void insert(BSTNode*& node, Currency* data);

    /**
     * Purpose: Searches for a value in the binary search tree starting from the given node.
     * Pre: 'node' - a pointer to the starting node.
     *      'value' - the value to search for.
     * Post: None.
     * Return: True if the value is found, false otherwise.
     */
    virtual bool search(BSTNode* node, double value) const;

    /**
     * Purpose: Deletes a node with the given value from the binary search tree.
     * Pre: 'node' - a reference to the pointer to the root node.
     *      'value' - the value of the node to delete.
     * Post: Node with the given value is deleted from the tree, if found.
     * Return: True if the deletion is successful, false otherwise.
     */
    virtual bool deleteNode(BSTNode*& node, double value);

    /**
     * Purpose: Counts the number of nodes in the binary search tree starting from the given node.
     * Pre: 'node' - a pointer to the starting node.
     * Post: None.
     * Return: The number of nodes in the tree.
     */
    virtual int count(BSTNode* node) const;

    /**
     * Purpose: Empties the binary search tree starting from the given node.
     * Pre: 'node' - a reference to the pointer to the root node.
     * Post: All nodes are deleted, and the tree is empty.
     * Return: None.
     */
    void empty(BSTNode*& node);

protected:
    BSTNode* getRoot() const;
    void setRoot(BSTNode* newRoot);

    /**
     * Purpose: Finds a BSTNode by its Currency object, starting from the given node.
     * Pre: 'node' - a pointer to the starting node.
     *      'currency' - a pointer to the Currency object to find.
     * Post: None.
     * Return: Pointer to the found BSTNode, or nullptr if not found.
     */
    BSTNode* findNodeByCurrency(BSTNode* node, Currency* currency) const; // breathFirst() helper

public:
    // Constructor and Destructor
    BinarySearchTree();
    ~BinarySearchTree();
    
    // Traversal Methods
    /**
     * Purpose: Performs an in-order traversal of the binary search tree.
     * Pre: None.
     * Post: Nodes are visited in the <Left><Root><Right> order.
     * Return: None.
     */
    void inOrder() const;

    /**
     * Purpose: Performs a pre-order traversal of the binary search tree.
     * Pre: None.
     * Post: Nodes are visited in the <Root><Left><Right> order.
     * Return: None.
     */
    void preOrder() const;

    /**
     * Purpose: Performs a post-order traversal of the binary search tree.
     * Pre: None.
     * Post: Nodes are visited in the <Left><Right><Root> order.
     * Return: None.
     */
    void postOrder() const;

    /**
     * Purpose: Performs a breadth-first (level order) traversal of the binary search tree.
     * Pre: None.
     * Post: Nodes are visited level by level from left to right.
     * Return: None.
     */
    void breadthFirst() const;


    // BST Methods
    /**
     * Purpose: Inserts a Currency object into the binary search tree.
     * Pre: 'data' - a valid Currency object pointer.
     * Post: 'data' is inserted into the binary search tree.
     * Return: None.
     */
    virtual void insert(Currency* data);

    /**
     * Purpose: Searches for a value in the binary search tree.
     * Pre: 'value' - the value to search for.
     * Post: None.
     * Return: True if the value is found, false otherwise.
     */
    virtual bool search(double value) const;

    /**
     * Purpose: Deletes a node with the given value from the binary search tree.
     * Pre: 'value' - the value of the node to delete.
     * Post: Node with the given value is deleted from the tree, if found.
     * Return: True if the deletion is successful, false otherwise.
     */
    virtual bool deleteNode(double value);


    // Utility Methods
    /**
     * Purpose: Counts the number of nodes in the binary search tree.
     * Pre: None.
     * Post: None.
     * Return: The number of nodes in the tree.
     */
    int count() const;

    /**
     * Purpose: Checks if the binary search tree is empty.
     * Pre: None.
     * Post: None.
     * Return: True if the tree is empty, false otherwise.
     */
    bool isEmpty() const;

    /**
     * Purpose: Empties the binary search tree.
     * Pre: None.
     * Post: All nodes are deleted, and the tree is empty.
     * Return: None.
     */
    void empty();

    /**
     * Purpose: Prints the binary search tree.
     * Pre: None.
     * Post: The tree is printed to the standard output.
     * Return: None.
     */
    void print() const;
};

#endif // BINARYSEARCHTREE
