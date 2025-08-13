#include <stdio.h>

#define POOL_SIZE   (100 * 1024) // 100 KB of memory
#define MAX_ENTRIES 100          // Maximum number of block metadata entries

// Simulated memory pool
static unsigned char mem_pool[POOL_SIZE];

// Structure to hold metadata for each allocated block
typedef struct {
    unsigned char *start_addr; // Pointer to start of block in mem_pool[]
    size_t block_size;         // Size of the block in bytes
    int is_free;               // 1 = free, 0 = allocated
} MemBlock;

// Array to store block metadata
static MemBlock block_table[MAX_ENTRIES];
static int block_used_count = 0;      // Number of metadata entries in use
static unsigned char *pool_ptr = mem_pool; // Points to next unallocated space in mem_pool

// Allocate a memory block
void* my_malloc(size_t bytes) {
    // First, check if there is a previously freed block we can reuse
    for (int i = 0; i < block_used_count; i++) {
        if (block_table[i].is_free && block_table[i].block_size >= bytes) {
            block_table[i].is_free = 0; // Mark as allocated
            return block_table[i].start_addr;
        }
    }

    // If no reusable block, allocate from the unused pool space
    if (pool_ptr + bytes <= mem_pool + POOL_SIZE && block_used_count < MAX_ENTRIES) {
        block_table[block_used_count].start_addr = pool_ptr;
        block_table[block_used_count].block_size = bytes;
        block_table[block_used_count].is_free = 0;

        pool_ptr += bytes; // Move pool pointer forward
        return block_table[block_used_count++].start_addr;
    }

    return NULL; // Not enough memory
}

// Free a previously allocated memory block
void my_free(void *address) {
    for (int i = 0; i < block_used_count; i++) {
        if (block_table[i].start_addr == (unsigned char*)address && !block_table[i].is_free) {
            block_table[i].is_free = 1; // Mark block as free
            return;
        }
    }
}

int main() {
    void *pointers[5];

    // Allocate three blocks of memory
    pointers[0] = my_malloc(128);
    pointers[1] = my_malloc(1024);
    pointers[2] = my_malloc(4096);

    // Free one block (1024 bytes)
    my_free(pointers[1]);

    // Allocate a smaller block (512 bytes) that reuses freed space
    pointers[1] = my_malloc(512);

    printf("Memory allocation simulation complete.\n");
    return 0;
}
