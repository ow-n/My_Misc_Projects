// Purpose: Demonstrate the use of Hash Tables to work with Currency objects

/** [BUILD COMMAND]
 * g++ -o lab5main .\lab5main.cpp .\Currency.cpp .\HashTable.cpp
 */ 

#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;

// Prototypes
void userInteractionLoop(const HashTable& hashtable);
bool isValidDollarFormat(const string& userInput);

/**
 * Purpose: Initialize and seed a hash table with predefined Dollar objects, display initial statistics, 
 *          and facilitate user interaction to search for Dollar objects within the hash table.
 * Pre: None.
 * Post: Hash table is seeded with Dollar objects, statistics are displayed, and user interaction 
 *       is facilitated until the user chooses to terminate the program.
 * Return: 0 indicating successful completion of the program.
 */
int main() {
    // Seeding 20 Dollar objects into a Hash Table
    HashTable hashTable;
    double values[] = {57.12, 23.44, 87.43, 68.99, 111.22, 44.55, 77.77, 18.36, 543.21, 
                       20.21, 345.67, 36.18, 48.48, 101.00, 11.00, 21.00, 51.00, 1.00, 
                       251.00, 151.00};
    for (double value : values) {
        Dollar dollar(value);
        hashTable.insert(dollar);
    }

    // Displaying statistics
    cout << "Data items loaded: " << hashTable.getNumOfItems() << endl;
    cout << "Load factor: " << hashTable.getLoadFactor() << endl;
    cout << "Number of collisions: " << hashTable.getCollisionCount() << endl;

    userInteractionLoop(hashTable);

    cout << "Press 'Enter' to end the program...";
    cin.get();
    return 0;
}

/**
 * Purpose: Provides an interactive loop for the user to search for specific Dollar values within the hash table.
 * Pre: 'hashTable' - a populated hash table of Dollar objects.
 * Post: The user is either provided with the index of the searched Dollar object within the hash table 
 *       or is informed that the data is invalid or not found. 
 *       Interaction continues until the user chooses to end it.
 * Return: None.
 */
void userInteractionLoop(const HashTable& hashTable) {
    string userInput;
    bool continueSearch = true;

    while (continueSearch) {
        cout << "\nEnter a Dollar value to search for (format: XX.XX): ";
        getline(cin, userInput);

        if (isValidDollarFormat(userInput)) {
            Dollar searchDollar(stod(userInput));
            int foundIndex = hashTable.search(searchDollar);

            if (foundIndex != -1) {
                cout << "Dollar object found at index: " << foundIndex << endl;
            } else {
                cout << "Invalid Data" << endl;
            }
        } else {
            cout << "Invalid input format" << endl;
        }

        // Ask user if they want to search again
        while (true) {
            cout << "\nDo you want to check again? (yes/no): ";
            getline(cin, userInput);

            if (userInput == "no" || userInput == "n") {
                continueSearch = false;
                break;
            } else if (userInput == "yes" || userInput == "y") {
                break;
            } else {
                cout << "Invalid input. Please enter 'yes' or 'no'.";
            }
        }
    }
}

/**
 * Purpose: Validate the format of a user-inputted dollar amount to ensure it matches the expected structure of XX.XX, 
 *          where X is a digit (0-9) and there are at most two digits after the decimal point.
 * Pre: 'userInput' is a string provided by the user and  represent a dollar value.
 * Post: The function determines whether the 'userInput' conforms to the expected dollar format.
 * Return: A boolean value indicating if the 'userInput' string matches the expected dollar format.
 */
bool isValidDollarFormat(const string& userInput) {
    size_t pos;
    double value;
    
    try {
        value = stod(userInput, &pos);
    } catch (const invalid_argument& e) {
        return false;  // If we can't convert the string to a double, it's not valid.
    }
    
    return pos == userInput.size() && (userInput.find('.') == string::npos || userInput.size() - userInput.find('.') <= 3);
}
