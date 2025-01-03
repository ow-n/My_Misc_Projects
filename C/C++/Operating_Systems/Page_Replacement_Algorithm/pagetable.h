/**
 * @file pagetable.h
 * @author Owen Man
 * @brief This class represents a traditional pagetable data structure.
 * @version 0.1
 */

#pragma once

#include <vector>
using namespace std;

// A page table entry
/**
 * @brief A page table entry. This class is used to represent a page table entry.
 * @details Each page has one entry in the page table. It contains the following fields:
 * - frame number
 * - valid bit
 */
class PageEntry {
public:
	int frame_num; // Physical frame number for a given page
	bool valid = false; // valid bit represents whether a page is in the physical memory
    bool dirty = false; // dirty bit represents whether a page is changed
};

/**
 * @brief A page table is like an array of page entries.
 * The size of the page table should equal to the number of pages in logical memory
 */
class PageTable {
private:
    vector<PageEntry> pages; // A page table is like an array of page entries.

public:
    PageTable(int num_pages); // Constructor
    ~PageTable(); // Destructor

    /**
     * @brief Access a page in the page table.
     * @param i
     * @return
     */
    PageEntry& operator [] (int i) {
        return pages[i];
    }
};
