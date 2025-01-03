// Demonstrate Inheritance and Polymorphism through performing operations on different currencies sharing the same base class.

#include <iostream>
#include <string>

class Currency {
private:
    int wholePart;
    int fractionalPart;

public:
    // Default Constructor
    Currency() : wholePart(0), fractionalPart(0) {}

    // Constructor for single double input eg. 4.99
    Currency(double value) {
        if (value < 0) {
            throw "Negative value is not allowed.";
        }
        // Multiply by 100 to convert it to a fractional value
        int valueAsFractional = static_cast<int>(value * 100 + 0.5); // add 0.5 for rounding
        // Integer division for whole; Modulus for fractional
        wholePart = valueAsFractional / 100;
        fractionalPart = valueAsFractional % 100;
    }

    // Copy Constructor
    Currency(const Currency& original) : wholePart(original.wholePart), fractionalPart(original.fractionalPart) {}

    // Destructor
    virtual ~Currency() {}

    // Getters and Setters
    int getWholePart() const {
        return wholePart;
    }

    bool setWholePart(int wholePart) {
        if (wholePart >= 0) {
            this->wholePart = wholePart;
            return true;
        } else {
            throw "wholePart must be non-negative.";
            return false;
        }
    }

    int getFractionalPart() const {
        return fractionalPart;
    }

    bool setFractionalPart(int fractionalPart) {
        if (fractionalPart >= 0) {
            this->fractionalPart = fractionalPart;
            return true;
        } else {
            throw "fractionalPart must be non-negative";
            return false;
        }
    }

    /**
     * Purpose: Adds the value of another currency object to the invoking object.
     * Pre: 'other' - a valid Currency object.
     * Post: The value of the 'other' object is added to the invoking object.
     *       An exception is thrown if the 'other' object is of a different currency type.
     * Return:
     */
    void add(const Currency& other) {
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

    /**
     * Purpose: Subtracts the value of another currency object from the invoking object.
     * Pre: 'other' - a valid Currency object.
     * Post: The value of the 'other' object is subtracted from the invoking object.
     *       An exception is thrown if the 'other' object is of a different currency type or if the subtraction would result in a negative value.
     * Return:
     */
    void subtract(const Currency& other) {
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

    /**
     * Purpose: Checks if the value of another currency object is equal to the invoking object.
     * Pre: 'other' - a valid Currency object.
     * Post: The value of the invoking object is compared to the value of the 'other' object.
     *       An exception is thrown if the 'other' object is of a different currency type.
     * Return: Returns 'true' if the values of the invoking object and the 'other' object are equal, and 'false' otherwise.
     */
    bool isEqual(const Currency& other) const {
        // Check is currency is the same
        if (getName() != other.getName()) {
            throw "Mismatch currency types";
        }
        return (getWholePart() == other.getWholePart()) && (getFractionalPart() == other.getFractionalPart());
    }

    /**
     * Purpose: Checks if the value of the invoking currency object is greater than another currency object.
     * Pre: 'other' - a valid Currency object.
     * Post: The value of the invoking object is compared to the value of the 'other' object.
     *       An exception is thrown if the 'other' object is of a different currency type.
     * Return: Returns 'true' if the value of the invoking object is greater than the value of the 'other' object, and 'false' otherwise.
     */
    bool isGreater(const Currency& other) const {
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

    /**
     * Purpose: Converts the value of the invoking currency object to a string.
     * Pre:
     * Post: The value of the invoking object is converted to a string in the format "xx.yy Currency".
     * Return: Returns a string representation of the invoking object's value.
     */
    std::string toString() const {
        return std::to_string(getWholePart()) + "." + (getFractionalPart() < 10 ? "0" : "") + std::to_string(getFractionalPart()) + " " + getName();
    }

    // Pure Virtual Function
    virtual std::string getName() const = 0;
};



class Dollar : public Currency {
private:
    static const std::string name;

public:
    // Default constructor
    Dollar() : Currency() {}

    // Constructor for single double input eg. 4.99
    Dollar(double value) : Currency(value) {}

    /**
     * Purpose: Retrieves the name of the currency.
     * Pre:
     * Post:
     * Return: Returns a string that represents the name of the currency.
     */
    std::string getName() const override {
        return name;
    }
};


class Pound : public Currency {
private:
    static const std::string name;

public:
    // Default constructor
    Pound() : Currency() {}

    // Constructor for single double input eg. 4.99
    Pound(double value) : Currency(value) {}

    /**
     * Purpose: Retrieves the name of the currency.
     * Pre:
     * Post:
     * Return: Returns a string that represents the name of the currency.
     */
    std::string getName() const override {
        return name;
    }
};


// Static Constants
const std::string Dollar::name = "Dollar";
const std::string Pound::name = "Pound";