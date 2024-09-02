// Demonstrate the use of Hash Tables to work with Currency objects

#include "HashTable.h"

// HashTable Class Implementation
// Private Methods
int HashTable::hashFunction(const Dollar& dollar) const {
    int wholePart = dollar.getWholePart();
    int fractionalPart = dollar.getFractionalPart();
    return ((wholeMultiplier * wholePart) + (fractionalMultiplier * fractionalPart)) % tableSize; // (m*w + n*f) % size
}

int HashTable::quadraticProbe(int index, int count) const {
    return (index + (count * count)) % tableSize;
}

bool HashTable::isPrime(int num) {
    if (num <= 1) return false;
    if (num <= 3) return true;

    if (num % 2 == 0 || num % 3 == 0) return false;

    int i = 5;
    while (i * i <= num) {
        if (num % i == 0 || num % (i + 2) == 0) return false;
        i += 6;
    }

    return true;
}

int HashTable::getNextPrime(int num) {
    while (!isPrime(num)) {
        num++;
    }
    return num;
}

// Pubic Methods
HashTable::HashTable(int wholeMultiplier, int fractionalMultiplier, int tableSize) 
    : wholeMultiplier(wholeMultiplier), fractionalMultiplier(fractionalMultiplier), numOfItems(0), collisionCount(0), tableSize(tableSize) {
    table = new Dollar*[tableSize];
    for(int i = 0; i < tableSize; i++) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    for (int i = 0; i < tableSize; i++) {
        if (table[i] != nullptr) {
            delete table[i];
        }
    }
    delete[] table;
}

// Getters
int HashTable::getWholeMultiplier() const {
    return wholeMultiplier; 
}

int HashTable::getFractionalMultiplier() const {
    return fractionalMultiplier;
}

int HashTable::getNumOfItems() const {
    return numOfItems;
}

double HashTable::getLoadFactor() const {
    return static_cast<double>(numOfItems) / tableSize;
}

int HashTable::getCollisionCount() const {
    return collisionCount;
}

int HashTable::getTableSize() const {
    return tableSize;
}


// Methods
bool HashTable::insert(const Dollar& dollar) {
    // Expand table is load greater than 0.8
    if (getLoadFactor() >= 0.8) {
        expandTable();
    }

    int index = hashFunction(dollar);
    int originalIndex = index;
    int count = 1; // used for quadratic probing

    while (table[index] != nullptr) {
        if (table[index]->isEqual(dollar)) {
            return false; // value already exists
        }
        collisionCount++;
        index = quadraticProbe(originalIndex, count);
        count++;
    }

    table[index] = new Dollar(dollar);  // make a copy of the Dollar object
    numOfItems++;
    return true;
}

void HashTable::expandTable() {
    // Determine the new table size, which is the next prime number >= 2 times the current table size.
    const int NEW_TABLE_SIZE = getNextPrime(tableSize * 2);
    
    // Allocate memory for the new table and initialize all slots to nullptr.
    Dollar** newTable = new Dollar*[NEW_TABLE_SIZE];
    for (int i = 0; i < NEW_TABLE_SIZE; i++) {
        newTable[i] = nullptr;
    }

    // Store the pointer to the old table and its size.
    Dollar** oldTable = table;
    int oldTableSize = tableSize;

    // Point the table pointer to the new table and update the table size.
    table = newTable;
    tableSize = NEW_TABLE_SIZE;

    // Reset the item count before re-inserting items.
    numOfItems = 0;

    // Re-insert the items from the old table into the new table.
    for (int i = 0; i < oldTableSize; i++) {
        if (oldTable[i] != nullptr) {
            insert(*oldTable[i]);
            delete oldTable[i];  // Free memory for the old Dollar object.
        }
    }

    // Delete the old table.
    delete[] oldTable;
}

int HashTable::search(const Dollar& dollar) const {
    // Compute the starting hash index.
    int index = hashFunction(dollar);
    int originalIndex = index;
    int count = 1;

    // Begin the search loop.
    while (table[index] != nullptr) {
        // Check if the item at the current index matches the search item.
        if (table[index]->isEqual(dollar)) {
            return index;
        }
        // If not, apply quadratic probing to find the next index to check.
        index = quadraticProbe(originalIndex, count);
        count++;

        // If we've looped through the entire table without finding the item, break out of the loop.
        if (count > tableSize) {
            break; // exit loop 
        }
    }

    return -1; // return -1 if Dollar object not found
}
