/**
 * @file pagetable.cpp
 * @author Owen Man
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */

#include "pagetable.h"

// Constructor
PageTable::PageTable(int num_pages) {
    pages.resize(num_pages); // resize vector to num_pages

    // Initialize all Pages as initially Invalid
    for (auto& page : pages) {
        page.frame_num = -1;    // -1 == no frame
        page.valid = false;     // page not in physical memory
        page.dirty = false;     // page not changed (dirty = changed, clean = not changed)
    }
}

// Destructor
PageTable::~PageTable() {
    pages.clear(); // clear vector
}
