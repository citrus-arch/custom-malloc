#ifndef MYMEMORY_H
#define MYMEMORY_H

#include <stddef.h>

void *mymalloc(size_t size);
void myfree(void *ptr);

#endif