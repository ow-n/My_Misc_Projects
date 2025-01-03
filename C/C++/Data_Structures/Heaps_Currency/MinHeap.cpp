// Demonstrate the use of Min Heaps to work with Currency objects


#include "MinHeap.h"
#include "StackQueue.h"

void MinHeap::insert(Currency* data) {
    BSTNode* newNode = new BSTNode(data);
    BSTNode* position = nextAvailablePosition(); // find position for new node
    
    if (!position) {
        setRoot(newNode);
    } else if (!position->getLeft()) {
        position->setLeft(newNode);
    } else {
        position->setRight(newNode);
    }

    bubbleUp(newNode); // maintain heap property
}

BSTNode* MinHeap::nextAvailablePosition() {
    if (!getRoot()) {
        return nullptr; // the heap is empty
    }

    Queue queue; 
    queue.enqueue(getRoot()->getData());

    while (true) {
        try {
            Currency* frontCurrency = queue.dequeue();
            BSTNode* currentNode = findNodeByCurrency(getRoot(), frontCurrency);

            if (!currentNode->getLeft()) {
                return currentNode;
            }
            queue.enqueue(currentNode->getLeft()->getData());

            if (!currentNode->getRight()) {
                return currentNode;
            }
            queue.enqueue(currentNode->getRight()->getData());
            
        } catch (const std::out_of_range&) {
            break; // exit loop when queue is empty
        }
    }

    return nullptr; // only if tree is full
}





bool MinHeap::search(double value) const {
    if (!getRoot()) {
        return false; // head is empty
    }

    int wholePart = static_cast<int>(value);
    int fractionalPart = static_cast<int>((value - wholePart) * 100);

    Queue queue;
    queue.enqueue(getRoot()->getData());

    while (true) {
        try {
            Currency* frontCurrency = queue.dequeue();

            if (frontCurrency->getWholePart() == wholePart && frontCurrency->getFractionalPart() == fractionalPart) {
                return true;  // if found value searched for
            }

            // Get the BSTNode corresponding to this Currency object
            BSTNode* currentNode = findNodeByCurrency(getRoot(), frontCurrency);

            // Continue the search by enqueuing child nodes
            if (currentNode->getLeft()) {
                queue.enqueue(currentNode->getLeft()->getData());
            }
            if (currentNode->getRight()) {
                queue.enqueue(currentNode->getRight()->getData());
            }
        }
        catch (const std::out_of_range&) {
            break; // exit loop when queue is empty
        }
    }

    return false;
}





bool MinHeap::deleteNode(double value) {
    if (!getRoot()) return false; // empty heap

    // Convert the double value to a Dollar object.
    Dollar targetDollar(value);

    // Find the node with the given value
    BSTNode* targetNode = findNodeByCurrency(getRoot(), &targetDollar);
    if (!targetNode) {
        return false; // value not found
    }

    // Replace target node's data with the last node's data.
    BSTNode* lastNode = getLastNode();
    targetNode->setData(lastNode->getData());

    // Delete the last node
    BSTNode* parentOfLastNode = getParent(lastNode);
    if (parentOfLastNode->getLeft() == lastNode) {
        parentOfLastNode->setLeft(nullptr);
    } else {
        parentOfLastNode->setRight(nullptr);
    }
    delete lastNode;

    // Decide to bubble down or up based on comparison with children
    BSTNode* left = targetNode->getLeft();
    BSTNode* right = targetNode->getRight();

    bool isLeftSmaller = left && isLessThan(left->getData(), targetNode->getData());
    bool isRightSmaller = right && isLessThan(right->getData(), targetNode->getData());

    if (isLeftSmaller || isRightSmaller) {
        bubbleDown(targetNode);
    } else {
        bubbleUp(targetNode);
    }

    return true;
}

void MinHeap::bubbleUp(BSTNode* node) {
    if (!node) return;

    BSTNode* parent = getParent(node);

    while (parent && isLessThan(node->getData(), parent->getData())) {
        // Swap node's data with its parent's data
        Currency* temp = node->getData();
        node->setData(parent->getData());
        parent->setData(temp);

        // Move up to the parent for next iteration
        node = parent;
        parent = getParent(node);
    }
}

void MinHeap::bubbleDown(BSTNode* node) {
    if (!node) return;

    BSTNode* left = node->getLeft();
    BSTNode* right = node->getRight();

    // Determine the smallest child
    BSTNode* smallest = node;

    if (left && isLessThan(left->getData(), node->getData())) {
        smallest = left;
    }
    if (right && isLessThan(right->getData(), smallest->getData())) {
        smallest = right;
    }

    // If the smallest isn't the current node, swap and continue bubbling down
    if (smallest != node) {
        Currency* temp = node->getData();
        node->setData(smallest->getData());
        smallest->setData(temp);
        bubbleDown(smallest);
    }
}

bool MinHeap::isLessThan(Currency* a, Currency* b) {
    if (!a || !b) return false; // safety check

    if (a->getWholePart() < b->getWholePart()) {
        return true;
    } else if (a->getWholePart() == b->getWholePart() && 
               a->getFractionalPart() < b->getFractionalPart()) {
        return true;
    }
    return false;
}

BSTNode* MinHeap::getLastNode() {
    if (!getRoot()) return nullptr;

    Queue queue;
    queue.enqueue(getRoot()->getData());

    BSTNode* lastNode = nullptr;
    while (true) {
        try {
            Currency* frontCurrency = queue.dequeue();
            lastNode = findNodeByCurrency(getRoot(), frontCurrency); // get node using the currency data
            if (lastNode->getLeft()) queue.enqueue(lastNode->getLeft()->getData());
            if (lastNode->getRight()) queue.enqueue(lastNode->getRight()->getData());
        } catch (const std::out_of_range&) {
            break;
        }
    }
    return lastNode;
}

BSTNode* MinHeap::getParent(BSTNode* node) {
    if (!node || node == getRoot()) return nullptr;

    Queue queue;
    queue.enqueue(getRoot()->getData());

    while (true) {
        try {
            Currency* frontCurrency = queue.dequeue();
            BSTNode* currentNode = findNodeByCurrency(getRoot(), frontCurrency);
            if (currentNode->getLeft() == node || currentNode->getRight() == node) {
                return currentNode;
            }
            if (currentNode->getLeft()) queue.enqueue(currentNode->getLeft()->getData());
            if (currentNode->getRight()) queue.enqueue(currentNode->getRight()->getData());
        } catch (const std::out_of_range&) {
            break;
        }
    }
    return nullptr;
}
