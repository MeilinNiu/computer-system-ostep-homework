#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 4096           // Define size of each page in bytes (4KB)
#define NUM_PAGES 256            // Number of pages in virtual memory
#define NUM_FRAMES 64            // Number of frames in physical memory
#define MAX_PROCESSES 10         // Maximum number of processes

// Page Table Entry structure, which stores the frame number and validity of a page
typedef struct {
    int frameNumber;             // Frame number in physical memory
    int valid;                   // Valid bit: 1 if page is in memory, 0 otherwise
} PageTableEntry;

// Page Table structure containing entries for each virtual page
typedef struct {
    PageTableEntry pages[NUM_PAGES];
} PageTable;

// Memory structure that manages physical frames and tracks mapping between pages and frames
typedef struct {
    int frameToPage[NUM_FRAMES]; // Maps frames to virtual pages
    int pageToFrame[NUM_PAGES];  // Maps pages to frames
    int freeFrames[NUM_FRAMES];  // Array to indicate free frames: 1 if free, 0 if occupied
} Memory;

// Initialize the page table for a process, marking all entries as invalid
void initializePageTable(PageTable *pt) {
    for (int i = 0; i < NUM_PAGES; i++) {
        pt->pages[i].frameNumber = -1;
        pt->pages[i].valid = 0;
    }
}

// Initialize physical memory, marking all frames as free
void initializeMemory(Memory *mem) {
    for (int i = 0; i < NUM_FRAMES; i++) {
        mem->freeFrames[i] = 1;      // 1 indicates the frame is free
        mem->frameToPage[i] = -1;
    }
    for (int i = 0; i < NUM_PAGES; i++) {
        mem->pageToFrame[i] = -1;
    }
}

// Find a free frame in physical memory; returns frame index if available, or -1 if full
int getFreeFrame(Memory *mem) {
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (mem->freeFrames[i] == 1) {
            mem->freeFrames[i] = 0;  // Mark frame as occupied
            return i;
        }
    }
    return -1;  // No free frame found
}

// Replace a page in memory with another using a random replacement strategy
void replacePage(Memory *mem, PageTable *pt, int page, int frame) {
    int oldPage = mem->frameToPage[frame];  // Get the old page in this frame
    pt->pages[oldPage].valid = 0;           // Invalidate the old page
    mem->frameToPage[frame] = page;         // Map frame to new page
    mem->pageToFrame[page] = frame;         // Map new page to frame
}

// Translate a virtual address to a physical address, handling page faults as needed
int translateAddress(PageTable *pt, Memory *mem, int virtualAddress) {
    int page = virtualAddress / PAGE_SIZE;      // Calculate page number
    int offset = virtualAddress % PAGE_SIZE;    // Calculate offset within the page

    // Check if page is already in memory
    if (pt->pages[page].valid) {
        return pt->pages[page].frameNumber * PAGE_SIZE + offset;
    }

    // Page fault handling: Find a free frame or replace an existing page
    int frame = getFreeFrame(mem);
    if (frame == -1) {  // No free frame, apply replacement strategy
        frame = rand() % NUM_FRAMES;  // Simple random replacement
        replacePage(mem, pt, page, frame);
    } else {
        mem->frameToPage[frame] = page;  // Map frame to page
        mem->pageToFrame[page] = frame;  // Map page to frame
    }

    // Update page table to mark page as valid and in memory
    pt->pages[page].frameNumber = frame;
    pt->pages[page].valid = 1;

    return frame * PAGE_SIZE + offset;
}

// Function to simulate accessing a memory address
void accessMemory(PageTable *pt, Memory *mem, int virtualAddress) {
    int physicalAddress = translateAddress(pt, mem, virtualAddress);
    printf("Virtual Address: %d => Physical Address: %d\n", virtualAddress, physicalAddress);
}

// Simulate a series of memory operations by randomly generating virtual addresses
void simulateOperations(PageTable *pt, Memory *mem) {
    int virtualAddress;

    // Simulate three random memory accesses
    virtualAddress = rand() % (NUM_PAGES * PAGE_SIZE);
    accessMemory(pt, mem, virtualAddress);

    virtualAddress = rand() % (NUM_PAGES * PAGE_SIZE);
    accessMemory(pt, mem, virtualAddress);

    virtualAddress = rand() % (NUM_PAGES * PAGE_SIZE);
    accessMemory(pt, mem, virtualAddress);
}

// Main function to initialize structures and simulate memory operations
int main() {
    PageTable pt;  // Page table for the process
    Memory mem;    // Physical memory

    // Initialize page table and memory
    initializePageTable(&pt);
    initializeMemory(&mem);

    // Run memory access simulation
    simulateOperations(&pt, &mem);

    return 0;
}