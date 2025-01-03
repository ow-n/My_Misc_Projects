// Demonstrate the use of ADTs to work with Currency objects

#ifndef LINKNODE_H
#define LINKNODE_H

#include "Currency.h"

class LinkNode {
public:
    Currency* data;
    LinkNode* next;

    LinkNode(Currency* data); // Constructor
};

#endif // LINKNODE_H
