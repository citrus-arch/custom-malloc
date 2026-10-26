#define _DEFAULT_SOURCE

#include "mymemory.h"

#include <unistd.h>

//block = 16 bytes
typedef struct block {
    //number of bytes requested by the user
    size_t size;
    int available;
} block;

void *mymalloc(size_t size)
{
    if (size == 0)
    {
        return NULL;
    }

    //request space for metadata + user data
    void *memory = sbrk(sizeof(block) + size);

    if (memory == (void *)-1)
    {
        return NULL;
    }

    //store metadata at the beginning
    //treat the memory at 0x1000 as a block structure = (block *)memory
    //its a type cast
    //the pointer called header points to that structure
    //below line gives access to the metadata
    block *header = (block *)memory;

    //copies the requested size into the metadata
    header->size = size;
    header->available = 0;

    //return the memory immediately after the header
    return (void *)(header + 1);
}

void myfree(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    //move backwards to find the block header
    block *header = (block *)ptr - 1;

    //mark the block as free
    header->available = 1;
}