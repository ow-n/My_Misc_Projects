#ifndef PRIMES_H
#define PRIMES_H

class Primes {
public:
    /* 
    * Purpose: Iterative function that checks if all elements in an array are prime
    * Pre: arr[] - a non empty array of integer numbers
    *      size  - the actual size of the array
    * Post: 
    * Return: true or false
    */
    static bool IsArrayPrimeIter(int arr[], int size);

    /* 
    * Purpose: Recursive function that checks if all elements in an array are prime
    * Pre: arr[] - a non empty array of integer numbers
    *      size  - the actual size of the array
    *      index - the index of the array that the function will check
    * Post: 
    * Return: true or false
    */
    static bool IsArrayPrimeRecur(int arr[], int size, int index);

    /* 
    * Purpose: Recursive function that checks if a given number is prime
    * Pre: arr[]   - a non empty array of integer numbers
    *      divisor - a number initially set to 2 that increments
    * Post: 
    * Return: true or false
    */
    static bool IsPrimeRecur(int num, int divisor);
};

#endif // PRIMES_H
