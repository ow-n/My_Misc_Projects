// Demonstrate the use of ADTs to work with Currency objects

#ifndef DOLLAR_H
#define DOLLAR_H

#include "Currency.h"
#include <string>

class Dollar : public Currency {
private:
    static const std::string name;

public:
    Dollar(); // Default constructor
    Dollar(double value); // Constructor for single double input eg. 4.99

    /**
     * Purpose: Retrieves the name of the currency.
     * Pre:
     * Post:
     * Return: Returns a string that represents the name of the currency.
     */
    std::string getName() const override;
};

#endif // DOLLAR_H
