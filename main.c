#include <unistd.h>
#include "mymemory.h"


int main(void)
{
    void *a = mymalloc(16);

    if (a == NULL)
    {
        return 1;
    }

    myfree(a);

    void *b = mymalloc(8);

    if (b == NULL)
    {
        return 1;
    }

    if (a != b)
    {
        write(STDOUT_FILENO, "reuse failed!\n", 13);
        return 1;
    }

    write(STDOUT_FILENO, "memory reuse successful\n", 24);

    return 0;
}