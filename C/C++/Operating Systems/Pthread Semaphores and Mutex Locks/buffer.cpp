/**
 * @file buffer.cpp
 * @author Owen Man
 * @brief Implementation file for the buffer class
 * @version 0.1
 */

#include "buffer.h"
#include <cstring> // for memset

/**
 * @brief Construct a new Buffer object
 * @param size the size of the buffer
 */
Buffer::Buffer(int size) : in(0), out(0) {
    memset(buffer, 0, sizeof(buffer)); // initialize all buffer elements to 0
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE); // initially buffer is empty
    sem_init(&full, 0, 0); // initially no items in buffer
}

/**
 * @brief Destroy the Buffer object
 */
Buffer::~Buffer() {
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
}

/**
 * @brief Insert an item into the buffer
 * @param item the item to insert
 * @return true if successful
 * @return false if not successful
 */
bool Buffer::insert_item(buffer_item item) {
    sem_wait(&empty); // Wait for space to become available
    sem_wait(&mutex); // Enter critical section

    // Insert item into the buffer
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;

    sem_post(&mutex); // Leave critical section
    sem_post(&full); // Signal that an item has been added

    return true;
}

/**
 * @brief Remove an item from the buffer
 * @param item the item to remove
 * @return true if successful
 * @return false if not successful
 */
bool Buffer::remove_item(buffer_item *item) {
    sem_wait(&full); // Wait for items to be available
    sem_wait(&mutex); // Enter critical section

    // Remove item from the buffer
    *item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;

    sem_post(&mutex); // Leave critical section
    sem_post(&empty); // Signal that a slot has been freed

    return true;
}

void Buffer::print_buffer() {
    sem_wait(&mutex); // Ensure exclusive access to buffer

    std::cout << "Buffer: [";
    int count = (in >= out) ? (in - out) : (BUFFER_SIZE - out + in);
    int index = out;
    for (int i = 0; i < count; i++) {
        std::cout << buffer[index];
        if (i < count - 1) std::cout << ", ";
        index = (index + 1) % BUFFER_SIZE;
    }
    std::cout << "]" << std::endl;

    sem_post(&mutex);
}

/**
 * @brief Get the size of the buffer
 * @return the size of the buffer
 */
int Buffer::get_size() { return BUFFER_SIZE; }


/**
 * @brief Get the number of items in the buffer
 * @return the number of items in the buffer
 */
int Buffer::get_count() {
    sem_wait(&mutex);
    int count = (in >= out) ? (in - out) : (BUFFER_SIZE + in - out);
    sem_post(&mutex);
    return count;
}

/**
 * @brief Chceck if the buffer is empty
 * @return true if the buffer is empty, else false
 */
bool Buffer::is_empty() {
    sem_wait(&mutex);
    bool empty = (in == out);
    sem_post(&mutex);
    return empty;
}

/**
 * @brief Check if the buffer is full
 * @return true if the buffer is full, else false
 */
bool Buffer::is_full() {
    sem_wait(&mutex);
    bool full = ((in + 1) % BUFFER_SIZE == out);
    sem_post(&mutex);
    return full;
}
