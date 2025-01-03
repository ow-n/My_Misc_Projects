/**
 * @file pcb.h
 * @author Owen Man
 * @brief This is the header file for the PCB class, a process control block.
 * @version 0.1
 */

#pragma once
#include <iostream>
#include <string>
using namespace std;

/**
 * @brief A process control block (PCB) Process control block(PCB) is a data structure representing a process in the system.
 *       It contains the following fields:
 *       - process ID (PID)
 *       - process name
 *       - burst time
 *       - original burst time
 *       - priority
 *       - turnaround time
 *       - arrival time
 */
class PCB {
public:
    // Name of the process
    string name;
    // The unique process ID
    unsigned int id;
    // The priority of a process. Larger number represents higher priority
    unsigned int priority;
    // The CPU burst time of the process
    unsigned int burst_time;
    // The CPU burst time of the process
    unsigned int original_burst_time;
    // The arrival time of the process
    unsigned int arrival_time;
    // The turnaround time of the process
    unsigned int turnaround_time;
    // The waiting time of the process
    unsigned int waiting_time;

    /**
     * @brief Construct a new PCB object
     * @param id: each process has a unique ID
     * @param priority: the priority of the process in the range 1-50. Larger number represents higher priority
     * @param state the state of the process.
     */
    PCB(string name, unsigned int id = 0, unsigned int priority = 1, unsigned int burst_time = 0) {
        this->id = id;
        this->name = name;
        this->priority = priority;
        this->burst_time = burst_time;
        this->original_burst_time = burst_time; // for round-robin wait calculation
        this->arrival_time = 0;
        this->turnaround_time = 0;
        this->waiting_time = 0;
    }

    /**
     * @brief Destroy the PCB object.
     *
     */
    ~PCB() {}

    /**
     * @brief Print the PCB object.
     */
    void print() {
        cout << "Process " << id << ": " << name << " has priority " << priority << " and burst time "
             << burst_time << endl;
    }
};
