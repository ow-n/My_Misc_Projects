/**
 * @file lru_replacement.cpp
 * @author Owen Man
 * @brief A class implementing the LRU page replacement algorithms
 * @version 0.1
 */

#include "lru_replacement.h"

// Constructor
LRUReplacement::LRUReplacement(int num_pages, int num_frames) : Replacement(num_pages, num_frames) {
}

// Destructor
LRUReplacement::~LRUReplacement() {
}

// Accesss a page alreay in physical memory
void LRUReplacement::touch_page(int page_num) {
    // Move accessed page to front of list
    auto page = pageMap.find(page_num);
    if (page != pageMap.end()) {    // if page is in memory
        memory.erase(page->second);         // remove page
        memory.push_front(page_num);        // add page to front
        pageMap[page_num] = memory.begin(); // update page position
    }
}

// Access an invalid page, but free frames are available
void LRUReplacement::load_page(int page_num) {
    page_table[page_num].frame_num = memory.size(); // set frame number
    page_table[page_num].valid = true;  // set page as valid
    memory.push_front(page_num);        // add page to front
    pageMap[page_num] = memory.begin(); // update page position
    num_frames--;   // decrement number of frames
}

// Access an invalid page and no free frames are available
int LRUReplacement::replace_page(int page_num) {
    int victim = memory.back(); // get least recently used page
    int frame_num = page_table[victim].frame_num; // get frame number

    memory.pop_back();                  // remove page from memory
    pageMap.erase(victim);              // remove page from map
    memory.push_front(page_num);        // add new page to front
    pageMap[page_num] = memory.begin(); // update page position

    page_table[page_num].frame_num = frame_num; // set frame number
    page_table[page_num].valid = true;          // set page as valid
    page_table[victim].valid = false;           // set victim page as invalid

    return 0;
}
