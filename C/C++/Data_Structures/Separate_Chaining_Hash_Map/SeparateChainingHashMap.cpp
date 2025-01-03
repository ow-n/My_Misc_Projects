/* Hash Map Implementation with Separate Chaining 
 * Stores and Manages Student Information
 * Insert(), Retrieve(), Remove() entries with Student ID
 * Key = Student ID
 * Value = Student Object */

#include <iostream>
#include <string>
#include <exception>

using namespace std;

// Hash Algorithm: DJB2 / DJBX33A
unsigned long DJB2hash(string str) {
    const char* cstr = str.c_str();
    unsigned long hash = 5381;
    int c;
    while (c = *cstr++) {
        hash = hash * 33 + c;
    }
    return hash;
}

// Stores Student Information
class Student {
public:
    string name;
    string studentID;
    int age;
    double gpa;

    Student(string name, string studentID, int age, double gpa) {
        this->name = name;
        this->studentID = studentID;
        this->age = age;
        this->gpa = gpa;
    }
};

// Entry Class to hold students in HashMap
class Entry {
    string key;
    Student *value;
    Entry *next;
    
public:
    Entry(string key, Student *value) {
        this->key = key;
        this->value = value;
        this->next = nullptr;
    }

    string getKey() { return key; }
    Student* getValue() { return value; }
    Entry* getNext() { return next; }
    void setNext(Entry* next) { this->next = next; }
};

// HashMap Class
class HashMap {
    Entry **table;
    int size;

public:
    HashMap(int size) {
        this->size = size;
        table = new Entry*[size];
        for(int i= 0; i < size; i++) {
            table[i] = NULL;
        }
    }

    /* Separate Chaining Functions */
    ~HashMap() {
        for(int i = 0; i < size; i++) { // for each bucket
            Entry *currentEntry = table[i]; // get pointer to front of LinkedList
            while(currentEntry != NULL) { // iterate through all entries in LinkedList
                Entry *nextEntry = currentEntry->getNext();
                delete currentEntry;
                currentEntry = nextEntry;
            }
        }
        delete[] table;
    }

    // Insert Student into HashMap by Student ID | Separate Chaining
    void put(Entry *e) {
        string key = e->getKey();           // get key from entry
        int index = DJB2hash(key) % size;   // get index from hash
        Entry *currentEntry = table[index]; // get pointer to front of LinkedList of bucket

        if (currentEntry == NULL) { // if buket empty
            table[index] = e;       // just insert the entry
        } else {                    // else go to end of LinkedList and insert
            while (currentEntry->getNext() != NULL) {
                currentEntry = currentEntry->getNext();
            }
            currentEntry->setNext(e);
        }
    }

    // Get Student from HashMap by Student ID | Separate Chaining
    Entry* get(string key) {
        int index = DJB2hash(key) % size;   // get index from hash
        Entry* currentEntry = table[index]; // get pointer to front of LinkedList of bucket

        // Traverse LinkedList to find Entry with matching key
        while (currentEntry != NULL) {
            if (currentEntry->getKey() == key) {
                return currentEntry;
            }
            currentEntry = currentEntry->getNext();  // iterate to through all entries
        }

        return NULL; // key not found
    }

    // Remove Student from HashMap by Student ID | Separate Chaining
    Entry* remove(string key) {
        int index = DJB2hash(key) % size;   // get index from hash
        Entry* current = table[index];      // get pointer to front of LinkedList of bucket
        Entry* prev = nullptr;              // track pointer to previous entry

        // Traverse LinkedList to find Entry with matching key
        while (current != nullptr && current->getKey() != key) {
            prev = current;
            current = current->getNext();
        }

        if (current == nullptr) {
            return nullptr; // key not found
        }

        // Remove 'current' by updating pointers
        if (prev != nullptr) { // entry is not first node
            prev->setNext(current->getNext());
        } else { // entry is first node
            table[index] = current->getNext(); // update bucket index pointer to next entry
        }

        return current;
    }

    /* Linear Probing Functions */
    /*
    ~HashMap() {
        for(int i = 0; i < size; i++)
            if(table[i] != NULL) {
                delete table[i];
            }
            delete[] table;
    }

    void put(Entry *e) {
        string key = e->getKey();
        int index = DJB2hash(key) % size;
        int startIndex = index;
        while(table[index] != NULL && table[index]->getKey() != key && table[index]->getKey() != "empty") {
            index = (index + 1) % size;
            if(index == startIndex) throw Overflow();
        }
        table[index] = e;
    }

    Entry* get(string key) {
        int index = DJB2hash(key) % size;
        int startIndex = index;
        while(table[index] != NULL && table[index]->getKey() != key) {
            index = (index + 1) % size;
            if(index == startIndex) return NULL;
        }
        return table[index];
    }

    Entry* remove(string key) {
        int index = DJB2hash(key) % size;
        int startIndex = index;
        while(table[index] != NULL && table[index]->getKey() != key) {
            index = (index + 1) % size;
            if(index == startIndex) return NULL;
        }
        Entry *e = table[index];
        delete e;
        table[index] = new Entry("empty", 0);
        return e;
    }
   */
};

int main() {
    HashMap hashMap(3);

    // Test data
    Student s1("Person 1", "1234567891", 20, 4.0);
    Student s2("Person 2", "1234567892", 21, 3.5);
    Student s3("Person 3", "1234567893", 22, 3.0);
    Student s4("Person 4", "0000000000", 21, 2.5); // same IDs
    Student s5("Person 5", "0000000000", 20, 2.0); // cause collision

    // Insert Entries: Key = Student ID & Value = Student Object
    hashMap.put(new Entry(s1.studentID, &s1));
    hashMap.put(new Entry(s2.studentID, &s2));
    hashMap.put(new Entry(s3.studentID, &s3));
    hashMap.put(new Entry(s4.studentID, &s4));
    hashMap.put(new Entry(s5.studentID, &s5));

    // Query Entries
    Entry* e5 = hashMap.get(s5.studentID);
    if (e5 != nullptr)
        cout << "Code Working: Found Person 5" << endl;
    else
        cout << "Code Issue: Couldn't find Person 1" << endl;

    Entry* eX = hashMap.get("5555555555"); // get Entry from Student 1 ID 
    if (eX != nullptr) 
        cout << "Code Issue: Found Non-Existant Person" << endl;
    else
        cout << "Code Working: Couldn't find fake person" << endl;

    // Remove entries
    Entry* removedEntry = hashMap.remove(s1.studentID); // remove Person 1
    Entry* e1 = hashMap.get(s1.studentID);              // try find Person 1
    if (e1 != nullptr)
        cout << "Code Issue: Person 1 not deleted" << endl;
    else
        cout << "Code Working: Deleted Person 1" << endl;

    return 0;
}