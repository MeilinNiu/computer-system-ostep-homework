#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define constants for block size, number of blocks, and number of inodes
#define BLOCK_SIZE 4096
#define NUM_BLOCKS 64
#define NUM_INODES 80

// Inode structure that contains the size of the file and an array of block pointers
typedef struct {
    int size;  // size of the file
    int blocks[15];  // direct block pointers
} Inode;

// Superblock structure containing bitmaps for free blocks and free inodes, and the start of the inode table
typedef struct {
    int free_blocks[NUM_BLOCKS];  // Bitmap for data blocks
    int free_inodes[NUM_INODES];  // Bitmap for inodes
    int inode_start;  // Start block for inode table
} Superblock;

// Directory entry structure that stores the name of a file and its associated inode number
typedef struct {
    char name[256];
    int inode_number;
} DirectoryEntry;

// Global file system structures
Superblock superblock;  // Superblock instance that stores general file system information
Inode inode_table[NUM_INODES];  // Array of inodes that represent the files
char data_blocks[NUM_BLOCKS][BLOCK_SIZE];  // Data blocks where the file contents are stored
DirectoryEntry root_directory[NUM_INODES];  // Root directory containing file names and their inode numbers

// Function prototypes
void initialize_fs();
void allocate_inode(int inode_num);
void write_file(int inode_num, char *data, int size);
void read_file(int inode_num);
void create_file(char *filename, int inode_num);
void list_files();

// Main function where the file system is initialized, files are created, written to, and read from
int main() {
    initialize_fs();  // Initialize the file system (setup free blocks, free inodes, root directory)

    // Create and write data to file1.txt
    create_file("file1.txt", 0);
    write_file(0, "Hello, World!", 13);  // Write "Hello, World!" to file1.txt
    read_file(0);  // Read and display the contents of file1.txt

    // Create another file and list files in the root directory
    create_file("file2.txt", 1);
    list_files();  // List all files in the root directory

    return 0;  // Exit the program
}

// Initialize the file system by setting the inode table, free blocks, free inodes, and root directory
void initialize_fs() {
    superblock.inode_start = 4;  // Example inode table starts at block 4
    memset(superblock.free_blocks, 1, sizeof(superblock.free_blocks));  // Mark all blocks as free initially
    memset(superblock.free_inodes, 1, sizeof(superblock.free_inodes));  // Mark all inodes as free initially

    // Initialize the root directory entry with inode number 0 and the name "root"
    root_directory[0].inode_number = 0;
    strcpy(root_directory[0].name, "root");
}

// Allocate an inode by setting its bitmap entry to 0 (allocated) and initializing its properties
void allocate_inode(int inode_num) {
    if (superblock.free_inodes[inode_num] == 1) {  // Check if the inode is free
        superblock.free_inodes[inode_num] = 0;  // Mark inode as allocated
        inode_table[inode_num].size = 0;  // Initialize the size of the file
        memset(inode_table[inode_num].blocks, -1, sizeof(inode_table[inode_num].blocks));  // No blocks allocated yet
    } else {
        printf("Error: Inode %d is already allocated\n", inode_num);  // Error message if inode is already allocated
    }
}

// Write data to the file's blocks. The data is copied to the data blocks based on the file's inode
void write_file(int inode_num, char *data, int size) {
    if (inode_num < NUM_INODES && superblock.free_inodes[inode_num] == 0) {  // Check if inode is valid
        inode_table[inode_num].size = size;  // Set the file size
        for (int i = 0; i < size / BLOCK_SIZE; i++) {  // Loop over the blocks needed to store the data
            inode_table[inode_num].blocks[i] = i;  // Allocate blocks for the file
            memcpy(data_blocks[i], data + (i * BLOCK_SIZE), BLOCK_SIZE);  // Copy data into the block
        }
        printf("Written data to inode %d\n", inode_num);  // Confirmation message
    } else {
        printf("Error: Invalid inode\n");  // Error message if inode is invalid
    }
}

// Read the file's data from the blocks allocated to it and print the contents
void read_file(int inode_num) {
    if (inode_num < NUM_INODES && superblock.free_inodes[inode_num] == 0) {  // Check if inode is valid
        printf("Reading file: inode %d, size %d\n", inode_num, inode_table[inode_num].size);
        for (int i = 0; i < inode_table[inode_num].size / BLOCK_SIZE; i++) {
            printf("Data Block %d: %s\n", inode_table[inode_num].blocks[i], data_blocks[inode_table[inode_num].blocks[i]]);
        }
    } else {
        printf("Error: Invalid inode\n");  // Error message if inode is invalid
    }
}

// Create a file by assigning a name and inode number to the root directory and allocating the inode
void create_file(char *filename, int inode_num) {
    if (inode_num < NUM_INODES) {  // Ensure inode number is valid
        printf("Creating file %s with inode %d\n", filename, inode_num);
        strcpy(root_directory[inode_num].name, filename);  // Assign the filename to the directory entry
        root_directory[inode_num].inode_number = inode_num;  // Set the inode number for the directory entry
        allocate_inode(inode_num);  // Allocate the inode for the file
    } else {
        printf("Error: Invalid inode\n");  // Error message if inode number is invalid
    }
}

// List all files in the root directory by checking the inode numbers of entries
void list_files() {
    printf("Listing files in the root directory:\n");
    for (int i = 0; i < NUM_INODES; i++) {
        if (root_directory[i].inode_number != -1) {  // Only print entries with valid inode numbers
            printf("%s\n", root_directory[i].name);  // Print the name of the file
        }
    }
}
