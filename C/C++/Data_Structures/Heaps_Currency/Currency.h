// Demonstrate the use of Min Heaps to work with Currency objects


#ifndef CURRENCY_H
#define CURRENCY_H

#include <string>

class Currency {
private:
    int wholePart;
    int fractionalPart;

public:
    Currency(); // Default Constructor
    Currency(double value); // Constructor for single double input
    Currency(const Currency& original); // Copy Constructor
    virtual ~Currency(); // Destructor

    int getWholePart() const;
    bool setWholePart(int wholePart);
    int getFractionalPart() const;
    bool setFractionalPart(int fractionalPart);

    /**
     * Purpose: Adds the value of another currency object to the invoking object.
     * Pre: 'other' - a valid Currency object.
     * Post: The value of the 'other' object is added to the invoking object.
     *       An exception is thrown if the 'other' object is of a different currency type.
     * Return: None.
     */
    void add(const Currency& other);

    /**
     * Purpose: Subtracts the value of another currency object from the invoking object.
     * Pre: 'other' - a valid Currency object.
     * Post: The value of the 'other' object is subtracted from the invoking object.
     *       An exception is thrown if the 'other' object is of a different currency type or if the subtraction would result in a negative value.
     * Return:
     */
    void subtract(const Currency& other);
    
    /**
     * Purpose: Checks if the value of another currency object is equal to the invoking object.
     * Pre: 'other' - a valid Currency object.
     * Post: The value of the invoking object is compared to the value of the 'other' object.
     *       An exception is thrown if the 'other' object is of a different currency type.
     * Return: Returns 'true' if the values of the invoking object and the 'other' object are equal, and 'false' otherwise.
     */
    bool isEqual(const Currency& other) const;

    /**
     * Purpose: Checks if the value of the invoking currency object is greater than another currency object.
     * Pre: 'other' - a valid Currency object.
     * Post: The value of the invoking object is compared to the value of the 'other' object.
     *       An exception is thrown if the 'other' object is of a different currency type.
     * Return: Returns 'true' if the value of the invoking object is greater than the value of the 'other' object, and 'false' otherwise.
     */
    bool isGreater(const Currency& other) const;

    /**
     * Purpose: Converts the value of the invoking currency object to a string.
     * Pre: None.
     * Post: The value of the invoking object is converted to a string in the format "xx.yy Currency".
     * Return: Returns a string representation of the invoking object's value.
     */
    std::string toString() const;

    virtual std::string getName() const = 0; // Pure Virtual Function
};




class Dollar : public Currency {
private:
    static const std::string name;

public:
    Dollar(); // Default constructor
    Dollar(double value); // Constructor for single double input eg. 4.99

    /**
     * Purpose: Retrieves the name of the currency.
     * Pre: None.
     * Post: None.
     * Return: Returns a string that represents the name of the currency.
     */
    std::string getName() const override;
};




class Pound : public Currency {
private:
    static const std::string name;

public:
    Pound(); // Default constructor
    Pound(double value); // Constructor for single double input eg. 4.99

    /**
     * Purpose: Retrieves the name of the currency.
     * Pre: None.
     * Post: None.
     * Return: Returns a string that represents the name of the currency.
     */
    std::string getName() const override;
};

#endif // CURRENCY_H
