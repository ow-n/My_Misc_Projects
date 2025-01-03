// Demonstrate the use of ADTs to work with Currency object

#include "LinkNode.h"

// Implementation for LinkNode class
// Constructor
LinkNode::LinkNode(Currency* data) {
    this->data = data;
    next = nullptr;
}
