/* The Five Sorting Algorithms
 * When I was writing this, I was thinking that the unsorted array was getting smaller,
 * so it made more sense to me that the outer loop function decreases in length
 * instead of incrementing the 'i'.
 * 
 * I also included my own runTestCases() function to test all the sorting algorithms.
 * */

#include <iostream>
#include <string>
using namespace std;

/* Selection Sort: O(n^2)
 * Sorts in Ascending order
 * Shifts largest elements to the right
 * 'len' is treated as unsorted array length
 */
void selectionSort(int A[], int len) { 
    if (len <= 1) return; // array is 0 or 1 elements

    for (int i = 0; i < len - 1; len--) { // repeats search, reduce unsorted array length
        int maxIndex = 0;
        for (int j = 1; j <= len - 1; j++) { // find max element
            if (A[j] > A[maxIndex]) {
                maxIndex = j;
            }
        }
        swap(A[maxIndex], A[len - 1]); // Swap maxIndex with end of unsorted array
    }
}

/* Bubble Sort: O(n^2)
 * Sorts in Ascending order
 * Bubbles largest elements to the right
 * 'len' is treated as 'to_do'
 */
void bubbleSort(int A[], int len) {
    if (len <= 1) return; // array is 0 or 1 elements

    bool didSwap = false;
    for (int i = 0; i < len - 1; len--) { // repeats search, reduce unsorted array length
    didSwap = false;
        for (int j = 1; j <= len - 1; j++) { // swaps higher element right
            if (A[j - 1] > A[j]) {
                swap(A[j], A[j - 1]);
                didSwap = true;
            }
        }
        if (!didSwap) break; // if no swaps, array is sorted
    }
}

/* Insertion Sort: O(n^2)
 * Sorts in Ascending order
 * Iterates up array, swapping lower elements left
 */
void insertionSort(int A[], int len) {
    for (int i = 1; i <= len - 1; i++) {
        int j = i;
        while ((A[j - 1] > A[j]) && j > 0) { // swaps lower elements left
            swap(A[j - 1], A[j]);
            j--;
        }
    }
}

/* Quick Sort: O(nlogn) commonly*
 * Sorts in Ascending order
 * Iterates up array, swapping lower elements left
 */
void quickSort(int A[], int low, int high);
int partition(int A[], int low, int high);

void quickSort(int A[], int len) {
    quickSort(A, 0, len - 1);
}

void quickSort(int A[], int low, int high) {
    if (low >= high) return; // base case
    
    int mid = partition(A, low, high); // split middle
    quickSort(A, low, (mid - 1)); // sort left
    quickSort(A, (mid + 1), high); // sort right
}

void printArray(int A[], int size);
int partition(int A[], int low, int high) {
    int pivot = A[low]; // Choose first element as pivot
    int mid = low + 1;
    int i = low + 1;

    while (i <= high) { // iterate through array
        if (A[i] <= pivot) { // i is less than pivot -> swap
            swap(A[mid++], A[i]);
            printArray(A, 5);
        }
        i++;
    }
    swap(A[low], A[mid - 1]); // swap pivot to mid
    return mid - 1;
}

/* Merge Sort: O(nlogn)
 * Sorts in ascending order
 */
void mergeSort(int A[], int low, int high);
void merge(int A[], int low, int mid, int high);

void mergeSort(int A[], int len) {
    mergeSort(A, 0, len - 1);
}

void mergeSort(int A[], int low, int high) {
    if (low == high) return; // base case

    int mid = (low + high) / 2;  // split middle
    mergeSort(A, low, mid);      // sort left
    mergeSort(A, (mid + 1), high); // sort right
    merge(A, low, mid, high);    // merge
}

void merge(int A[], int low, int mid, int high) {
    int* B = new int[high - low + 1]; // Temporary array to store merged result
    int i = low;     // iterates subarray 1
    int j = mid + 1; // iterates subarray 2
    int k = 0;       // iterates B

    // Merge Two Halves into B
    while ((i <= mid) && (j <= high)) { // while both subarray nonempty
        // Copy to B whichever Smaller
        if (A[i] <= A[j]) B[k++] = A[i++]; // copy from left
        else B[k++] = A[j++];              // copy from right
    }
    // Copy any leftovers from subarrays to B
    while (i <= mid) B[k++] = A[i++];
    while (j <= high) B[k++] = A[j++];
    // copy B back to A
    for (i = low, k = 0; i <= high; i++, k++) A[i] = B[k];
    delete[] B;
}

/* -----------------*/
/* Helper Functions */
/* -----------------*/

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArray(int A[], int size) {
    for (int i = 0; i < size; i++)
        cout << A[i] << " ";
    cout << endl;
}

void copyArr(int source[], int destination[], int len) {
    for (int i = 0; i < len; i++) {
        destination[i] = source[i];
    }
}

void testSort(int A[], int len, const string &sortName) {
    cout << "Unsorted Array: ";
    printArray(A, len);

    if (sortName == "Selection") {
        selectionSort(A, len);
    } else if (sortName == "Bubble") {
        bubbleSort(A, len);
    } else if (sortName == "Insertion") {
        insertionSort(A, len);
    } else if (sortName == "Quick") {
        quickSort(A, len);
    } else if (sortName == "Merge") {
        mergeSort(A, len);
    } else {
        cout << "Wrong Sorting Input -> " << sortName << endl;
    }

    cout << "Sorted Array:   ";
    printArray(A, len);
    cout << endl;
}

void runTestCases() {
    int a[1] = {8};
    int aLen = 1;
    int aCopy[1]; // Case: 1 Num
    
    int b[] = {12, 10, 19, 9, 7, 8, 20, 1, 11, 2, 15, 14, 17, 5, 4, 3, 13, 18, 6, 16};
    int bLen = 20;
    int bCopy[20]; // Case: 20 Num

    int c[] = {5, 9, 1, 9, 5, 5, 1, 9, 1, 5};
    int cLen = 10;
    int cCopy[10]; // Case: Interveaving

    int d[] = {10, -10, 5, 0, 5, -5, 9, -9, 10, -10};
    int dLen = 10;
    int dCopy[10]; // Case: Negatives

    int e[] = {0, 0, 0};
    int eLen = 3;
    int eCopy[3];
    int max = INT_MAX;
    int min = INT_MIN;
    e[0] = max;
    e[2] = min; // Case: Max & Min
    
    cout << "====={ Testing Selection Sort }=====" << endl;
    copyArr(a, aCopy, 1);
    testSort(aCopy, aLen, "Selection");
    copyArr(b, bCopy, 20);
    testSort(bCopy, bLen, "Selection");
    copyArr(c, cCopy, 10);
    testSort(cCopy, cLen, "Selection");
    copyArr(d, dCopy, 10);
    testSort(dCopy, dLen, "Selection");
    copyArr(e, eCopy, 3);
    testSort(eCopy, eLen, "Selection");
    
    cout << "\n====={ Testing Bubble Sort }=====" << endl;
    copyArr(a, aCopy, 1);
    testSort(aCopy, aLen, "Bubble");
    copyArr(b, bCopy, 20); 
    testSort(bCopy, bLen, "Bubble");
    copyArr(c, cCopy, 10); 
    testSort(cCopy, cLen, "Bubble");
    copyArr(d, dCopy, 10); 
    testSort(dCopy, dLen, "Bubble");
    copyArr(e, eCopy, 3); 
    testSort(eCopy, eLen, "Bubble");

    cout << "\n====={ Testing Insertion Sort }=====" << endl;
    copyArr(a, aCopy, 1);
    testSort(aCopy, aLen, "Insertion");
    copyArr(b, bCopy, 20); 
    testSort(bCopy, bLen, "Insertion");
    copyArr(c, cCopy, 10); 
    testSort(cCopy, cLen, "Insertion");
    copyArr(d, dCopy, 10); 
    testSort(dCopy, dLen, "Insertion");
    copyArr(e, eCopy, 3); 
    testSort(eCopy, eLen, "Insertion");

    cout << "\n====={ Testing Quick Sort }=====" << endl;
    copyArr(a, aCopy, 1);
    testSort(aCopy, aLen, "Quick");
    copyArr(b, bCopy, 20); 
    testSort(bCopy, bLen, "Quick");
    copyArr(c, cCopy, 10); 
    testSort(cCopy, cLen, "Quick");
    copyArr(d, dCopy, 10); 
    testSort(dCopy, dLen, "Quick");
    copyArr(e, eCopy, 3); 
    testSort(eCopy, eLen, "Quick");

    cout << "\n====={ Testing Merge Sort }=====" << endl;
    copyArr(a, aCopy, 1);
    testSort(aCopy, aLen, "Merge");
    copyArr(b, bCopy, 20); 
    testSort(bCopy, bLen, "Merge");
    copyArr(c, cCopy, 10); 
    testSort(cCopy, cLen, "Merge");
    copyArr(d, dCopy, 10); 
    testSort(dCopy, dLen, "Merge");
    copyArr(e, eCopy, 3); 
    testSort(eCopy, eLen, "Merge");
}

int main() {
    //runtestCases(); // <-- Runs all my test Cases

    const int MAX_SIZE = 100;
    int testArr[MAX_SIZE];
    int testArrCopy[MAX_SIZE];
    int len = 0;

    // User Input Array
    string userArr = "";
    cout << "Enter Array:    ";
    getline(cin, userArr);
    cout << endl;

    // Convert UserArr to TestArr
    int buildNum = 0;
    bool numStart = false;
    bool isNegative = false;
    for (char c : userArr) {
        if (c == '-') { // if c is negative and Num hasn't start -> mark as negative
            if (!numStart) {
                isNegative = true;
            }
        } else if (c >= '0' && c <= '9') {
            numStart = true;
            buildNum = (buildNum * 10) + (c - '0'); // builds number
        } else {
            if (numStart == true && len < MAX_SIZE) {
                testArr[len++] = isNegative ? -buildNum : buildNum; // add num to array
                buildNum = 0; // reset flags
                numStart = false;
                isNegative = false;
            }
        }
    }
    if (numStart == true) { // add last num to array
        testArr[len++] = isNegative ? -buildNum : buildNum;
    }
    if (len == 0) {
        cout << "No Numbers Entered" << endl;
        return 0;
    }

    // Test Sorting Algorithms
    cout << "====={ Selection Sort Test }=====" << endl;
    copyArr(testArr, testArrCopy, len);
    testSort(testArrCopy, len, "Selection");
    cout << "====={ Bubble Sort Test }=====" << endl;
    copyArr(testArr, testArrCopy, len);
    testSort(testArrCopy, len, "Bubble");
    cout << "====={ Insertion Sort Test }=====" << endl;
    copyArr(testArr, testArrCopy, len);
    testSort(testArrCopy, len, "Insertion");
    cout << "====={ Quick Sort Test }=====" << endl;
    copyArr(testArr, testArrCopy, len);
    testSort(testArrCopy, len, "Quick");
    cout << "====={ Merge Sort Test }=====" << endl;
    copyArr(testArr, testArrCopy, len);
    testSort(testArrCopy, len, "Merge");

    return 0;
}