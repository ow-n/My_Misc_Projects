// Iteratively check if all elements in a vector are prime

#include <iostream>
#include <vector>

// Function declarations
bool IsPrime(int num);
bool IsArrayPrimeIter(const std::vector<int>& arr);

int main() {
    std::vector<int> primeArray = {2, 3, 5, 7, 11};
    std::vector<int> nonPrimeArray = {1, 2, 3, 5, 7};

    if (IsArrayPrimeIter(primeArray))
        std::cout << "Array is prime\n";
    else
        std::cout << "Array is not prime\n";

    return 0;
}

// Function to check if all elements in a vector are prime
bool IsArrayPrimeIter(const std::vector<int>& arr) {
    std::cout << "Entering IsArrayPrimeIter(std::vector<int>& arr)\n";

    for (int num : arr) {
        if (!IsPrime(num)) {
            std::cout << "Leaving IsArrayPrimeIter(std::vector<int>& arr)\n";
            return false;
        }
    }

    std::cout << "Leaving IsArrayPrimeIter(std::vector<int>& arr)\n";
    return true;
}

// Function to check if a number is prime or not
bool IsPrime(int num) {
    if (num <= 1)
        return false;
    if (num == 2)
        return true;
    if (num % 2 == 0)
        return false;
    for (int i = 3; i * i <= num; i += 2)
        if (num % i == 0)
            return false;
    return true;
}
