// Demonstrate iteration vs recursion by checking primes in user arrays

#include <iostream>
using namespace std;

// Prototypes
bool IsArrayPrimeIter(int arr[], int size);
bool IsArrayPrimeRecur(int arr[], int size, int index);
bool IsPrimeRecur(int num, int divisor);

// Main Function
int main() {
    const int SORT_MAX_SIZE = 16;

    cout << "Enter the size of the array (max 16): ";
    int size;
    cin >> size;

    if (size > SORT_MAX_SIZE) {
        size = SORT_MAX_SIZE;
    }

    int arr[SORT_MAX_SIZE];
    cout << "Enter the elements of the array: ";
    for (int index = 0; index < size; index++) {
        cin >> arr[index];
    }

    // Iterative
    if (IsArrayPrimeIter(arr, size)) {
        cout << "Prime Array usi=ng iteration\n\n";
    } else {
        cout << "Not a Prime Array using iteration\n\n";
    }

    // Recursive
    if (IsArrayPrimeRecur(arr, size, 0)) {
        cout << "Prime Array using recursion\n\n";
    } else {
        cout << "Not a Prime Array using recursion\n\n";
    }

    return 0;
}

// Iterative function to check if all elements in array are prime
bool IsArrayPrimeIter(int arr[], int size) {
    cout << "\nEntering IsArrayPrimeIter(int arr[], int size)\n";

    for (int index = 0; index < size; index++) {
        int num = arr[index];
        if (num <= 1) { // False: less or equal to 1
            cout << "Leaving IsArrayPrimeIter(int arr[], int size)\n";
            return false;
        }
        if (num != 2) {
            if (num % 2 == 0) { // False: divisible by 2
                cout << "Leaving IsArrayPrimeIter(int arr[], int size)\n";
                return false;
            }
            for (int divisor = 3; divisor * divisor <= num; divisor += 2) { // divisor^2 = upper limit checks
                if (num % divisor == 0) { 
                    cout << "Leaving IsArrayPrimeIter(int arr[], int size)\n";
                    return false; // False: divisible by odd numbers between 3 and the square root
                }
            }
        }
    }

    cout << "Leaving IsArrayPrimeIter(int arr[], int size)\n";
    return true;
}

// Recursive function to check if all elements in array are prime
bool IsArrayPrimeRecur(int arr[], int size, int index) {
    cout << "Entering IsArrayPrimeRecur(int arr[], int size, int index)\n";
    if (index == size) {
        cout << "Leaving IsArrayPrimeRecur(int arr[], int size, int index)\n";
        return true; // True: all elements checked and are prime
    }
    if (!IsPrimeRecur(arr[index], 2)) {
        cout << "Leaving IsArrayPrimeRecur(int arr[], int size, int index)\n";
        return false; // False: current element is not prime
    }
    return IsArrayPrimeRecur(arr, size, index + 1);
}

// Recursive function to check if a single number is prime
bool IsPrimeRecur(int num, int divisor) {
    cout << "Entering IsPrimeRecur(int num, int divisor)\n";
    if (num <= 1) {
        cout << "Leaving IsPrimeRecur(int num, int divisor)\n";
        return false; // False: less or equal to 1
    }
    if (divisor * divisor > num) {
        cout << "Leaving IsPrimeRecur(int num, int divisor)\n";
        return true; // True: no divisors other than 1 and num found
    }
    if (num % divisor == 0) {
        cout << "Leaving IsPrimeRecur(int num, int divisor)\n";
        return false; // False: divisible by divisor
    }
    return IsPrimeRecur(num, divisor + 1);
}
