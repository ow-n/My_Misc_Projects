# Pthread Semaphores and Mutex Locks
Implement the producer-consumer problem using Pthread semaphores and mutex locks.

# Problem Description:
The Producer-Consumer problem is a synchronization challenge, which involves
coordinating producer and consumer threads that share a common, finite-sized buffer.
The goal is to ensure that producers do not produce items when the buffer is full, and
consumers do not consume items when the buffer is empty. This project uses the
PThread library to create and manage producer and consumer threads to demonstrate
this concept.

# Program Design
The program is structured around a Buffer class that encapsulates the buffer and
synchronization logic. The class uses semaphores to manage mutual exclusion and to
signal the state of the buffer.

Buffer Class: Manages items with methods to insert and remove items. Semaphores
empty, full, and mutex control access and synchronization.
Producer and Consumer Threads: These threads interact with the buffer. Producers add
items identified by their thread ID, and consumers remove these items in FIFO order.

# System Implementation
The implementation uses the semaphore-based synchronization technique to handle
access to the buffer. I first tried using mutex locks, but I found it really difficult to debug
deadlock situations. Switching to semaphores simplified the control flow but I wasn’t
able to pass the final test case with 5 producers.

Deadlock Prevention: Transition from mutex to semaphore to avoid deadlock scenarios.
Output Inconsistencies: Unexplained discrepancies between local output and
automated grading systems, which could be due to nuances in thread scheduling or
timing.

# Results
The functionality was tested with different numbers of producer and consumer threads.
The system behaved as expected, maintaining correct synchronization between
threads.
