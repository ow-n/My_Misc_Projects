/**
 * @file scheduler_priority_rr.cpp
 * @author Owen Man
 * @brief This Scheduler class implements the Priority RR scheduling algorithm.
 * @version 0.1
 */

#include "scheduler_priority_rr.h"
#include <iostream>

SchedulerPriorityRR::SchedulerPriorityRR(int time_quantum) : time_quantum(time_quantum) {
}

SchedulerPriorityRR::~SchedulerPriorityRR() {
}

void SchedulerPriorityRR::init(std::vector<PCB>& process_list) {
    this->process_list = process_list; // copy process_list

    // Selection Sort Original Process_List on Priority and ID
    for (size_t i = 0; i < this->process_list.size() - 1; i++) { // iterate through process_list
        size_t min_idx = i; // min ele in unsorted array
        for (size_t j = i + 1; j < this->process_list.size(); j++) { // iterate through unsorted array
            if (this->process_list[j].priority > this->process_list[min_idx].priority) { // sort by burst_time
                min_idx = j; // find min ele
            } else if (this->process_list[j].priority == this->process_list[min_idx].priority) { // if burst_time is same
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

void SchedulerPriorityRR::print_results() {
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

void SchedulerPriorityRR::simulate() {
    std::queue<PCB*> priority_queue; // separate queue for grouping priority Pis
    unsigned int current_priority = 0; // current priority being processed

    while (!ready_queue.empty() || !priority_queue.empty()) { // make sure both queue's empty
        // If PriorityQueue empty, fill with Pi from ReadyQueue
        if (priority_queue.empty()) {
            current_priority = ready_queue.front()->priority; // update priority level
            while (!ready_queue.empty() && ready_queue.front()->priority == current_priority) {
                PCB* process = ready_queue.front();
                ready_queue.pop();
                priority_queue.push(process);
            }
        }

        // Get Process from PriorityQueue
        PCB* process = priority_queue.front();
        priority_queue.pop();

        // Run Process
        if (priority_queue.empty()) { // last processor in PriorityQueue
            cout << "Running Process " << process->name << " for " << process->burst_time << " time units" << endl;
            current_time += process->burst_time;  // increment time
            // Calculate Turnaround & Waiting Time
            process->turnaround_time = current_time - process->arrival_time;
            process->waiting_time = process->turnaround_time - process->original_burst_time;
            // Update Totals
            total_turnaround_time += process->turnaround_time;
            total_waiting_time += process->waiting_time;
        } else if (process->burst_time > time_quantum) { // Pi too long -> ReQueue
            cout << "Running Process " << process->name << " for " << time_quantum << " time units" << endl;
            process->burst_time -= time_quantum; // decrease burst_time by time_quantum
            current_time += time_quantum;        // increment time
            priority_queue.push(process);        // Requeue Process
        } else { // Process Finished
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
}
