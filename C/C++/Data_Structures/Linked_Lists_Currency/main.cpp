// Demonstrate the use of ADTs to work with Currency objects

#include "Currency.h"
#include "Dollar.h"
#include "LinkNode.h"
#include "SinglyLinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include <iostream>

using namespace std;

int main() {
    cout << "Program demonstration of Abstract Data Types by Owen Man & Calvin Zhou.\n\n";

    // Create the Dollar objects and add them to the array
    double dollarAmounts[] = {57.12, 23.44, 87.43, 68.99, 111.22, 44.55, 77.77, 18.36, 543.21, 20.21,
                              345.67, 36.18, 48.48, 101.00, 11.00, 21.00, 51.00, 1.00, 251.00, 151.00};
    Currency* currencies[20];
    cout << "Preparing Program by creating Dollar objects and adding them to the array...\n\n";
    for (int i = 0; i < 20; i++) {
        currencies[i] = new Dollar(dollarAmounts[i]);
    }

    // Testing SingleLinkedList Class --------------------
    cout << "Testing SinglyLinkedList...\n";
    SinglyLinkedList sll;

    cout << "Adding first 7 objects in reverse order...\n";
    int sllIndex = 0;
    for (int i = 6; i >= 0; --i) {
        sll.addCurrency(currencies[i], sllIndex);
        sllIndex++;
    }

    cout << "Searching for $87.43 and $44.56 in the list...\n";
    Dollar* searchTarget1 = new Dollar(87.43);
    Dollar* searchTarget2 = new Dollar(44.56);
    cout << "Found target $87.43 at index: " << sll.findCurrency(searchTarget1) << "\n";
    cout << "Target $44.56 was not found and returned: " << sll.findCurrency(searchTarget2) << "\n";

    cout << "Removing $111.22 and currency at index 2 from the list...\n";
    Dollar* searchTarget3 = new Dollar(111.22);
    sll.removeCurrency(sll.findCurrency(searchTarget3));
    sll.removeCurrency(2);
    cout << sll.printList() << "\n";
    cout << "Adding next 4 objects at their index in the linked list calculated as (index in array % 5)...\n";
    for (int i = 8; i <= 11; i++) { 
        sll.addCurrency(currencies[i], i % 5); 
    }

    cout << sll.printList() << "\n"; // deltee <-- 
    cout << "Removing 2 objects at indexes calculated as (countCurrency % 6) and (countCurrency / 7)...\n";
    sll.removeCurrency(sll.countCurrency() % 6);
    sll.removeCurrency(sll.countCurrency() / 7);
    cout << sll.printList() << "\n";

    // Testing Stack Class --------------------
    cout << "\nTesting Stack Class...\n";
    Stack st;

    cout << "Pushing 7 objects from the array index 13 onwards to the stack...\n";
    for (int i = 13; i < 20; i++) {
        st.push(currencies[i]);
    }

    cout << "Peeking the top of the stack: ";
    cout << st.peek()->toString() << "\n";

    cout << "Popping the stack 3 times...\n";
    st.pop();
    st.pop();
    st.pop();
    cout << st.printStack() << "\n";

    cout << "Pushing 5 more objects from the start of the objects array...\n";
    for (int i = 0; i < 5; i++) {
        st.push(currencies[i]);
    }

    cout << "Popping the stack 2 times...\n";
    st.pop();
    st.pop();
    cout << st.printStack() << "\n";

    // Testing Queue Class --------------------
    cout << "\nTesting Queue Class...\n";
    Queue q;
    
    cout << "Enqueueing the 7 objects at odd indexes starting from index 5 in the array...\n";
    for (int i = 5; i < 18; i+=2) {
        q.enqueue(currencies[i]);
    }

    cout << "Peeking the front and end of the queue: ";
    cout << q.peekFront()->toString() << " and " << q.peekRear()->toString() << "\n";

    cout << "Performing 2 dequeues in succession...\n";
    q.dequeue();
    q.dequeue();
    cout << q.printQueue() << "\n";

    cout << "Enqueueing 5 more objects from the index 10 in the array...\n";
    for (int i = 10; i < 15; i++) {
        q.enqueue(currencies[i]);
    }

    cout << "Dequeuing three times in succession...\n";
    q.dequeue();
    q.dequeue();
    q.dequeue();
    cout << q.printQueue() << "\n";

    cout << "\nCleaning up and deleting the Dollar objects...\n";
    for (int i = 0; i < 20; i++) {
        delete currencies[i];
    }
    
    cout << "Thank you for using our ADT demonstration. Goodbye." << "\n\n";
    cout << "Press 'Enter' to end the program...";
    cin.get();
    return 0;
}
