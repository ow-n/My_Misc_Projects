/**
 * @file lifo_replacement.cpp
 * @author Owen Man
 * @brief A class implementing the Last in First Out (LIFO) page replacement algorithms
 * @version 0.1
 */

#include "lifo_replacement.h"

// Constructor
LIFOReplacement::LIFOReplacement(int num_pages, int num_frames) : Replacement(num_pages, num_frames) {
}

// Destructor
LIFOReplacement::~LIFOReplacement() {
}

// Access an invalid page, but free frames are available
void LIFOReplacement::load_page(int page_num) {
    PageEntry* pageEntry = &this->page_table[page_num]; // get page entry
    pageEntry->frame_num = this->lifoStack.size();      // set frame number
    pageEntry->valid = true;        // set page as valid
    this->lifoStack.push(page_num); // push page number to stack
    this->num_frames--;             // decrement number of frames
}

// Access an invalid page and no free frames are available
int LIFOReplacement::replace_page(int page_num) {
    int victim_page = this->lifoStack.top(); // get top page in stack
    PageEntry* oldPageEntry = &this->page_table[victim_page]; // get page entry
    this->lifoStack.pop(); // remove top page in stack
    oldPageEntry->valid = false; // set page as invalid

    PageEntry* newPageEntry = &this->page_table[page_num]; // get page entry
    newPageEntry->frame_num = oldPageEntry->frame_num; // set frame number
    newPageEntry->valid = true;     // set page as valid
    this->lifoStack.push(page_num); // push page number to stack
    return victim_page;             // return victim page
}
