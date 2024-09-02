/** [NAME BLOCK]
 * Lab Number: 6
 * Names: Owen Man
 * Purpose: Demonstrate the use of Min Heaps to work with Currency objects
 */

/** [BUILD COMMAND]
 * g++ -o lab6main .\lab6main.cpp .\BinarySearchTree.cpp .\Currency.cpp .\MinHeap.cpp .\SinglyLinkedList.cpp .\StackQueue.cpp
 */ 

/* [CHANGES]
 * - Added getRoot, setRoot in BinarySearch Tree
 * - Added BSTNode* parent and getter/setter for it
 * - Updated BST::insert() to update parent
 * - Moved findNodeByCurrency to protected
 * - Changed BST::insert/search/delete to virtual
 */

#include <iostream>
#include "MinHeap.h"

using namespace std;

int main() {
    cout << "Program to demonstrate the use of traversals on Min Heaps.\n\n";
    
    MinHeap minHeap;
    double values[] = {57.12, 23.44, 87.43, 68.99, 111.22, 44.55, 77.77, 18.36, 543.21, 
                       20.21, 345.67, 36.18, 48.48, 101.00, 11.00, 21.00, 51.00, 1.00, 
                       251.00, 151.00};
    int counter = 0; // track inserted nodes

    for (double value : values) {
        minHeap.insert(new Dollar(value));
        counter++;

        if (counter == 10 || counter == 20) {
            cout << "\nAfter inserting " << counter << " items:\n\n";

            cout << "In-order traversal: ";
            minHeap.inOrder();
            cout << "\n\n";

            cout << "Post-order traversal: ";
            minHeap.postOrder();
            cout << "\n\n";

            cout << "Pre-order traversal: ";
            minHeap.preOrder();
            cout << "\n\n";

            cout << "Breadth-first traversal: ";
            minHeap.breadthFirst();
            cout << "\n\n";
        }
    }

    cout << "\nPress 'Enter' to end the program...";
    cin.get();
    return 0;
}