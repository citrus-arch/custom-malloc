#define _DEFAULT_SOURCE

#include "mymemory.h"

#include <unistd.h>

//block = 16 bytes
typedef struct block {
    //number of bytes requested by the user
    size_t size;
    int available;
    struct block *prev;
    struct block *next;
} block;

static block *head = NULL;

void *mymalloc(size_t size)
{
    if (size == 0)
    {
        return NULL;
    }

    //allign allocations to  bytes for our initial x86 experiment
    if (size > (size_t)-1 - 7)
    {
        return NULL;
    }

    //search for a free block that is large enough
    block *current = head;

    while (current != NULL)
    {
        if (current->available && current->size >= size)
        {
            current->available = 0;
            return (void *)(current + 1);
        }

        current = current->next;
    }

    //no suitable block : request space for metadata + user data
    void *memory = sbrk(sizeof(block) + size);

    if (memory == (void *)-1)
    {
        return NULL;
    }

    block *new_block = memory;
    new_block->size = size;
    new_block->available = 0;
    new_block->next = NULL;
    new_block->prev = NULL;

    //add the new block to the end of the list
    if (head == NULL)
    {
        head = new_block;
    }
    else
    {
        current = head;

        while (current->next != NULL)
        {
            current = current->next;
        }

        current->next = new_block;
        new_block->prev = current;
    }

    return (void *)(new_block + 1);
}

void myfree(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }

    //move backwards to find the block header
    //ptr points to the user's data
    //ptr is type-cast to block
    //So the pointer moves from the beginning of the user's data back to the beginning of the metadata.
    //we put that in header
    block *header = (block *)ptr - 1;

    //mark the block as free
    header->available = 1;
}