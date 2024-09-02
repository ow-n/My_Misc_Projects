# PCB Data Structure
There are two test programs to test the correctness and performance of your implementation. A makefile
is provided for building the executables `test1` and `test2`. To build the executables `test1` and `test2`, type `make` at the command line. Then run each test and confirm the outputs match with the "test1_out.txt" and "test2_out.txt" files. 
```
$ make
$ ./test1
$ ./test2
```

# Problem Statement:
The goal of this programming assignment was to create a program that used a
priority data structure in order to add and remove PCBs from a list efficiently.
This data structure will be the test on how efficiently it can add and remove these
PCBs to the data structure implemented. The first test was used to add and
remove PCBs to my data structure, to ensure that the data structure could hold
them in the correct priority order. The second test was based on how efficiently I
could add 500 PCBs to a list and then efficiently try to add or remove a PCB
1,000,000 times. The goal is to have a time that is less than .1 seconds for the
highest efficiency, which is only achievable by a certain few data structures.

# Design & System Implementation:
I originally created nodes and implemented a linked list for my ready queue. After
running the test cases and seeing how slow it was, I decided to revise my decision
to find a more optimal solution.

I decided to go with a priority max heap due to the insert and remove functions
both taking only O(logn) time complexity. This is the fastest data structure when it
comes to adding and removing values with priorities, therefore during the second
test, I was able to efficiently add and remove all of the PCBs to my ready queue.
PCB** heap; //an array used for a heap of PCBs

The ReadyQueue was implemented using a dynamic array to represent the binary
heap. It organized the PCBs and ensured that the highest priority process was
always at the root.
To originally store all of the PCBs that were waiting to be added, a simple vector
was used which was implemented by the following
vector<PCB * table>
This will then hold all of the PCBs that will be used

# Results:
My expected time complexities for the main functions are:
Insertion / addPCB: O(log n) due to potentially needing to restore the heap
structure from the root.

- Removal / removePCB: O(log n) due to needing to restructure the heap downwards
from the root after removing the root elements.
- Heap Maintenance / bubble up / bubble down: O(log n) due to these functions
needing to traverse the height of the heap.

Using my max-heap data structure, I was able to get a time of .15 seconds with 1
million lines of code. Although this varied, it was still a very fast solution
compared to the linked list.
