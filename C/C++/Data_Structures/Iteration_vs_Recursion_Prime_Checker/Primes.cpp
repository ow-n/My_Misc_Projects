#include <iostream>
#include "Primes.h"

/* PSEUDOCODE
 * Function IsArrayPrimeIter takes an array of integers and the size of the array
 * For each index from 0 to "size":
 *     Assign the value at the current index to "num"
 * If num is less than or equal to 1:
 *     Return false
 * If num is not equal to 2:
 *     If num is divisible by 2:
 *         Return false
 *     For each odd divisor from 3 up to the square root of num:
 *         If num is divisible by the current divisor:
 *            Return false
 *  Return true
 */
bool Primes::IsArrayPrimeIter(int arr[], int size) {
    std::cout << "\nEntering IsArrayPrimeIter\n";

    for (int index = 0; index < size; index++) {
        int num = arr[index];

        // False if less or equal to 1
        if (num <= 1) {
            std::cout << "Leaving IsArrayPrimeIter()\n";
            return false;
        }

        // False if...
        if (num != 2) {
            // False if divisibly by 2
            if (num % 2 == 0) {
                std::cout << "Leaving IsArrayPrimeIter\n";
                return false;
            }
            // False if divisible by by odd numbers up to sqrt(num)
            for (int divisor = 3; divisor * divisor <= num; divisor += 2) {
                if (num % divisor == 0) { 
                    std::cout << "Leaving IsArrayPrimeIter\n";
                    return false;
                }
            }
        }
    }

    // True if num = 2
    std::cout << "Leaving IsArrayPrimeIter\n";
    return true;
}

/* PSEUDOCODE
 * Function IsArrayPrimeRecur takes an array of integers, the size of the array, and an index as inputs
 * If the index is equal to the size of the array:
 *     Return true
 * If the number at the current index of the array is not prime from the function call IsPrimeRecur:
 *     Return false
 * Return the result of calling IsArrayPrimeRecur with the array, its size, and the next index
 */
bool Primes::IsArrayPrimeRecur(int arr[], int size, int index) {
    std::cout << "Entering IsArrayPrimeRecur\n";
    bool result;

    // Base case: all elements checked and are prime
    if (index == size) {
        result = true;
    }
    // Recursion case: check if current element is prime
    else if (!IsPrimeRecur(arr[index], 2)) {
        result = false;
    } else {
        result = IsArrayPrimeRecur(arr, size, index + 1);
    }

    std::cout << "Leaving IsArrayPrimeRecur\n";
    return result;
}

/* PSEUDOCODE
 * Function IsPrimeRecur takes a number and a divisor as inputs
 * If the number is less than or equal to 1:
 *     Return false
 * If the square of the divisor is greater than the number:
 *     Return true
 * If the number is divisible by the divisor:
 *     Return false
 * If the divisor is 2:
 *     Call IsPrimeRecur with the number and the next divisor
 * Else:
 *     Call IsPrimeRecur with the number and the next odd divisor
 */
bool Primes::IsPrimeRecur(int num, int divisor) {
    bool result;

    if (num <= 1) { 
        result = false;
    } 
    else if (divisor * divisor > num) { 
        result = true;
    }
    else if (num % divisor == 0) { 
        result = false;
    }
    else if (divisor == 2) { 
        result = IsPrimeRecur(num, divisor + 1);
    }
    else {
        result = IsPrimeRecur(num, divisor + 2);
    }

    return result;
}
