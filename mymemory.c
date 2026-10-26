#define _DEFAULT_SOURCE

#include "mymemory.h"

#include <unistd.h>

void *mymalloc(size_t size)
{
    if (size == 0)
    {
        return NULL;
    }

    void *ptr = sbrk(size);

    if (ptr == (void *)-1)
    {
        return NULL;
    }

    return ptr;
}