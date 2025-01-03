// Demonstrate the use of Binary Search Trees to work with Currency objects

#include "BinarySearchTree.h"
#include "StackQueue.h"
#include <iostream>

// BSTNode Class Implementation
// Constructor
BSTNode::BSTNode(Currency* data) : data(data), left(nullptr), right(nullptr) {}

// Getters and Setters
Currency* BSTNode::getData() const {
    return data;
}

void BSTNode::setData(Currency* newData) {
    data = newData;
}

BSTNode* BSTNode::getLeft() const {
    return left;
}

BSTNode*& BSTNode::getLeftRef() {
    return left;
}

void BSTNode::setLeft(BSTNode* newLeft) {
    left = newLeft;
}

BSTNode* BSTNode::getRight() const {
    return right;
}

BSTNode*& BSTNode::getRightRef() {
    return right;
}

void BSTNode::setRight(BSTNode* newRight) {
    right = newRight;
}




// BinarySearchTree Class Implementation
// Constructor and Destructor
BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    empty();
}

// Traversal Methods
void BinarySearchTree::inOrder() const {
    inOrder(root);
}

void BinarySearchTree::inOrder(BSTNode* node) const {
    if (node) {
        inOrder(node->getLeft());
        std::cout << node->getData()->toString() << " ";
        inOrder(node->getRight());
    }
}

void BinarySearchTree::preOrder() const {
    preOrder(root);
}

void BinarySearchTree::preOrder(BSTNode* node) const {
    if (node) {
        std::cout << node->getData()->toString() << " ";
        preOrder(node->getLeft());
        preOrder(node->getRight());
    }
}

void BinarySearchTree::postOrder() const {
    postOrder(root);
}

void BinarySearchTree::postOrder(BSTNode* node) const {
    if (node) {
        postOrder(node->getLeft());
        postOrder(node->getRight());
        std::cout << node->getData()->toString() << " ";
    }
}

void BinarySearchTree::breadthFirst() const {
    if (root == nullptr) {
        return;
    }

    Queue queue;
    queue.enqueue(root->getData()); // queues root node

    while (true) {
        try {
            Currency* frontCurrency = queue.dequeue();

            // Find the corresponding BSTNode for this Currency object
            BSTNode* currentNode = findNodeByCurrency(root, frontCurrency);

            // Process the current node
            std::cout << currentNode->getData()->toString() << " ";

            // Enqueue the left child, if any
            if (currentNode->getLeft() != nullptr) {
                queue.enqueue(currentNode->getLeft()->getData());
            }

            // Enqueue the right child, if any
            if (currentNode->getRight() != nullptr) {
                queue.enqueue(currentNode->getRight()->getData());
            }
        }
        catch (const std::out_of_range&) {
            // Queue is empty; break the loop
            break;
        }
    }
}

BSTNode* BinarySearchTree::findNodeByCurrency(BSTNode* node, Currency* currency) const {
    if (node == nullptr) {
        return nullptr;
    }
    if (node->getData() == currency) {
        return node;
    }

    BSTNode* foundNode = findNodeByCurrency(node->getLeft(), currency);
    if (foundNode != nullptr) {
        return foundNode;
    }
    return findNodeByCurrency(node->getRight(), currency);
}

// BST Methods
void BinarySearchTree::insert(Currency* data) {
    insert(root, data);
}

void BinarySearchTree::insert(BSTNode*& node, Currency* data) {
    double dataValue = data->getWholePart() + data->getFractionalPart() / 100.0;
    if (node == nullptr) {
        node = new BSTNode(data);
    } else {
        double nodeValue = node->getData()->getWholePart() + node->getData()->getFractionalPart() / 100.0;
        if (dataValue < nodeValue) {
            insert(node->getLeftRef(), data);
        } else {
            insert(node->getRightRef(), data);
        }
    }
}

bool BinarySearchTree::search(double value) const {
    return search(root, value);
}

bool BinarySearchTree::search(BSTNode* node, double value) const {
    if (node == nullptr) return false;
    double nodeValue = node->getData()->getWholePart() + node->getData()->getFractionalPart() / 100.0;
    if (nodeValue == value) return true;
    if (value < nodeValue) return search(node->getLeft(), value);
    return search(node->getRight(), value);
}

bool BinarySearchTree::deleteNode(double value) {
    return deleteNode(root, value);
}

bool BinarySearchTree::deleteNode(BSTNode*& node, double value) {
    if (node == nullptr) return false;
    double nodeValue = node->getData()->getWholePart() + node->getData()->getFractionalPart() / 100.0;
    if (value < nodeValue) {
        return deleteNode(node->getLeftRef(), value);
    } else if (value > nodeValue) {
        return deleteNode(node->getRightRef(), value);
    } else {
        if (node->getLeft() == nullptr) {
            BSTNode* temp = node;
            node = node->getRight();
            delete temp;
        } else if (node->getRight() == nullptr) {
            BSTNode* temp = node;
            node = node->getLeft();
            delete temp;
        } else {
            // Finding inorder successor (leftmost node in right subtree)
            BSTNode* successor = node->getRight();
            while (successor->getLeft() != nullptr) successor = successor->getLeft();
            
            // Manually copying the data of the successor
            int wholePart = successor->getData()->getWholePart();
            int fractionalPart = successor->getData()->getFractionalPart();
            
            // Setting node's data to the copied data
            node->getData()->setWholePart(wholePart);
            node->getData()->setFractionalPart(fractionalPart);
            
            // Deleting the successor
            deleteNode(node->getRightRef(), wholePart + fractionalPart / 100.0);
        }

        return true;
    }
}

// Utility Methods
int BinarySearchTree::count() const {
    return count(root);
}

int BinarySearchTree::count(BSTNode* node) const {
    if (node == nullptr) return 0;
    return 1 + count(node->getLeft()) + count(node->getRight());
}

bool BinarySearchTree::isEmpty() const {
    return root == nullptr;
}

void BinarySearchTree::empty() {
    empty(root);
    root = nullptr;
}

void BinarySearchTree::empty(BSTNode*& node) {
    if (node) {
        empty(node->getLeftRef());
        empty(node->getRightRef());
        delete node;
        node = nullptr;
    }
}

void BinarySearchTree::print() const {
    inOrder();
}
