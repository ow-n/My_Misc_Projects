// Demonstrate the use of Hash Tables to work with Currency objects

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Currency.h"

class HashTable {
private:
    Dollar** table;  // pointers to pointers to Dollar objects, allows dynamic array/expansion
    int tableSize; // size of hash table
    int numOfItems;
    int collisionCount;
    int wholeMultiplier; // multiplier for whole part of Dollar in hash function
    int fractionalMultiplier; // multiplier for fractional part of Dollar in hash function

    /**
     * Purpose: Computes the hash index for a given Dollar object based on its whole and fractional parts.
     * Pre: 'dollar' - a valid Dollar object.
     * Post: None.
     * Return: The computed hash index for the provided Dollar object.
     */
    int hashFunction(const Dollar& dollar) const;

    /**
     * Purpose: Resolves collisions by determining the next suitable index using quadratic probing.
     * Pre: 'index' - the original index that has a collision.
     *      'count' - the number of times we've probed to resolve collisions for the current insertion.
     * Post: None.
     * Return: The new index after applying quadratic probing.
     */
    int quadraticProbe(int index, int count) const;

    /**
     * Purpose: Determines if a given number is prime.
     * Pre: 'num' - a valid integer.
     * Post: None.
     * Return: true if 'num' is a prime number, false otherwise.
     */
    bool isPrime(int num);

    /**
     * Purpose: Finds the next prime number greater than or equal to the given number.
     * Pre: 'num' - a valid integer.
     * Post: None.
     * Return: The next prime number greater than or equal to 'num'.
     */
    int getNextPrime(int num);

public:
    // Constructor & Destructor
    HashTable(int wholeMultiplier = 2, int fractionalMultiplier = 3, int tableSize = 29);
    ~HashTable();

    // Getters
    int getWholeMultiplier() const;
    int getFractionalMultiplier() const;
    int getNumOfItems() const;
    double getLoadFactor() const;
    int getCollisionCount() const;
    int getTableSize() const;

    /**
     * Purpose: Inserts a Dollar object into the hash table.
     * Pre: 'dollar' - a valid Dollar object to insert.
     * Post: The Dollar object is inserted into the hash table based on its hash index.
     *       If a collision occurs, quadratic probing is used to resolve it.
     *       If the load factor exceeds 0.8, the table is expanded.
     * Return: true if the insertion was successful (i.e., the Dollar object didn't already exist), false otherwise.
     */
    bool insert(const Dollar& dollar);
    
    /**
     * Purpose: Expands the hash table to the next prime number >= tableSize * 2 and rehashes all existing items.
     * Pre: None.
     * Post: The hash table has been resized and all existing items have been re-inserted into the new table.
     * Return: None (void method).
     */
    void expandTable();
    
    /**
     * Purpose: Searches for a given Dollar object in the hash table.
     * Pre: 'dollar' - a valid Dollar object to search for.
     * Post: None.
     * Return: The index where the Dollar object was found in the hash table; 
     *         returns -1 if the Dollar object is not present in the table.
     */
    int search(const Dollar& dollar) const;

};

#endif // HASHTABLE_H
