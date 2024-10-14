#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

// Structure to represent a memory block
typedef struct Block {
    int start;
    int size;
    struct Block* next;
} Block;

// Memory allocation manager
typedef struct {
    int totalSize;
    int headerSize;
    char policy[10];
    char returnPolicy[20];
    int align;
    Block* freeList;
} MallocManager;

// Function to create a new block
Block* createBlock(int start, int size) {
    Block* block = (Block*)malloc(sizeof(Block));
    block->start = start;
    block->size = size;
    block->next = NULL;
    return block;
}

// Function to initialize the memory manager
MallocManager* initMalloc(int size, int start, int headerSize, const char* policy, const char* order, int align) {
    MallocManager* manager = (MallocManager*)malloc(sizeof(MallocManager));
    manager->totalSize = size;
    manager->headerSize = headerSize;
    strcpy(manager->policy, policy);
    strcpy(manager->returnPolicy, order);
    manager->align = align;
    manager->freeList = createBlock(start, size);
    return manager;
}

// Function to align the size
int alignSize(int size, int alignment) {
    int remainder = size % alignment;
    if (remainder != 0) {
        size += (alignment - remainder);
    }
    return size;
}

// Function to allocate memory according to the policy
int allocateMemory(MallocManager* manager, int size) {
    if (manager->align > 0) {
        size = alignSize(size, manager->align);
    }
    size += manager->headerSize;
    
    Block* current = manager->freeList;
    Block* prev = NULL;
    Block* bestBlock = NULL;
    Block* bestPrev = NULL;

    int bestSize = (strcmp(manager->policy, "BEST") == 0) ? manager->totalSize + 1 : -1;

    // Searching for the best fit, worst fit, or first fit
    while (current != NULL) {
        if (current->size >= size) {
            if ((strcmp(manager->policy, "FIRST") == 0) ||
                (strcmp(manager->policy, "BEST") == 0 && current->size < bestSize) ||
                (strcmp(manager->policy, "WORST") == 0 && current->size > bestSize)) {
                bestBlock = current;
                bestPrev = prev;
                bestSize = current->size;
                if (strcmp(manager->policy, "FIRST") == 0) {
                    break;
                }
            }
        }
        prev = current;
        current = current->next;
    }

    // If no suitable block is found
    if (bestBlock == NULL) {
        printf("No suitable block found for allocation.\n");
        return -1;
    }

    // Allocating the memory block
    int allocatedAddress = bestBlock->start;
    bestBlock->start += size;
    bestBlock->size -= size;

    // Removing the block from the free list if fully allocated
    if (bestBlock->size <= 0) {
        if (bestPrev == NULL) {
            manager->freeList = bestBlock->next;
        } else {
            bestPrev->next = bestBlock->next;
        }
        free(bestBlock);
    }

    return allocatedAddress;
}

// Function to free the allocated memory
void freeMemory(MallocManager* manager, int address, int size) {
    // Add logic to merge blocks and add back to free list
    Block* newBlock = createBlock(address, size);
    newBlock->next = manager->freeList;
    manager->freeList = newBlock;
    printf("Memory freed at address: %d\n", address);
}

// Main function for testing
int main() {
    MallocManager* manager = initMalloc(1000, 0, 0, "FIRST", "ADDRSORT", -1);
    int addr1 = allocateMemory(manager, 100);
    printf("Allocated at address: %d\n", addr1);
    int addr2 = allocateMemory(manager, 200);
    printf("Allocated at address: %d\n", addr2);
    freeMemory(manager, addr1, 100);
    int addr3 = allocateMemory(manager, 50);
    printf("Allocated at address: %d\n", addr3);
    return 0;
}