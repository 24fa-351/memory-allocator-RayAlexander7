#include "memory_manager.h"
#include <unistd.h>  // for sbrk()
#include <stdio.h>   // for fprintf(), stderr

// Memory block structure
typedef struct Block {
    size_t size;
    struct Block* next;
} Block;

static Block* free_list = NULL;

// Function to get a block of memory from the system
void* get_me_blocks(size_t size) {
    void* ptr = sbrk(0);  // Get current break point
    if (sbrk(size) == (void*) -1) {  // Increase the program's data space
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    return ptr;
}

// Custom malloc function
void* my_malloc(size_t size) {
    if (size == 0) return NULL;

    // Traverse the free list to find a suitable block
    Block* prev = NULL;
    Block* curr = free_list;

    // First-fit algorithm
    while (curr != NULL) {
        if (curr->size >= size) {
            if (prev == NULL) {
                free_list = curr->next;
            } else {
                prev->next = curr->next;
            }
            return (void*)((char*)curr + sizeof(Block));  // Skip the block header
        }
        prev = curr;
        curr = curr->next;
    }

    // No suitable block found, get a new block from the system
    Block* new_block = get_me_blocks(size + sizeof(Block));
    if (new_block == NULL) return NULL;

    new_block->size = size;
    new_block->next = NULL;
    return (void*)((char*)new_block + sizeof(Block));  // Skip the block header
}

// Custom free function
void my_free(void* ptr) {
    if (ptr == NULL) return;

    Block* block = (Block*)((char*)ptr - sizeof(Block));  // Get the block header
    block->next = free_list;
    free_list = block;  // Add the block back to the free list
}

// Custom realloc function
void* my_realloc(void* ptr, size_t new_size) {
    if (ptr == NULL) {
        return my_malloc(new_size);  // Equivalent to malloc if ptr is NULL
    }

    if (new_size == 0) {
        my_free(ptr);  // Equivalent to free if new_size is 0
        return NULL;
    }

    // Get the old block
    Block* old_block = (Block*)((char*)ptr - sizeof(Block));
    if (old_block->size >= new_size) {
        return ptr;  // No need to reallocate if the old block is large enough
    }

    // Allocate a new block
    void* new_ptr = my_malloc(new_size);
    if (new_ptr == NULL) return NULL;

    // Copy the old data to the new block
    memcpy(new_ptr, ptr, old_block->size);
    my_free(ptr);  // Free the old block

    return new_ptr;
}
