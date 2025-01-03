/**
 * @file replacement.cpp
 * @author Owen Man
 * @brief A base class for different page replacement algorithms.
 * @version 0.1
 */

#include <iostream>
#include "replacement.h"

// Constructor
Replacement::Replacement(int num_pages, int num_frames) : page_table(num_pages) {
    this->num_frames = num_frames;
    this->num_pages = num_pages;
    this->frame_available = std::vector<bool>(num_frames, true); // init all frames as available
}

// Destructor
Replacement::~Replacement() {
}

// Simulate a single page access 
// @return true if it's a page fault
bool Replacement::access_page(int page_num, bool is_write) {
    // If the page is valid, it calls the touch_page function. 
    if (this->page_table[page_num].valid) {
        touch_page(page_num);
        total_references++;
    }
    // If the page is not valid but free frames are available, it calls the load_page function.
    else if (!this->page_table[page_num].valid && this->num_frames > 0) {
        load_page(page_num);
        total_references++;
        total_page_faults++;
        return true;
    }
    // If the page is not valid and there is no free frame, it calls the replace_page function.
    else if (!this->page_table[page_num].valid && this->num_frames == 0) {
        replace_page(page_num);
        total_references++;
        total_page_faults++;
        total_page_replacements++;
        return true;
    }
    return false;
}

// Print out statistics of simulation
void Replacement::print_statistics() const {
    std::cout << "Number of references: \t\t" << total_references << std::endl;
    std::cout << "Number of page faults: \t\t" << total_page_faults << std::endl;
    std::cout << "Number of page replacements: \t" << total_page_replacements << std::endl;
}

// Get a free frame
int Replacement::getFreeFrame() {
    for (size_t i = 0; i < frame_available.size(); ++i) {
        if (frame_available[i]) {
            frame_available[i] = false;
            return static_cast<int>(i);
        }
    }
    return -1; // no free frame found
}

// Set a frame as free
void Replacement::setFreeFrame(int frame_num) {
    if (frame_num >= 0 && static_cast<size_t>(frame_num) < frame_available.size()) {
        frame_available[frame_num] = true;
    }
}
