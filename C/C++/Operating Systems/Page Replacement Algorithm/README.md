# Page Replacement Algorithm
Implement a page table and analyze different page replacement algorithms.

# Problem Description:
Page replacement is used to manage virtual memory in operating systems. Virtual memory extends our available physical memory by storing parts of the data on disk in a space like a paging file. However, for a program to execute, it’s instructions and data must be in the physical memory (RAM). If it’s not in the physical memory, it causes a page fault, forcing the operating system to decide which existing page to swap out to get the needed pages.

The decision-making involved in how the operating systems switched out pages depends on the algorithms used. That is why in this assignment, we are implementing a First-In-First-Out (FIFO), Last-In-First-Out (LIFO) and Least Recently Used (LRU) algorithm to evaluate their performances.


# Program Design
**PageTable**: Manages a virtual address space divided into pages. Each page has a unique frame number when loaded into physical memory, alongside valid and dirty bits to track its state. 
    • A vector of ‘PageEntry’ was used to allow indexing access to the pages, so that it’s efficient to retrieve and update the status during load operations.

**Replacement**: The parent class of the three algorithms. This class implements the access, load, and replace functions needed by the other algorithms.

    • FIFO manages pages in the order they were loaded.
        ◦ Uses a Queue since it allows addition to the back and removal from the front
    • LIFO discards the most recently added page first.
        ◦ Uses a stack as it allows pages to be added and removed from the top.
    • LRU prioritizes pages based on their access frequency and recency.
        ◦ Uses a doubly linked list (list) to track the recency of page accesses
        ◦ Uses a hash map (unordered_map) for quick access to list nodes
        ◦ These data structures were used as the list allows fast front and back operations and the map allows quick manipulation of the lists as pages are accessed.

# System Implementation
For the FIFO algorithm, I imported <queue>, which allowed pages to be queue and dequeued. Similarly, for the LIFO algorithm, I imported <stack>, which allowed me to push and pop the pages. In the LRU algorithm, I imported <list> and <unordered_map>. This algorithm initially ran correctly initially but I began to run into issues when trying to optimize it to be sub-1 second. I tried implementing it via heaps with no success. With continual trial and cleaning up the implementation in the touch, load, and replace pages functions, I still couldn’t get it to work anymore.

I realized my replacement access page function was messily written. After cleaning that function up, I got the LRU algorithm to sub 1 second but that also broke my FIFO and LIFO algorithms. Then I finally got everything to work realizing I was building my data structures incorrectly.


# Results
Testing was conducted using two sets of data: small_refs.txt and large_refs.txt. Each test aimed to evaluate the algorithms’ performance across varying page sizes and memory configurations, from 256 bytes to 8192 bytes for page sizes and from 4 MB to 64 MB for physical memory sizes.

Each of the algorithms processed 2 million references.
FIFO produced 141,266 page faults and 108,498 replacements, showing moderate efficiency.
LIFO produced 444,862 page faults and 412,094 replacements, showing worse performance.
LRU, expectedly, outperformed others in scenarios by producing 132,844 page faults and 100,076 replacements.
