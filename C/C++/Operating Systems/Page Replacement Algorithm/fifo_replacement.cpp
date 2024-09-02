/**
 * @file fifo_replacement.cpp
 * @author Owen Man
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */

#include "fifo_replacement.h"

// Constructor
FIFOReplacement::FIFOReplacement(int num_pages, int num_frames) : Replacement(num_pages, num_frames) {
}

// Destructor
FIFOReplacement::~FIFOReplacement() {
}

// Access an invalid page, but free frames are available
void FIFOReplacement::load_page(int page_num) {
    PageEntry* pageEntry = &this->page_table[page_num]; // get page entry
    pageEntry->frame_num = this->fifoQueue.size();      // set frame number
    pageEntry->valid = true;        // set page as valid
    this->fifoQueue.push(page_num); // push page number to queue
    this->num_frames--;             // decrement number of frames
}

// Access an invalid page and no free frames are available
int FIFOReplacement::replace_page(int page_num) {
    int victim_page = this->fifoQueue.front(); // get first page in queue
    PageEntry* oldPageEntry = &this->page_table[victim_page]; // get page entry
    this->fifoQueue.pop();       // remove first page in queue
    oldPageEntry->valid = false; // set page as invalid

    PageEntry* newPageEntry = &this->page_table[page_num];  // get page entry
    newPageEntry->frame_num = oldPageEntry->frame_num;      // set frame number 
    newPageEntry->valid = true;     // set page as valid
    this->fifoQueue.push(page_num); // push page number to queue
    return victim_page;             // return victim page
}
