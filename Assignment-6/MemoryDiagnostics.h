/**********************************************************
 * File: MemoryDiagnostics.h
 *
 * Code to allow for memory diagnostics.  These functions
 * allow us to count how many Nodes you have allocated and
 * deallocated.
 */
#ifndef MemoryDiagnostics_Included
#define MemoryDiagnostics_Included

/* Function: numAllocations
 * Usage: long x = numAllocations();
 * --------------------------------------------------------
 * Returns how many total allocations of Nodes have occurred
 * throughout the program.
 */
long numAllocations();

/* Function: numDeallocations
 * Usage: long x = numDeallocations();
 * --------------------------------------------------------
 * Returns how many total deallocations of Nodes have occurred
 * throughout the program.
 */
long numDeallocations();

#endif
