// Demonstrate the use of ADTs to work with Currency objects

#include "Dollar.h"

// Static Constants
const std::string Dollar::name = "Dollar";

// Default constructor
Dollar::Dollar() : Currency() {}

// Constructor for single double input eg. 4.99
Dollar::Dollar(double value) : Currency(value) {}

// Functions
std::string Dollar::getName() const {
    return name;
}
