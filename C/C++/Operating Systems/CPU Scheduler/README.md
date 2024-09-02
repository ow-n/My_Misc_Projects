# Scheduling Algorithms
Implement basic scheduling algorithms.

# Problem Description:
This assignment solves the problem of deciding which process the CPU should run. This program implements several scheduling algorithms and compares the efficiency of each algorithm. It takes a sample data set of processes and the program lets us see the average turnaround time and waiting time for each algorithm.

# Program Design
There is a pcb.h file that contains all the information of a process. For each algorithm, there is a scheduler header, cpp file, and driver. The driver creates an instance of the scheduler and then initializes it with the schedule.txt. 

I’ve designed the program in a way that each algorithm initially copies the process_list, and then loads the processes into another queue data type called ready_queue. I initially designed it that way intending to easily print out the same ID order of the processes, but this didn’t work out.

I implemented a selection sort in the initialization of the scheduler to push the pointers of processes into the ready_queue in the order of arrival time. I realized this changed the order of the process_list so I needed to sort them once again in the print_results function to print it out in the order of IDs.

I used a selection sort to keep the implementation simple and to explicitly specify the sorting intention, as selection sort is unstable and needs to be sorted in two ways. A more efficient approach would be using a priority heap to queue processes and maybe using a map for printing the process by ID number.

# System Implementation
I was struggling to find the best approach to handling the processes. I spent a long time with the implementation of handling the processes in a vector and sorting them, which worked from FCFS to Priority. Then when I got to RR scheduling, I realized I should have used an actual queue and should have been pushing and popping the processes from there. That’s when I redesigned the implementation from vectors to queues. 

Since the example output printed each process’s turnaround time and wait time, I decided to add those variables to the PCB. This made the implementation simpler instead of calculating those values and total values in the print section. 

For the priority round-robin, I found that I needed a second queue to queue the processes of the same priority. This is when I realized my implementation may not be a fully accurate simulation as the second queue is supposedly the actual ready queue. I’m unsure what is the standard way of implementing this. The other way to keep this in a single queue is if I implement a priority heap instead, I could have it sort itself to its priority so I don’t need the second queue.

# Results
FCFS: Avg Turnaround Time: 94.375, Avg Waiting Time: 73.125
SJF: Avg Turnaround Time: 92.5, Avg Waiting Time: 61.5
Priority: Avg Turnaround Time: 96.25, Avg Waiting Time: 75
RR: Avg Turnaround Time: 143.125, Avg Waiting Time: 121.875
Priority RR: Avg Turnaround Time: 106.75, Avg Waiting Time: 85.5

These were the results of the simple test case used in the program. SJF proved most efficient in terms of turnaround time and waiting time. These results are in line with what we expect, but remember that it cannot be implemented at the level of CPU scheduling since there’s no way of knowing the length of the next CPU burst. We could only tell since all the processes were known to us from the beginning
