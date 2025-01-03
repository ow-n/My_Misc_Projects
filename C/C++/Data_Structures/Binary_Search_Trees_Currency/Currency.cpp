// Demonstrate the use of Binary Search Trees to work with Currency objects

#include "Currency.h"

// Implementation for Currency class
// Default Constructor
Currency::Currency() : wholePart(0), fractionalPart(0) {}

// Constructor for single double input eg. 4.99
Currency::Currency(double value) {
    if (value < 0) {
        throw "Negative value is not allowed.";
    }
    int valueAsFractional = static_cast<int>(value * 100 + 0.5); // add 0.5 for rounding
    wholePart = valueAsFractional / 100;
    fractionalPart = valueAsFractional % 100;
}

// Copy Constructor
Currency::Currency(const Currency& original) : wholePart(original.wholePart), fractionalPart(original.fractionalPart) {}

// Destructor
Currency::~Currency() {}

// Getters and Setters
int Currency::getWholePart() const {
    return wholePart;
}

bool Currency::setWholePart(int wholePart) {
    if (wholePart >= 0) {
        this->wholePart = wholePart;
        return true;
    } else {
        throw "wholePart must be non-negative.";
        return false;
    }
}

int Currency::getFractionalPart() const {
    return fractionalPart;
}

bool Currency::setFractionalPart(int fractionalPart) {
    if (fractionalPart >= 0) {
        this->fractionalPart = fractionalPart;
        return true;
    } else {
        throw "fractionalPart must be non-negative";
        return false;
    }
}

// Functions
void Currency::add(const Currency& other) {
    // Check is currency is the same
    if (getName() != other.getName()) {
        throw "Mismatch currency types";
    }

    int totalFractionalPart = getFractionalPart() + other.getFractionalPart();
    if (totalFractionalPart >= 100) {
        setWholePart(getWholePart() + totalFractionalPart / 100); // eg. 155 / 100 = 1
        setFractionalPart(totalFractionalPart % 100);
    } else {
        setFractionalPart(totalFractionalPart);
    }
    setWholePart(getWholePart() + other.getWholePart());
}

void Currency::subtract(const Currency& other) {
    // Check is currency is the same
    if (getName() != other.getName()) {
        throw "Mismatch currency types";
    }

    // Check if the result would be negative
    if (other.getWholePart() > getWholePart() || (other.getWholePart() == getWholePart() && other.getFractionalPart() > getFractionalPart())) {
        throw "Subtraction would result in a negative value";
    }

    // Subtract whole parts
    setWholePart(getWholePart() - other.getWholePart());

    // Subtract fractional parts, borrowing from whole parts if necessary
    if (other.getFractionalPart() > getFractionalPart()) {
        setWholePart(getWholePart() - 1);
        setFractionalPart(getFractionalPart() + 100);
    }
    setFractionalPart(getFractionalPart() - other.getFractionalPart());
}

bool Currency::isEqual(const Currency& other) const {
    // Check is currency is the same
    if (getName() != other.getName()) {
        throw "Mismatch currency types";
    }
    return (getWholePart() == other.getWholePart()) && (getFractionalPart() == other.getFractionalPart());
}

bool Currency::isGreater(const Currency& other) const {
    // Check is currency is the same
    if (getName() != other.getName()) {
        throw "Mismatch currency types";
    }

    if (getWholePart() > other.getWholePart()) {
        return true;
    } else if (getWholePart() == other.getWholePart()) {
        return getFractionalPart() > other.getFractionalPart();
    } else {
        return false;
    }
}

std::string Currency::toString() const {
    return std::to_string(getWholePart()) + "." + (getFractionalPart() < 10 ? "0" : "") + std::to_string(getFractionalPart()) + " " + getName();
}




// Dollar Class Implementation
// Static Constants
const std::string Dollar::name = "Dollar";

// Default constructor
Dollar::Dollar() : Currency() {}

// Constructor for single double input eg. 4.99
Dollar::Dollar(double value) : Currency(value) {}

// Function
std::string Dollar::getName() const {
    return name;
}




// Pound Class Implementation
// Static Constants
const std::string Pound::name = "Pound";

// Default constructor
Pound::Pound() : Currency() {}

// Constructor for single double input eg. 4.99
Pound::Pound(double value) : Currency(value) {}

// Function
std::string Pound::getName() const {
    return name;
}
