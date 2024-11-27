#include <stdio.h>
#include "memory_manager.h"

int main() {
    // Test my_malloc
    printf("Allocating 100 bytes...\n");
    void* ptr1 = my_malloc(100);
    if (ptr1) printf("Allocated memory at %p\n", ptr1);

    // Test my_free
    printf("Freeing memory...\n");
    my_free(ptr1);

    // Test my_realloc
    printf("Allocating 200 bytes...\n");
    void* ptr2 = my_malloc(200);
    if (ptr2) printf("Allocated memory at %p\n", ptr2);

    printf("Reallocating to 300 bytes...\n");
    void* ptr3 = my_realloc(ptr2, 300);
    if (ptr3) printf("Reallocated memory at %p\n", ptr3);

    // Clean up
    my_free(ptr3);

    return 0;
}
