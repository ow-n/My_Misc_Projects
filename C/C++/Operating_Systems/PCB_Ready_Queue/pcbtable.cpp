/**
 * @file pcbtable.h
 * @author Owen Man
 * @brief This is the implementation file for the PCBTable class.
 */

#include "pcbtable.h"

/**
 * @brief Construct a new PCBTable object of the given size (number of PCBs)
 *
 * @param size: the capacity of the PCBTable
 */
PCBTable::PCBTable(int size) {
   table.reserve(size);
}

/**
 * @brief Destroy the PCBTable object. Make sure to delete all the PCBs in the table.
 *
 */
PCBTable::~PCBTable() {
    // Deletes all the PCBs in the table
    for (PCB* pcb : table) {
        delete pcb;
    }
   table.clear();
}

/**
 * @brief Get the PCB at index "idx" of the PCBTable.
 *
 * @param idx: the index of the PCB to get
 * @return PCB*: pointer to the PCB at index "idx"
 */
PCB* PCBTable::getPCB(unsigned int idx) {
    if (idx < table.size()) { // if idx is within bounds of vector
        return table[idx];
    }
    return NULL;
}

/**
 * @brief Add a PCB pointer to the PCBTable at index idx.
 *
 * @param pcb: the PCB to add
 */
void PCBTable::addPCB(PCB *pcb, unsigned int idx) {
    if (idx >= table.size()) { // make sure idx is large enough for new PCB
        table.resize(idx + 1, nullptr); // resizes vector to make room
    }
    // Add a PCB pointer to the PCBTable at index idx.
    table[idx] = pcb;
}
