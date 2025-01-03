/* Linked List Implementation */

#include <iostream>
using namespace std;

struct Node {
    int num;
    Node *next;
};

// Creates Linked List from Array, Returns Head
Node* createLinkedList (int a[], int len) {
    if (len == 0) return nullptr; // Case: Empty Array

    Node *head = new Node; // create head node
    head->num = a[0];
    head->next = nullptr;

    Node *curr = head; // track last node

    for (int i = 1; i < len; i++) { // [i=1] so don't recreate head node
        Node *newNode = new Node;
        newNode->num = a[i];
        newNode->next = nullptr;

        curr->next = newNode;
        curr = newNode;
    }

    return head;
}

// Merge Array of Linked Lists, Returns Head
Node* mergeLinkedLists (Node **LL, int len){
    if (len == 0) return nullptr; // Case: Empty array

    Node *mergedHead = nullptr;
    Node *mergedTail = nullptr;

    for (int i = 0; i < len; i++) {
        Node *current = LL[i]; // current head of the list being merged
        while (current != nullptr) {
            // Create a new node with the current value
            Node *newNode = new Node;
            newNode->num = current->num;
            newNode->next = nullptr;

            // Append to the merged list
            if (mergedHead == nullptr) {
                mergedHead = newNode; // first node becomes the head
                mergedTail = newNode; // and the tail
            } else {
                mergedTail->next = newNode; // append to the tail
                mergedTail = newNode;       // update the tail
            }

            current = current->next; // move to the next node in the current list
        }
    }

    return mergedHead; // Return the head of the merged list
}
// Remove Duplicates from Linked List, Returns Head
Node* removeDuplicate(Node *L) {
    Node* current = L; // Current Node iterates through
    while (current != nullptr) {
        Node* runner = current; // Runner Node finds dupes
        while (runner->next != nullptr) {
            if (runner->next->num == current->num) {
                Node *temp = runner->next;
                runner->next = runner->next->next;
                delete temp;
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
    return L;
}

// Reverse Linked List, Returns Head
Node* reverseLinkedList(Node* L) {
    Node* prev = nullptr;
    Node* curr = L;
    Node* next = nullptr;

    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    L = prev; // curr gets set to nullptr, so head is [prev]
    return L;
}

void printLinkedList(Node *head) {
    Node *current = head;
    while (current != nullptr) {
        cout << current->num << " ";
        current = current->next;
    }
    cout << endl;
}

void printArray(int a[], int len) {
    for (int i = 0; i < len; i++) {
        cout << a[i] << " ";
    }
}

int main() {
    int LL1Arr[] = {1, 2, 3, 4, 5};
    int LL2Arr[] = {6, 7, 8, 9, 10};
    int LL3Arr[] = {2, 2, 2, 42, 5};

    cout << "Testing createLinkedList()" << endl;
    cout << "==========================" << endl;
    cout << "Array 1 Before: ";
    printArray(LL1Arr, 5);
    cout << "\n    creating linked list..." << endl;
    cout << "Linked List After: ";
    Node *LL1 = createLinkedList(LL1Arr, 5);
    printLinkedList(LL1);

    cout << "\n\nTesting mergeLinkedLists()" << endl;
    cout << "==========================" << endl;
    cout << "    creating Linked Lists 2 & 3..." << endl;
    Node *LL2 = createLinkedList(LL2Arr, 5);
    Node *LL3 = createLinkedList(LL3Arr, 5);
    cout << "    putting Linked Lists 1, 2, & 3 in an array..." << endl;
    Node *LLArr[] = {LL1, LL2, LL3};
    cout << "Linked List 1 Before: ";
    printLinkedList(LL1);
    cout << "Linked List 2 Before: ";
    printLinkedList(LL2);
    cout << "Linked List 3 Before: ";
    printLinkedList(LL3);
    cout << "    merging linked lists..." << endl;
    cout << "Merged Linked List After: ";
    Node *LLMerged = mergeLinkedLists(LLArr, 3);
    printLinkedList(LLMerged);
    
    cout << "\n\nTesting removeDuplicate()" << endl;
    cout << "=========================" << endl;
    cout << "Merged Linked List Before: ";
    printLinkedList(LLMerged);
    cout << "removing duplicates..." << endl;
    Node *noDupeLL = removeDuplicate(LLMerged);
    cout << "Removed Duplicates Linked List After: ";
    printLinkedList(noDupeLL);

    cout << "\n\nTesting reverseLinkedList()" << endl;
    cout << "===========================" << endl;
    cout << "Removed Duplicates Linked List Before: ";
    printLinkedList(noDupeLL);
    cout << "    reversing linked list..." << endl;
    Node *reversedLL = reverseLinkedList(noDupeLL);
    cout << "Reversed Linked List After: ";
    printLinkedList(reversedLL);

    return 0;
}
