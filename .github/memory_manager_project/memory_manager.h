#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <stddef.h>  // for size_t

// Function declarations
void* my_malloc(size_t size);
void my_free(void* ptr);
void* my_realloc(void* ptr, size_t new_size);

// Helper functions
void* get_me_blocks(size_t size);

#endif // MEMORY_MANAGER_H
