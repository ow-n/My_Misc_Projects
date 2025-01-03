/**
 * @file scheduler_fcfs.cpp
 * @author Owen Man
 * @brief This Scheduler class implements the FCSF scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_fcfs.h"
#include <iostream>

SchedulerFCFS::SchedulerFCFS() {
}

SchedulerFCFS::~SchedulerFCFS() {
}

void SchedulerFCFS::init(std::vector<PCB>& process_list) {
    this->process_list = process_list; // copy process_list

    // Selection Sort Original Process_List on Arrival Time and ID
    for (size_t i = 0; i < this->process_list.size() - 1; i++) { // iterate through process_list
        size_t min_idx = i; // min ele in unsorted array
        for (size_t j = i + 1; j < this->process_list.size(); j++) { // iterate through unsorted array
            if (this->process_list[j].arrival_time < this->process_list[min_idx].arrival_time) { // sort by arrival_time
                min_idx = j; // find min ele
            } else if (this->process_list[j].arrival_time == this->process_list[min_idx].arrival_time) { // if arrival_time is same
                if (this->process_list[j].id < this->process_list[min_idx].id) { // sort by id
                    min_idx = j; // find min ele
                }
            }
        }
        if (min_idx != i) { // if min ele is not the first ele
            PCB temp = this->process_list[i]; // swap
            this->process_list[i] = this->process_list[min_idx];
            this->process_list[min_idx] = temp;
        }
    }

    for (PCB& process : this->process_list) { // push processes into ready_queue
        ready_queue.push(&process);
    }
}

void SchedulerFCFS::print_results() {
    // Selection Sort Process List on Arrival Time
    for (size_t i = 0; i < this->process_list.size() - 1; i++) { // iterate through process_list
        size_t min_idx = i; // min ele in unsorted array
        for (size_t j = i + 1; j < this->process_list.size(); j++) { // iterate through unsorted array
            if (this->process_list[j].id < this->process_list[min_idx].id) { // sort by id
                min_idx = j; // find min ele
            }
        }
        if (min_idx != i) { // if min ele is not the first ele
            PCB temp = this->process_list[i]; // swap
            this->process_list[i] = this->process_list[min_idx];
            this->process_list[min_idx] = temp;
        }
    }

    for (const PCB& process : process_list) {
        cout << process.name << " turn-around time = " << process.turnaround_time
                  << ", waiting time = " << process.waiting_time << endl;
    }
    cout << "Average turn-around time = " << total_turnaround_time / process_list.size()
              << ", Average waiting time = " << total_waiting_time / process_list.size() << endl;
}

void SchedulerFCFS::simulate() {
    while (!ready_queue.empty()) {
        PCB* process = ready_queue.front();
        ready_queue.pop();

        cout << "Running Process " << process->name << " for " << process->burst_time << " time units" << endl;
        current_time += process->burst_time;  // increment time
        // Calculate Turnaround & Waiting Time
        process->turnaround_time = current_time - process->arrival_time;
        process->waiting_time = process->turnaround_time - process->original_burst_time;
        // Update Totals
        total_turnaround_time += process->turnaround_time;
        total_waiting_time += process->waiting_time;
    }
}
