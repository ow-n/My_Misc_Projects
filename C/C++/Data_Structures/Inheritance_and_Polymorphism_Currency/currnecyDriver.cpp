/* NAME BLOCK
 * Lab Number: 2
 * Names: Owen Man & Calvin Zhou
 * Purpose: Demonstrate Inheritance and Polymorphism through performing operations on
 *          different currencies sharing the same base class.
 */

#include "currency.cpp"
#include <iostream>
using namespace std;

 /*
  * Purpose: Creates a Pound and Dollar object in a Currency array. Performs various
  *          operations and demonstrates OOP and error-handling. 
  * Pre: Currency class and derived classes are properly implemented.
  * Post: Operations on Currency object have been performed and printed and
  *       Errors have been caught.
  * Return:
  */
int main() {
    // Initalize 2 currencies and print their inital values
    Currency* currencies[2];
    currencies[0] = new Pound();
    currencies[1] = new Dollar();
    cout << currencies[0]->toString() << " " << currencies[1]->toString() << endl;

    // Add a pound object
    currencies[0]->add(Pound(1.11));
    cout << currencies[0]->toString() << " " << currencies[1]->toString() << endl;

    // Add a dollar object
    currencies[1]->add(Dollar(12.12));
    cout << currencies[0]->toString() << " " << currencies[1]->toString() << endl;

    // Error: Add dollar to pound object
    try {
        currencies[1]->add(Pound(3.45)); // This should throw an exception
    } catch (char const* errorMessage) {
        cout << errorMessage << endl;
    }
    cout << currencies[0]->toString() << " " << currencies[1]->toString() << endl;

    // Add a dollar object
    currencies[1]->add(Dollar(0.13));
    cout << currencies[0]->toString() << " " << currencies[1]->toString() << endl;

    // Subtract a dollar object
    currencies[1]->subtract(Dollar(10));
    cout << currencies[0]->toString() << " " << currencies[1]->toString() << endl;

    // Error: Subtract a dollar object too large
    try {
        currencies[1]->subtract(Dollar(2.5)); // This should throw an exception
    } catch (char const* errorMessage) {
        cout << errorMessage << endl;
    }
    cout << currencies[0]->toString() << " " << currencies[1]->toString() << endl;

    // Subtract a pound object
    currencies[0]->subtract(Pound(0.11));
    cout << currencies[0]->toString() << " " << currencies[1]->toString() << endl;

    // Test Other Methods
    /*
    Pound testPound{1};
    cout << testPound.toString() << endl;;
    cout << testPound.isEqual(*currencies[0]) << endl;
    testPound.add(Pound(0.01));
    cout << testPound.toString() << endl;;
    cout << currencies[0]->isEqual(testPound) << endl;
    cout << currencies[0]->isGreater(testPound) << endl;
    try {
        Pound negativePound{ -1 };
    } catch (char const* errorMessage) {
        cout << errorMessage << endl;
    }
    */

    // Clean up
    delete currencies[0];
    delete currencies[1];

    cout << "Press 'Enter' to end the program...";
    cin.get();
    return 0;
}