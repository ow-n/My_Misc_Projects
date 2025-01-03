/**
 * @file fifo_replacement.h
 * @author Owen Man
 * @brief A class implementing the FIFO page replacement algorithms
 * @version 0.1
 */

#pragma once

#include "replacement.h"
#include <queue> // for tracking order of pages

/**
 * @brief A class to simulate FIFO page replacement algorithm.
 */
class FIFOReplacement : public Replacement {
private:
    std::queue<int> fifoQueue;  // FIFO queue to track order of pages

public:
    /**
     * @brief Constructor
     * @param num_pages Total number of available free frames.
     * @param num_frames Total number of free frames.
     */
    FIFOReplacement(int num_pages, int num_frames);

    /**
    * @brief Destructor
    */
    virtual ~FIFOReplacement();

    /**
     * @brief Access an invalid page, but free frames are available.
     * Assign the page to an available  frame, not replacement needed
     * @param page_num The logical page number.
     */
    virtual void load_page(int page_num);

    /**
     * @brief Access an invalid page, and there is no free frame.
     * Replace the page with the page that has been in memory the longest.
     * @param page_num The logical page number.
     * @return Selected victim page #
     */
    virtual int replace_page(int page_num);

};
