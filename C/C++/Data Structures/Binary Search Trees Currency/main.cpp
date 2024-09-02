// Demonstrate the use of Binary Search Trees to work with Currency objects

/** [BUILD COMMAND]
 * g++ -o lab4main .\lab4main.cpp .\BinarySearchTree.cpp .\Currency.cpp .\SinglyLinkedList.cpp .\StackQueue.cpp
 */ 

/** [CHANGES]
 * We combined some of the .h and .cpp files.
 * No implementation was changed in previous file.
 */ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Currency.h"
#include "BinarySearchTree.h"

using namespace std;

// Constant Variable
const double INVALID_VALUE = -1.0;

enum MenuOption {
    INSERT = 1, // subsequent enumerators are +1
    SEARCH,
    DELETE,
    PRINT_TRAVERSALS,
    EXIT
};

// Prototypes
void printMessage(const string& message, ostringstream& oss);
void printMessage(const string& part1, double value, const string& part2, ostringstream& oss);
void performTraversals(BinarySearchTree& tree, ostringstream& oss);
string getTraversalString(BinarySearchTree& tree, void (BinarySearchTree::*traversalMethod)() const);
void displayUserInterface(BinarySearchTree& tree, ostringstream& oss);
void displayMenu(); // helper for displayUserInterface()
void handleInsert(BinarySearchTree& tree, ostringstream& oss); // helper for displayUserInterface()
void handleSearch(BinarySearchTree& tree, ostringstream& oss); // helper for displayUserInterface()
void handleDelete(BinarySearchTree& tree, ostringstream& oss); // helper for displayUserInterface()
double getUserInputValue(const string& prompt, ostringstream& oss); // helper for handle()
bool isValidNumber(const string& rawValue); // helper for getUserInputValue()

/**
 * Purpose: Console program that allows a user to interact with a Binary Search Tree.
 * Pre: None.
 * Post: Program output written to "output.txt" file.
 * Return: None.
 */
int main() {
    // Inserting 20 Dollar objects into a Binary Search Tree
    BinarySearchTree tree;
    double values[] = {57.12, 23.44, 87.43, 68.99, 111.22, 44.55, 77.77, 18.36, 543.21, 
                       20.21, 345.67, 36.18, 48.48, 101.00, 11.00, 21.00, 51.00, 1.00, 
                       251.00, 151.00};
    for (double value : values) {
        tree.insert(new Dollar(value));
    }

    ofstream outfile("output.txt");
    ostringstream oss;
    printMessage("A program that demonstrates a Binary Search Tree Data Structure on Currency objects.", oss);

    performTraversals(tree, oss);

    displayUserInterface(tree, oss);

    outfile << oss.str(); // write results stored in oss to "output.txt"
    outfile.close();

    cout << "Press 'Enter' to end the program...";
    cin.get();
    return 0;
}

/**
 * Purpose: Prints a message to the console and appends it to an ostringstream.
 * Pre: 'message' - a valid string.
 * Post: 'message' is printed to the console and appended to 'oss'.
 * Return: None.
 */
void printMessage(const string& message, ostringstream& oss) {
    cout << message;
    oss << message;
}

/**
 * Purpose: Constructs a message with two strings and a double value, then prints and appends it.
 * Pre: 'part1', 'part2' - valid string parts; 'value' - a double to be included between the string parts.
 * Post: The constructed message is printed to the console and appended to 'oss'.
 * Return: None.
 */
void printMessage(const string& part1, double value, const string& part2, ostringstream& oss) {
    ostringstream message;
    message << fixed << setprecision(2); // sets precision to two decimal places
    message << part1 << value << part2;
    printMessage(message.str(), oss); // reuse the existing printMessage function
}

/**
 * Purpose: Performs different traversals on a binary search tree and prints the results.
 * Pre: 'tree' - a valid BinarySearchTree object; 'mainOss' - a reference to an ostringstream.
 * Post: Various traversals are performed on 'tree', and the results are printed to the console and appended to 'mainOss'.
 * Return: None.
 */
void performTraversals(BinarySearchTree& tree, ostringstream& oss) {
    // For each traversal, call it twice: once for the console and once for the string
    auto printTraversal = [&](const string& title, void (BinarySearchTree::*traversalMethod)() const) {
        cout << title;
        (tree.*traversalMethod)();
        string result = getTraversalString(tree, traversalMethod);
        oss << title << result;
    };

    printTraversal("\n\nBreadth-first traversal:\n", &BinarySearchTree::breadthFirst);
    printTraversal("\n\nIn-order traversal:\n", &BinarySearchTree::inOrder);
    printTraversal("\n\nPre-order traversal:\n", &BinarySearchTree::preOrder);
    printTraversal("\n\nPost-order traversal:\n", &BinarySearchTree::postOrder);
    printMessage("\n\n", oss);
}

/**
 * Purpose: Retrieves a traversal result as a string.
 * Pre: 'tree' - a valid BinarySearchTree object; 'traversalMethod' - a pointer to a member function of BinarySearchTree for the traversal.
 * Post: The traversal result of 'tree' using 'traversalMethod' is captured as a string.
 * Return: A string containing the traversal result.
 */
string getTraversalString(BinarySearchTree& tree, void (BinarySearchTree::*traversalMethod)() const) {
    ostringstream oss;
    streambuf* originalCoutBuffer = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());
    (tree.*traversalMethod)();
    cout.rdbuf(originalCoutBuffer);
    return oss.str();
}

/**
 * Purpose: Displays the user interface and handles user interactions for managing the binary search tree.
 * Pre: 'tree' - a valid BinarySearchTree object; 'oss' - a reference to an ostringstream.
 * Post: User interactions are processed, and the binary search tree is manipulated accordingly.
 * Return: None.
 */
void displayUserInterface(BinarySearchTree& tree, ostringstream& oss) {
    string choice;
    bool exitRequested = false;

    do {
        displayMenu();
        getline(cin, choice); // read the entire line

        if (isValidNumber(choice) && choice.find('.') == std::string::npos) { // filters decimals as well
            MenuOption option = static_cast<MenuOption>(stoi(choice)); // convert input from string to MenuOption enumerator

            switch (option) {
                case INSERT:
                    handleInsert(tree, oss);
                    break;
                case SEARCH:
                    handleSearch(tree, oss);
                    break;
                case DELETE:
                    handleDelete(tree, oss);
                    break;
                case PRINT_TRAVERSALS:
                    performTraversals(tree, oss);
                    break;
                case EXIT:
                    printMessage("Exiting the program.", oss);
                    exitRequested = true; // set flag to exit loop
                    break; // exits to main()
                default:
                    cout << "Invalid choice. Please try again.\n\n";
            }
        } else {
            cout << "Invalid choice. Please try again.\n\n";
        }
    } while (!exitRequested);
}

void displayMenu() { // change output if menu changes
    cout << "\nSelect an operation (E.g. \"1\"):\n";
    cout << "1. Insert\n2. Search\n3. Delete\n4. Print Traversals\n5. Exit\n";
    cout << "Choice: ";
}

/**
 * Purpose: Inserts a value into the binary search tree.
 * Pre: 'tree' - a valid BinarySearchTree object; 'oss' - a reference to an ostringstream.
 * Post: The value is inserted into 'tree' unless it is a duplicate.
 * Return: None.
 */
void handleInsert(BinarySearchTree& tree, ostringstream& oss) {
    double value = getUserInputValue("Enter the value to insert: ", oss);
    if (value == INVALID_VALUE) {
        return; // error message already printing in getUserInputValue()
    }
    if (tree.search(value)) {
        printMessage("Duplicate value. \"", value, "\" Ignored.\n\n", oss);
    } else {
        tree.insert(new Dollar(value));
        printMessage("Value \"", value, "\" inserted.\n\n", oss);
    }
}

/**
 * Purpose: Searches for a value in the binary search tree.
 * Pre: 'tree' - a valid BinarySearchTree object; 'oss' - a reference to an ostringstream.
 * Post: The search result is printed to the console and appended to 'oss'.
 * Return: None.
 */
void handleSearch(BinarySearchTree& tree, ostringstream& oss) {
    double value = getUserInputValue("Enter the value to search: ", oss);
    if (value != INVALID_VALUE) {
        if (tree.search(value)) {
            printMessage("Value \"", value, "\" found.\n\n", oss);
        } else {
            printMessage("Value \"", value, "\" not found.\n\n", oss);
        }
    }
}

/**
 * Purpose: Deletes a value from the binary search tree.
 * Pre: 'tree' - a valid BinarySearchTree object; 'oss' - a reference to an ostringstream.
 * Post: The value is deleted from 'tree' if found.
 * Return: None.
 */
void handleDelete(BinarySearchTree& tree, ostringstream& oss) {
    double value = getUserInputValue("Enter the value to delete: ", oss);
    if (value != INVALID_VALUE) {
        if (tree.deleteNode(value)) {
            printMessage("Value \"", value, "\" deleted.\n\n", oss);
        } else {
            printMessage("Value \"", value, "\" not found. Deletion failed.\n\n", oss);
        }
    }
}

/**
 * Purpose: Retrieves a user input value as a double.
 * Pre: 'prompt' - a valid string to prompt the user; 'oss' - a reference to an ostringstream.
 * Post: The user's input value is returned if valid.
 * Return: A double representing the user's input value, or INVALID_VALUE if the input is invalid.
 */
double getUserInputValue(const string& prompt, ostringstream& oss) {
    string rawValue;
    cout << prompt;
    getline(cin, rawValue);
    if (isValidNumber(rawValue)) {
        double value = stod(rawValue);
        return value;
    } else {
        printMessage("Invalid value. \"" + rawValue + "\" Ignored.\n\n", oss);
        return INVALID_VALUE;
    }
}

/**
 * Purpose: Validates whether a given string can be converted to a double with up to 2 decimal places.
 * Pre: 'rawValue' - a string to be validated.
 * Post: None.
 * Return: True if 'rawValue' is a valid positive number with up to 2 decimal places, False otherwise.
 */
bool isValidNumber(const string& rawValue) {
    int decimalPointCount = 0;
    bool hasDigit = false; // ensures at least one digit exists
    int decimalPlaces = 0; // tracks number of digits after the decimal point

    // Check if remaining characters are all digits or a single decimal point
    for (char c : rawValue) {
        if (isspace(c) || c == '-') {
            return false; // spaces and negative signs not allowed
        }

        if (isdigit(c)) {
            hasDigit = true;
            if (decimalPointCount > 0) {
                decimalPlaces++;
            }
        } else if (c == '.' && decimalPointCount == 0) {
            decimalPointCount++;
        } else {
            return false; // any other character not allowed
        }

        if (decimalPlaces > 2) {
            return false; // more than 2 decimal places not allowed
        }
    }

    return hasDigit && (decimalPointCount <= 1);
}
