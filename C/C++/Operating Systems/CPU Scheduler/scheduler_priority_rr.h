/**
 * @file scheduler_priority_rr.h
 * @author Owen Man
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */

#ifndef ASSIGN3_SCHEDULER_PRIORITY_RR_H
#define ASSIGN3_SCHEDULER_PRIORITY_RR_H

#include "scheduler.h"
#include <queue>

class SchedulerPriorityRR : public Scheduler {
private:
    std::vector<PCB> process_list; // holds all processes
    std::queue<PCB*> ready_queue;  // queues processes when arrived
    unsigned int current_time = 0; // simulated time
    double total_turnaround_time = 0; // when Pi finished from start
    double total_waiting_time = 0;    // time Pi waits in ready_queue
    unsigned int time_quantum; // time Pi allowed to run before switching

public:
    /**
     * @brief Construct a new SchedulerPriority object
     */
    SchedulerPriorityRR(int time_quantum = 10);

    /**
     * @brief Destroy the SchedulerPriority object
     */
    ~SchedulerPriorityRR() override;

    /**
     * @brief This function is called once before the simulation starts.
     *        It is used to initialize the scheduler.
     * @param process_list The list of processes in the simulation.
     */
    void init(std::vector<PCB>& process_list) override;

    /**
     * @brief This function is called once after the simulation ends.
     *        It is used to print out the results of the simulation.
     */
    void print_results() override;

    /**
     * @brief This function simulates the scheduling of processes in the ready queue.
     *        It stops when all processes are finished.
     */
    void simulate() override;

};

#endif //ASSIGN3_SCHEDULER_PRIORITY_RR_H
