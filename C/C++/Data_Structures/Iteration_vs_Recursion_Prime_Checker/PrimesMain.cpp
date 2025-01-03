// Demonstrate iteration vs recursion by checking primes in arrays
 
// NumInts = 5, Ints = 53 5099 1223 567 17
// NumInts = 4, Ints = 1871 8069 3581 6841

#include <iostream>
#include "Primes.h"

using namespace std;

/* PSEUDOCODE
 * Get the size of array by reading user input and store in 'size'
 * IF 'size' is greater than 16, then set it to 16 (SORT_MAX_SIZE)
 * 
 * FOR each index from 0 to 'size' DO
 *     Read user input for 'arr' at current 'index'
 * 
 * Call IsArrayPrimeIter to check if Array is Prime using Iteration
 * IF function returns True then
 *     Print "Prime Array using iteration"
 * ELSE
 *     Print "Not a Prime Array using iteration"
 *
 * Call IsArrayPrimeRecur to check if Array is Prime using Recursion
 * IF function returns True then
 *     Print "Prime Array using iteration"
 * ELSE
 *     Print "Not a Prime Array using iteration"
 */

/* 
 * Purpose: Takes user inputs to check if arrays are prime using iteration and recurrsion
 * Pre:
 * Post:
 * Return: 
 */
int main() {
    const int SORT_MAX_SIZE = 16;

    cout << "Enter the size of the array (max 16): ";
    int size;
    cin >> size;

    if (size > SORT_MAX_SIZE) {
        cout << "Input was too large, size set to 16";
        size = SORT_MAX_SIZE;
    }

    int arr[SORT_MAX_SIZE];
    cout << "Enter the elements of the array: ";
    for (int index = 0; index < size; index++) {
        cin >> arr[index];
    }

    // Iterative
    if (Primes::IsArrayPrimeIter(arr, size)) {
        cout << "Prime Array using iteration\n\n";
    } else {
        cout << "Not a Prime Array using iteration\n\n";
    }

    // Recursive
    if (Primes::IsArrayPrimeRecur(arr, size, 0)) {
        cout << "Prime Array using recursion\n\n";
    } else {
        cout << "Not a Prime Array using recursion\n\n";
    }

    cout << "Press 'Enter' to end the program...";
    cin.get();
    return 0;
}
