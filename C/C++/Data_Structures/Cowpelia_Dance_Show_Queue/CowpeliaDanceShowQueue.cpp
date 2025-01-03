/* Cowpelia Dance Show
 * N number of Cows. K spaces on Stage.
 * Each Cow has individual dance duration.
 * Cows are in a Queue, and Enter Stage as soon as Space is Available
 * This program calculates when the last cow finishes dancing.
 * 
 * Dance Duration Range: 1...100,000
 * Not Tested for Invalid Inputs
 *     My Assumptions:
 *      - K >= 0
 * */

#include <iostream>
using namespace std;

struct Node {
    int duration;
    Node* next;
    Node(int d) : duration(d), next(nullptr) {}
};

class CowQueue {
private:
    Node* front;
    Node* rear;
    int size;

public:
    CowQueue() : front(nullptr), rear(nullptr), size(0) {}

    ~CowQueue() {
        while (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void enqueue(int duration) {
        Node* newNode = new Node(duration);
        if (rear == nullptr) { // if queue is empty, front+rear = new node
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    int dequeue() {
        if (front == nullptr) return 0; // Case: Empty Queue
        int dequeuedDuration = front->duration;
        Node* temp = front;
        front = front->next;

        if (front == nullptr) { // Case: Emptied Queue -> update rear
            rear = nullptr;
        }
        delete temp;
        size--;
        return dequeuedDuration;
    }

    int getHead() {
        if (front == nullptr) return 0; // Case: Empty Queue
        return front->duration;
    }

    int getSize() {
        return size;
    }

    bool isEmpty() {
        return size == 0;
    }

    /* Calculate Cowpelia Dance Show Duration */
    int calculateTime(int K) {
        if (K == 0) return 0; // Case: No Stage == No Cowpelia
        
        int* stage = new int[K]; /// initialize all stage slots to 0
        for (int i = 0; i < K; i++) {
            stage[i] = 0;
        }
        int currentTime = 0, activeCows = 0;

        // Prefill Stage with First K or N Cows
        for (int i = 0; i < K && !isEmpty(); ++i) {
            stage[i] = dequeue();
            activeCows++;
        }

        while (activeCows > 0) {
            int minDuration = INT_MAX;
            // Find Smallest Dance Duration on Stage
            for (int i = 0; i < activeCows; i++) {
                if (stage[i] < minDuration) {
                    minDuration = stage[i];
                }
            }
            currentTime += minDuration;

            // Process Cows to Stage
            for (int i = 0; i < activeCows; i++) {
                stage[i] -= minDuration; // decrease all cow timers by minDuration

                // Once Cow finishes dancing:
                if (stage[i] == 0) {
                    if (!isEmpty()) { // If Queue has Cows
                        stage[i] = dequeue();             // replace with new cow
                    } else {          // If Queue is Empty
                        stage[i] = stage[activeCows - 1]; // replace last stage position with current position
                        activeCows--;
                        i--; // current i now is a new cow, so need to decrement i
                    }
                }
            }
        }
        delete[] stage;
        return currentTime;
    }
};

/* Boundary Test Cases */
void testCaseExample() {
    CowQueue cows;
    cows.enqueue(4);
    cows.enqueue(7);
    cows.enqueue(8);
    cows.enqueue(6);
    cows.enqueue(4);                // N = 5, num cows
    int T = cows.calculateTime(4);  // K = 4, stage size
    cout << "[Assignment] \t\t\tCowpelia ends at T = " << T << ". Expected T = 8." << endl;
}

void testCase1Cow() {
    CowQueue cows;
    cows.enqueue(1);                // N = 1
    int T = cows.calculateTime(1);  // K = 1
    cout << "[1 Cow] \t\t\tCowpelia ends at T = " << T << ". Expected T = 1." << endl;
}

void testCaseNoStage() {
    CowQueue cows;
    cows.enqueue(1);                // N = 1
    int T = cows.calculateTime(0);  // K = 0
    cout << "[No Stage] \t\t\tCowpelia ends at T = " << T << ". Expected T = 0." << endl;
}

void testCaseShyCows() {
    CowQueue cows;
    cows.enqueue(0);
    cows.enqueue(0);
    cows.enqueue(0);
    cows.enqueue(0);                // N = 4
    int T = cows.calculateTime(2);  // K = 2
    cout << "[Shy Cows] \t\t\tCowpelia ends at T = " << T << ". Expected T = 0." << endl;
}

void testCaseNLessThanK() { // Less Cows than Spaces
    CowQueue cows;
    cows.enqueue(2);
    cows.enqueue(3);                // N = 2
    int T = cows.calculateTime(4);  // K = 4
    cout << "[Less Cows than Spaces] \tCowpelia ends at time T = " << T << ". Expected T = 3."  << endl;
}

void testCase2CowFinTogether() {
    CowQueue cows;
    cows.enqueue(5);
    cows.enqueue(5);
    cows.enqueue(2);
    cows.enqueue(2); // cow(2)'s finish, 5->3, cow(8)'s get added, now: [3,3,8,8]
    cows.enqueue(8);
    cows.enqueue(8);                // N = 6
    int T = cows.calculateTime(4);  // K = 4
    cout << "[2 Cows Finish Together] \tCowpelia ends at T = " << T << ". Expected T = 10." << endl;
}

void testCaseShiftingCows() { // REWORK
    CowQueue cows;
    cows.enqueue(1); // [1,-,-,-,-]
    cows.enqueue(2);
    cows.enqueue(3);
    cows.enqueue(4);
    cows.enqueue(5); // [1,2,3,4,5] -> [0,1,2,3,4] -> [1,2,3,4,-] -> ...
                                    // N = 5
    int T = cows.calculateTime(5);  // K = 5
    cout << "[Shifting Cows] \t\tCowpelia ends at T = " << T << ". Expected T = 5." << endl;

}

void testCaseBoundaryDurations() {
    CowQueue cows;
    cows.enqueue(100000);   // [100 000, -, -]
    cows.enqueue(0);        // [100 000, 0, -]
    cows.enqueue(99999);    // [100 000, 0, 99 999]
    cows.enqueue(99999);    // [100 000, 99 999, 99 999] -> [1, 0, 0]
    cows.enqueue(1);        // [1, 1, 0]
    cows.enqueue(1);        // [1, 1, 1] -> [0, 0, 0]
    cows.enqueue(888);      // [888, 0, 0]
                                    // N = 7
    int T = cows.calculateTime(3);  // K = 3
    cout << "[Boundary Durations] \t\tCowpelia ends at T = " << T << ". Expected = 100888" << endl;
}

void testCaseBoundarySim() {
    CowQueue cows;
    cows.enqueue(10);       // [10, -, -]
    cows.enqueue(0);        // [10, 0, -]
    cows.enqueue(9);        // [10, 0, 9]
    cows.enqueue(9);        // [10, 9, 9] -> [1, 0, 0]  (+9)
    cows.enqueue(1);        // [1, 1, 0]
    cows.enqueue(1);        // [1, 1, 1] -> [0, 0, 0]   (+1)
    cows.enqueue(40);       // [40, 0, 0]               (+40)
                                    // N = 7
    int T = cows.calculateTime(3);  // K = 3
    cout << "[Boundary Sim Durations 1] \tCowpelia ends at T = " << T << ". Expected = 50" << endl;
}

void testCaseBoundarySim2() {
    CowQueue cows;
    cows.enqueue(10);       // [10, -, -]
    cows.enqueue(9);        // [10, 9, -]
    cows.enqueue(0);        // [10, 9, 0] SWITCHED, NOT A SHIFTING ISSUE?
    cows.enqueue(9);        // [10, 9, 9] -> [1, 0, 0]  (+9)
    cows.enqueue(1);        // [1, 1, 0]
    cows.enqueue(1);        // [1, 1, 1] -> [0, 0, 0]   (+1)
    cows.enqueue(40);       // [40, 0, 0]               (+40)
                                    // N = 7
    int T = cows.calculateTime(3);  // K = 3
    cout << "[Boundary Sim Durations 2] \tCowpelia ends at T = " << T << ". Expected = 50" << endl;
}

int main() {
    int N, K;
    cin >> N >> K;

    CowQueue cows; // Queue N Cows:
    for (int i = 0; i < N; i++) {
        int duration;
        cin >> duration;
        cows.enqueue(duration);
    }
    
    int T = cows.calculateTime(K);
    cout << "Cowpelia ends at T = " << T << endl;
    
    /*
    testCaseExample();
    testCase1Cow();
    testCaseNoStage();
    testCaseShyCows();

    testCase2CowFinTogether();
    testCaseShiftingCows();

    testCaseBoundaryDurations();
    testCaseBoundarySim();
    testCaseBoundarySim2();
    */
    return 0;
}
